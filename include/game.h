#ifndef GAME_H
#define GAME_H

#include "definitions.h"

class Game{

public:
    Game();
    ~Game();
    void init(const std::string title, int x, int y, int width, int height);
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
