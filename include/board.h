#ifndef BOARD_H
#define BOARD_H

#include "definitions.h"
#include "piece.h"

class Board{
public:
    Board();
    ~Board();
    void initGrid(SDL_Renderer *rend);
    void placePiece();
    void renderGrid(SDL_Renderer *rend);
    int grid[20][20];
private:
    const int TILE_HEIGHT = WIN_HEIGHT / ROWS;
    const int TILE_WIDTH = WIN_WIDTH / COLS;
    Piece *pieces;
    void generatePiece();
};



#endif