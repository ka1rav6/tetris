#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>
#include <cerrno>
#include <string>
#include <cstring>
#include <vector>

#define WIN_HEIGHT 800
#define WIN_WIDTH 600
#define ROWS 20
#define COLS 10

typedef std::vector<std::vector<int>> shapeGrid;


enum Fill {
    EMPTY, // 0
    FILLED, // 1 
    FIXED // 2
};

#endif