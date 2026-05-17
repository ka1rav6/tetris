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
    window = SDL_CreateWindow(title.c_str(), x, y, width, height, 0);
    rend = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(rend)
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    board = new Board();
    board->initGrid(rend);
    isRunning = true;
}

void Game::handleEvents(){
    SDL_Event event;
    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT)
            isRunning = false;
        else
            board->handleEvent(event);
    }
}

bool Game::running(){
    return isRunning;
}

void Game::render(){
    SDL_SetRenderDrawColor(rend, 0, 0, 0, 255);
    SDL_RenderClear(rend);
    board->renderGrid(rend);
    SDL_RenderPresent(rend);
}

void Game::update(){
    board->update();
}

void Game::clean(){
    delete board;
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(rend);
    SDL_Quit();
}
