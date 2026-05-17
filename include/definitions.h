#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "SDL2/SDL.h"
#include <iostream>
#include <cerrno>
#include <string>
#include <cstring>
#include <vector>
#include <map>

#define WIN_HEIGHT 600
#define WIN_WIDTH 500
#define ROWS 20
#define COLS 10
#define CELL_SIZE 28
#define BOARD_X 20
#define BOARD_Y 20
#define PANEL_X (BOARD_X + COLS * CELL_SIZE + 20)

typedef std::vector<std::vector<int>> shapeGrid;

enum Fill {
    EMPTY,
    FILLED,
    FIXED
};

#endif