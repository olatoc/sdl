#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "player.h"

class Projectile{

public:
    Projectile(int x, int y, int vel, ushort idc);
    void init();
    void move();
    bool out_of_bounds();
    bool hit_player(Player* p);

    SDL_Rect *rect;

    int x,y;
    int vel;
    ushort id;

};

// struct proj_node{
//     Projectile *proj;
//     proj_node *next;
// };