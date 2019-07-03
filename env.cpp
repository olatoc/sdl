#include "env.h"

#define x rect->x
#define y rect->y
#define w rect->w
#define h rect->h

Platform::Platform(int xc, int yc, int wid, int hgt){
    platform_init();
    x = xc;
    y = yc;
    w = wid;
    h = hgt;
};

void Platform::platform_init(){
    rect = new SDL_Rect();
}