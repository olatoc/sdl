#include <SDL2/SDL.h> 
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h> 

class Platform{
public:
    SDL_Texture *player_tex;
    SDL_Rect *player_rect;
    SDL_Renderer *rend;
};