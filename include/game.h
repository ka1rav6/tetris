#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <cerrno>
#include <string>
#include <cstring>


class Game{

public:
    Game();
    ~Game();
    void init(const std::string title, int x, int y, int height, int width);
    void handleEvents();
    bool running();
    void render();
    void update();
    void clean();
private:
    bool isRunning;
    SDL_Window* window;
    SDL_Renderer* rend;
    
};



#endif  /* game.h*/
