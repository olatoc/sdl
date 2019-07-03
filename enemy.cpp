#include <stdio.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h> 
#include "enemy.h"


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

    enemy_rect = new SDL_Rect();
    enemy_rect->x = 100;
    enemy_rect->y = 500;
    enemy_rect->w = width;
    enemy_rect->h = height;
}

void Enemy::enemy_update(){

    if (!isJump && !bottomClamp()){
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
    return enemy_rect->y + vely < 1500 - height ? true : false;
}
bool Enemy::topClamp(){
    return enemy_rect->y + vely > 0 ? true : false;
}

void Enemy::jump(){
    vely = -20;
}

void Enemy::move(bool dir){
    if (dir){
        velx = 5;
    } else{
        velx = -5;
    }
}

void Enemy_events();

void Enemy_render();
void Enemy_clean();