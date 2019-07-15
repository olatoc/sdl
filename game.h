#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "enemy.h"
#include "env.h"
//#include "projectile.h"

class Game{

private:
    bool isRunning;
    SDL_Window *win;
    SDL_Renderer *rend;
    SDL_Surface* screen;
    const Uint8 *state;

public:
    Game(int width, int height);
    ~Game();

    int width, height;
    void init();
    void player_init();
    void switch_gravity();
    int g;
    bool player_onPlatform();
    bool enemy_onPlatform(Enemy *e);

    void handleEvents();
    void update();
    void render();
    void clean();

    SDL_Renderer* getRend();

    bool running();

    Player *p;
    Enemy *e;
    Platform *plat[5];
    Enemy *enemies[10];

    int *count;

};