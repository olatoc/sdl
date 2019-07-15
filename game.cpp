#include <stdio.h>
#include "game.h"

#define px p->player_rect->x
#define py p->player_rect->y
#define ph p->player_rect->h
#define pw p->player_rect->w

#define E_COUNT (ushort)1

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
    count = new int(0);
    g = 3;

    isRunning = true;
    p = new Player(200,200);
    plat[0] = new Platform(1000,1250, 500, 50);
    plat[1] = new Platform(700,1000, 500, 50);
    plat[2] = new Platform(400,750, 500, 50);
    plat[3] = new Platform(100,1300, 500, 50);
    plat[4] = new Platform(1000,400, 500, 50);


    p->player_init(rend);
    int size;
    for (int i = 0; i < E_COUNT; i++){
        size = rand() % 50 + 50;
        enemies[i] = new Enemy(size,size);
        enemies[i]->enemy_init(rend);
        enemies[i]->player = p;
        enemies[i]->count = count;
        enemies[i]->enemy_rect->x = i*(2000/10);
    }
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
    for (int i = 0; i < E_COUNT; i++){
        enemies[i]->enemy_update();
    }
    //apply gravity to player and enemies
    if (*count % 2 == 0){
        p->vely += g;
        for (int i = 0; i < E_COUNT; i++){
            enemies[i]->vely += g*(rand() % 3 + 1);
        }
    }

    p->onPlatform = player_onPlatform();
    for (int i = 0; i < E_COUNT; i++){
        enemies[i]->onPlatform = enemy_onPlatform(enemies[i]);
        if (*count % 30 == 0){
            enemies[i]->shoot();
        }
    }
    (*count)++;
    SDL_Delay(30);
}
void Game::render(){
    SDL_RenderClear(rend);
    SDL_SetRenderDrawColor( rend, 0, 0, 100, 255 );
    //Render player
    SDL_RenderCopy(rend, p->player_tex, 0, p->player_rect);

    //Render platforms
    for (int i = 0; i < 5; i++){
        SDL_RenderFillRect(rend, plat[i]->rect);
    }
    //Render enemies
    for (int i = 0; i < E_COUNT; i++){
        SDL_RenderCopy(rend, enemies[i]->enemy_tex, 0, enemies[i]->enemy_rect);
        if (enemies[i]->proj_vec.size() > 0){
            int size = enemies[i]->proj_vec.size();
            for (int j = 0; j < size; j++){
                SDL_RenderFillRect(rend, enemies[i]->proj_vec[j]->rect);
            }
        }

    }
    //Render background
    SDL_SetRenderDrawColor( rend, 50, 50, 180, 255 );
    SDL_RenderPresent(rend);
}

bool Game::player_onPlatform(){
    for (int i = 0; i < 5; i++){
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
bool Game::enemy_onPlatform(Enemy *e){
    int e_x, e_w, e_y, e_h;
    e_x = e->enemy_rect->x;
    e_w = e->enemy_rect->w;
    e_y = e->enemy_rect->y;
    e_h = e->enemy_rect->h;
    for (int i = 0; i < 5; i++){
        if (e_x + e_w > plat[i]->rect->x
        && e_x < plat[i]->rect->x + plat[i]->rect->w
        && e_y  + e_h + e->vely > plat[i]->rect->y
        && e_y + e_h < plat[i]->rect->y + 10
        && e->vely > 0){
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

