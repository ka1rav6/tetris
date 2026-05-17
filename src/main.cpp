#include "../include/game.h"

Game *game = nullptr;

int main(int argc, const char** argv){
    srand(time(NULL));
    game = new Game();
    game->init("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIN_WIDTH, WIN_HEIGHT);
    while(game->running()){
        game->handleEvents();
        game->update();
        game->render();
    }
    game->clean();
    delete game;
    return 0;
}
