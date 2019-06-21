#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "player.h"

class Game{

private:
    bool isRunning;
    SDL_Window *win;
    SDL_Renderer *rend;

public:
    Game();
    ~Game();
    void init();
    void player_init();

    void handleEvents();
    void update();
    void render();
    void clean();

    SDL_Renderer* getRend();

    bool running();

    Player *p;

    int count;

};