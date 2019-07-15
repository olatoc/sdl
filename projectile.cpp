#include "projectile.h"

Projectile::Projectile(int xc, int yc, int velc, ushort idc){
    x = xc;
    y = yc;
    vel = velc;
    id = idc;
    init();
}

void Projectile::init(){
    rect = new SDL_Rect();
    rect->x = x;
    rect->y = y;
    rect->w = 20;
    rect->h = 20;
}

void Projectile::move(){
    rect->x += vel;
}

bool Projectile::out_of_bounds(){
    return !(rect->x + rect->w > 0 && rect->x < 2000);
}

bool Projectile::hit_player(Player *player){
    return rect->x + rect->w > player->player_rect->x && rect->x < player->player_rect->x + player->player_rect->w
            && rect->y + rect->h > player->player_rect->y && rect->y < player->player_rect->y + player->player_rect->h;
}