#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>

class Platform{
public:
    Platform(int xc, int yc, int wid, int hgt);
    SDL_Rect *rect;

    void platform_init();
};