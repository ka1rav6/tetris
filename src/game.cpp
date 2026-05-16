#include "../include/game.h"
#include "../include/board.h"

Board *board = nullptr;

Game::Game(){}
Game::~Game(){}

void Game::init(const std::string title, int x, int y, int width, int height){
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        perror("Subsystems Initialisation Failed");
        return;
    }
    std::cout << "Subsystems Initiatised" <<std::endl;
    window = SDL_CreateWindow(title.c_str(), x, y, width, height, 0);
    
    if (window)
        std::cout << "Window Created" <<std::endl;

    rend = SDL_CreateRenderer(window, -1, 0);
    if (rend){
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
        std::cout << "Renderer has been created successfully" <<std::endl;
    }
    board = new Board();
    board->initGrid(rend);
    isRunning = true;

}

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    // Main handling events part:
    switch (event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            // handle more events here
            break;
    }
}
bool Game::running(){
    return isRunning;
}

void Game::render(){
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255); // clear color
    SDL_RenderClear(rend);
    // this is where i would add stuff to render
    board->renderGrid(rend);
    SDL_RenderPresent(rend);
}
void Game::update(){}
void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);
    SDL_Quit();
    std::cout << "Game has been cleaned!" <<std::endl;
}





