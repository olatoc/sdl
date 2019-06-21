#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h> 

class Player{
public:
    Player();
    ~Player();

    SDL_Texture *player_tex;
    SDL_Rect *player_rect;
    SDL_Renderer *rend;

    void player_events();
    void player_update();
    void jump();
    void move(bool dir);
    bool topClamp();
    bool bottomClamp();
    void player_init(SDL_Renderer *render);
    void player_render();
    void player_clean();

    int x, y;
    int velx, vely;

    bool isJump;
    bool isMove;
};