#include <stdio.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h> 
#include "enemy.h"

Enemy::Enemy(){
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
    enemy_rect->w = 150;
    enemy_rect->h = 100;
}

void Enemy::enemy_update(){

    enemy_rect->w = (int)(1000 - enemy_rect->y)/2;
    enemy_rect->h = (int)(1000 - enemy_rect->y)/2;

    if (!bottomClamp()){
        vely *= -1;
    }
    if (!topClamp()){
        vely *= -1;
    }

    if (enemy_rect->x > 900 || enemy_rect->x < 0){
        velx *= -1;
    }

    enemy_rect->x += velx;
    enemy_rect->y += vely;

}

bool Enemy::bottomClamp(){
    return enemy_rect->y < 900 ? true : false;
}
bool Enemy::topClamp(){
    return enemy_rect->y > 0 ? true : false;
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