#include <stdio.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h> 
#include "game.h"

SDL_Rect *tempRect;

Game::Game(int width, int height){
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        win = SDL_CreateWindow("GAME",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        width, height, 0);
        rend = SDL_CreateRenderer(win, -1, 0);
        isRunning = true;
    } else{
        isRunning = false;
    }

}
Game::~Game(){
    
}
void Game::init(){
    screen = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
    count = 0;
    g = 3;

    isRunning = true;
    p = new Player(200,200);
    e = new Enemy();
    p->player_init(rend);
    e->enemy_init(rend);

    tempRect = new SDL_Rect();
    tempRect->x = 500;
    tempRect->y = 500;
    tempRect->w = 400;
    tempRect->h = 50;
}

void Game::handleEvents(){
    state = SDL_GetKeyboardState(NULL);
    SDL_PumpEvents();
    if (state[SDL_SCANCODE_A]){
        p->movex(false);
        p->isMove = true;
    } else if (state[SDL_SCANCODE_D]){
        p->movex(true);
        p->isMove = true;
    }
    if (state[SDL_SCANCODE_W]){
        if (!p->isJump){
            p->jump();
        }
        p->isJump = true;
    }else{
        p->isJump = false;
    }
    if (state[SDL_SCANCODE_SPACE]){
        if (!p->isSwitch){
            switch_gravity();
        }
        p->isSwitch = true;
    } else{
        p->isSwitch = false;
    }
    SDL_Event event;
    while (SDL_PollEvent(&event)){
        if (event.type == SDL_QUIT){
            isRunning = false;
        }
    }
}

void Game::update(){
    p->player_update();
    e->enemy_update();
    if (count % 3 == 0){
        p->vely += g;
        e->vely += g;
    }
    count++;
    //printf("%d\n",count);
    SDL_Delay(33);
}
void Game::render(){
    SDL_RenderClear(rend);
    SDL_SetRenderDrawColor( rend, 0, 0, 255, 255 );
    //Render player
    SDL_RenderCopy(rend, p->player_tex, 0, p->player_rect);
    //Render rects
    //SDL_RenderFillRect(rend, tempRect);
    SDL_SetRenderDrawColor( rend, 255, 105, 180, 255 );
    SDL_RenderPresent(rend);
}
SDL_Renderer* Game::getRend(){
    return rend;
}

void Game::switch_gravity(){
    g *= -1;
}

void Game::clean(){
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}

bool Game::running(){
    return isRunning;
}

