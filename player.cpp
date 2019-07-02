#include <stdio.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h> 
#include "player.h"

Player::Player(int wid, int hgt){
    width = wid;
    height = hgt;
    x = 100;
    y = 100;
    velx = 0;
    vely = 0;
}

Player::~Player(){

}
void Player::player_init(SDL_Renderer *render){
    SDL_Surface *temp_surface = IMG_Load("/home/oliver/Documents/Games/SDL/img/dog.png");
    player_tex = SDL_CreateTextureFromSurface(render, temp_surface);
    SDL_FreeSurface(temp_surface);

    player_rect = new SDL_Rect();
    player_rect->x = 100;
    player_rect->y = 500;
    player_rect->w = width;
    player_rect->h = height;
}

void Player::player_update(){

    if (!isJump && !bottomClamp()){
        vely = 0;
    }
    if (!topClamp()){
        vely *= -1;
    }

    if (rightClamp() || leftClamp()){
        velx = 0;
    }

    if (isMove){
        player_rect->x += velx;
    }
    player_rect->y += vely;
    isMove = false;
}

bool Player::leftClamp(){
    return player_rect->x + velx < 0 ? true : false;
}
bool Player::rightClamp(){
    return player_rect->x + velx > 2000 - player_rect->w ? true : false;
}
bool Player::bottomClamp(){
    return player_rect->y + vely < 1500 - height ? true : false;
}
bool Player::topClamp(){
    return player_rect->y + vely > 0 ? true : false;
}

void Player::jump(){
    vely = -20;
}

void Player::movex(bool dir){
    if (dir){
        velx = 10;
    } else{
        velx = -10;
    }
}
void Player::movey(bool dir){
    if (dir){
        velx = 5;
    } else{
        velx = -5;
    }
}

void player_events();

void player_render();
void player_clean();
