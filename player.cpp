#include <stdio.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h> 
#include "player.h"

Player::Player(){
    x = 100;
    y = 100;
    velx = 0;
    vely = 0;
}

Player::~Player(){

}
void Player::player_init(SDL_Renderer *render){
    SDL_Surface *temp_surface = IMG_Load("/home/oliver/Documents/Games/SDL/img/quieres.jpg");
    player_tex = SDL_CreateTextureFromSurface(render, temp_surface);
    SDL_FreeSurface(temp_surface);

    player_rect = new SDL_Rect();
    player_rect->x = 100;
    player_rect->y = 500;
    player_rect->w = 100;
    player_rect->h = 100;
}

void Player::player_update(){

    if (vely == 0){
        //printf("%d\n", player_rect->y);
    }


    if (!isJump && !bottomClamp()){
        vely = 0;
    }
    if (!topClamp()){
        vely *= -5;
    }
    isJump = false;

    if (player_rect->x > 900 || player_rect->x < 0){
        velx *= -1;
    }

    //if (isMove){
        player_rect->x += velx;
    //}
    player_rect->y += vely;
    isMove = false;
    //printf("%d\n", vely);
}

bool Player::bottomClamp(){
    return player_rect->y < 900 ? true : false;
}
bool Player::topClamp(){
    return player_rect->y > 0 ? true : false;
}

void Player::jump(){
    vely = -20;
}

void Player::move(bool dir){
    if (dir){
        velx = 5;
    } else{
        velx = -5;
    }
}

void player_events();

void player_render();
void player_clean();