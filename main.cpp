#include "game.h"

Game *game;

#define WIDTH 2000
#define HEIGHT 1500

int main(int argc, const char *argv[]){
    game = new Game(WIDTH, HEIGHT);

    game->init();
    
    while (game->running()){
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();
}