#ifndef BOARD_H
#define BOARD_H

#include "definitions.h"


class Board{
public:
    Board();
    ~Board();
    void initGrid();
    void placePiece();
    void renderGrid(SDL_Renderer *rend);
private:
    int grid[20][20];
    const int TILE_HEIGHT = WIN_HEIGHT / ROWS;
    const int TILE_WIDTH = WIN_WIDTH / COLS;
};



#endif