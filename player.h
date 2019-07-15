#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h> 

class Player{
public:
    Player(int width, int height);
    ~Player();

    SDL_Texture *player_tex;
    SDL_Rect *player_rect;
    SDL_Renderer *rend;

    void player_events();
    void player_update();
    void jump();
    void movex(bool dir);
    void movey(bool dir);
    bool leftClamp();
    bool rightClamp();
    bool topClamp();
    bool bottomClamp();
    void player_init(SDL_Renderer *render);
    void player_render();
    void player_clean();

    int width, height;
    int x, y;
    int velx, vely;

    ushort health;

    bool isJump;
    bool isMove;
    bool isSwitch;
    bool onPlatform;
};