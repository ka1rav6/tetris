#include "../include/game.h"

Game *game = nullptr;

int main(int argc, const char** argv){
    game = new Game();
    game->init("Sample", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 800);
    // main game loop
    while (game->running()){
        game->handleEvents();
        game->update();
        game->render();
    }
    game->clean();
    return 0;
}
