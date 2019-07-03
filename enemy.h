#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h> 

class Enemy{
public:
    Enemy(int width, int height);
    ~Enemy();

    SDL_Texture *enemy_tex;
    SDL_Rect *enemy_rect;
    SDL_Renderer *rend;

    void enemy_events();
    void enemy_update();
    void jump();
    void move(bool dir);
    bool rightClamp();
    bool leftClamp();
    bool topClamp();
    bool bottomClamp();
    void enemy_init(SDL_Renderer *render);
    void enemy_render();
    void enemy_clean();

    int x, y;
    int velx, vely;
    int width, height;

    bool isJump;
    bool isMove;
};