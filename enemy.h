#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h> 
#include <vector>
#include <iostream>
#include "projectile.h"

using namespace std;

class Enemy{
public:
    Enemy(int width, int height);
    ~Enemy();

    SDL_Texture *enemy_tex;
    SDL_Rect *enemy_rect;
    SDL_Renderer *rend;
    int *count;

    Player *player;
    Player *getPlayer();

    void enemy_events();
    void enemy_update();
    void jump();
    void move();
    void shoot();
    bool rightClamp();
    bool leftClamp();
    bool topClamp();
    bool bottomClamp();
    void enemy_init(SDL_Renderer *render);
    void enemy_render();
    void enemy_clean();

    int x, y;
    int velx, vely;
    int speed;
    int width, height;

    std::vector<Projectile*> proj_vec;

    void delete_proj(Projectile *proj);
    void update_proj();

    bool isJump;
    bool isMove;
    bool onPlatform;
};
