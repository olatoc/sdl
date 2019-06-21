#include <stdio.h>
#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h> 
#include "game.h"

Game::Game(){
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        win = SDL_CreateWindow("GAME",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        1000, 1000, 0);
        rend = SDL_CreateRenderer(win, -1, 0);
        isRunning = true;
    } else{
        isRunning = false;
    }

}
Game::~Game(){
    
}
void Game::init(){
    count = 0;

    isRunning = true;
    p = new Player();
    e = new Enemy();
    p->player_init(rend);
    e->enemy_init(rend);
}

void Game::handleEvents(){
    SDL_Event event;
  
    while (SDL_PollEvent(&event)){
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) { 
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    p->jump();
                    p->isJump = true;
                    break;
                 case SDL_SCANCODE_A:
                 case SDL_SCANCODE_LEFT:
                    p->move(false);
                    p->isMove = true;
                    break;
                // case SDL_SCANCODE_S:
                // case SDL_SCANCODE_DOWN:
                //     p->dest.y += speed / 30;
                //     break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    p->move(true);
                    p->isMove = true;
                break;
           }
       }
    }
}
void Game::update(){
    p->player_update();
    e->enemy_update();
    if (count % 3 == 0){
        p->vely += 1;
        e->vely += 1;
    }
    
    count++;
    //printf("%d\n",count);
    SDL_Delay(30);
}
void Game::render(){
    SDL_RenderClear(rend);
    SDL_RenderCopy(rend, p->player_tex, 0, p->player_rect);
    SDL_RenderCopy(rend, e->enemy_tex, 0, e->enemy_rect);
    SDL_RenderPresent(rend);
}
SDL_Renderer* Game::getRend(){
    return rend;
}

void Game::clean(){
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);
    SDL_Quit();
}
bool Game::running(){
    return isRunning;
}

