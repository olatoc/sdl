#include "game.h"

Game *game;

int main(int argc, const char *argv[]){
    game = new Game(2000, 1500);

    game->init();
    
    while (game->running()){
        game->handleEvents();
        game->update();
        game->render();
    }

    game->clean();
}