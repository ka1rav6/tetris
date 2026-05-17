#ifndef BOARD_H
#define BOARD_H

#include "definitions.h"
#include "piece.h"

class Board
{
public:
    Board();
    ~Board();
    Fill grid[ROWS][COLS];
    Piece currentPiece;
    void initGrid(SDL_Renderer *rend);
    void renderGrid(SDL_Renderer *rend);
    void generatePiece();
    void handleEvent(SDL_Event &e);
    void update();
};

#endif