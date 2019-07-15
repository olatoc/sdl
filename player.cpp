#include <stdio.h>
#include "player.h"

#define x player_rect->x
#define y player_rect->y

Player::Player(int wid, int hgt){
    width = wid;
    height = hgt;
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
    //health_bar = new SDL_Rect();
    x = 100;
    y = 500;
    player_rect->w = width;
    player_rect->h = height;

    health = 100;
}

void Player::player_update(){

    if (bottomClamp()){
        vely = 0;
    }
    if (!isJump && onPlatform){
        vely = 0;
    }
    if (!topClamp()){
        vely *= -1;
    }

    if (rightClamp() || leftClamp()){
        velx = 0;
    }

    if (isMove){
        x += velx;
    }
    y += vely;
    isMove = false;
}

bool Player::leftClamp(){
    return x + velx < 0 ? true : false;
}
bool Player::rightClamp(){
    return x + velx > 2000 - player_rect->w ? true : false;
}
bool Player::bottomClamp(){
    return y + vely < 1500 - height ? false : true;
}
bool Player::topClamp(){
    return y + vely > 0 ? true : false;
}

void Player::jump(){
    vely = -30;
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
