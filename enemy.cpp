#include <stdio.h>
#include "enemy.h"

#define DIST_P enemy_rect->x + enemy_rect->w/2 - (player->player_rect->x + player->player_rect->w/2)
#define PROJ_TICK *count % 3 == 0

Enemy::Enemy(int wid, int hgt){
    width = wid;
    height = hgt;
    x = 200;
    y = 200;
    velx = 0;
    vely = 0;
}

Enemy::~Enemy(){

}
void Enemy::enemy_init(SDL_Renderer *render){
    SDL_Surface *temp_surface = IMG_Load("/home/oliver/Documents/Games/SDL/img/quieres.jpg");
    enemy_tex = SDL_CreateTextureFromSurface(render, temp_surface);
    SDL_FreeSurface(temp_surface);

    speed = 5;

    enemy_rect = new SDL_Rect();
    enemy_rect->x = 100;
    enemy_rect->y = 500;
    enemy_rect->w = width;
    enemy_rect->h = height;

}

void Enemy::enemy_update(){
    move();
    update_proj();

    if (onPlatform){
        vely = 0;
    }
    if (bottomClamp()){
        vely = 0;
    }
    if (!topClamp()){
        vely *= -1;
    }

    if (rightClamp() || leftClamp()){
        velx = 0;
    }

    enemy_rect->x += velx;
    enemy_rect->y += vely;
    isMove = false;

}

bool Enemy::leftClamp(){
    return enemy_rect->x + velx < 0 ? true : false;
}
bool Enemy::rightClamp(){
    return enemy_rect->x + velx > 2000 - enemy_rect->w ? true : false;
}
bool Enemy::bottomClamp(){
    return enemy_rect->y + vely < 1500 - height ? false : true;
}
bool Enemy::topClamp(){
    return enemy_rect->y + vely > 0 ? true : false;
}

void Enemy::jump(){
    vely = -20;
}

void Enemy::move(){
    if (DIST_P < 0){
        velx = speed;
    } else{
        velx = -speed;
    }
}

void Enemy::shoot(){
    proj_vec.push_back(new Projectile(enemy_rect->x, enemy_rect->y, velx > 0 ? 10 : -10, rand()));
}

void Enemy::delete_proj(Projectile *proj){
    ushort id = proj->id;
    for (int i = 0; i < proj_vec.size(); i++){
        if (proj_vec[i]->id == id){
            proj_vec.erase(proj_vec.begin() + i);
        }
    }
}

void Enemy::update_proj(){
    int size = proj_vec.size();
    for (int i = 0; i < size; i++){
        proj_vec[i]->move();
        if (PROJ_TICK){
            if (proj_vec[i]->hit_player(player)){
                delete_proj(proj_vec[i]);
            } else if (proj_vec[i]->out_of_bounds()){
                delete_proj(proj_vec[i]);
                player->health -= 1;
            }
        }
    }
}
