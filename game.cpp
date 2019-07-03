#include <stdio.h>
#include "game.h"

#define px p->player_rect->x
#define py p->player_rect->y
#define ph p->player_rect->h
#define pw p->player_rect->w

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
    e = new Enemy(200,200);
    plat[0] = new Platform(1000,1000, 800, 50);
    plat[1] = new Platform(500,500, 800, 50);
    p->player_init(rend);
    e->enemy_init(rend);

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
    if (count % 2 == 0){
        p->vely += g;
        e->vely += 2*g;
    }
    if (check()){
        p->isPlatform = true;
    } else{
        p->isPlatform = false;
    }
    count++;
    //printf("%d\n",count);
    SDL_Delay(33);
}
void Game::render(){
    SDL_RenderClear(rend);
    SDL_SetRenderDrawColor( rend, 0, 0, 100, 255 );
    //Render player
    SDL_RenderCopy(rend, p->player_tex, 0, p->player_rect);
    //SDL_RenderCopy(rend, e->enemy_tex, 0, e->enemy_rect);

    //Render rects
    for (int i = 0; i < 2; i++){
        SDL_RenderFillRect(rend, plat[i]->rect);
    }
    SDL_SetRenderDrawColor( rend, 50, 50, 180, 255 );
    SDL_RenderPresent(rend);
}

bool Game::check(){
    //printf("%d\n", sizeof(plat)/sizeof(void*));
    for (int i = 0; i < 2; i++){
        if (px + pw > plat[i]->rect->x
        && px < plat[i]->rect->x + plat[i]->rect->w
        && py  + ph + p->vely > plat[i]->rect->y
        && py + ph < plat[i]->rect->y + 10
        && p->vely > 0){
            return true;
        }
    }
    return false;
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

