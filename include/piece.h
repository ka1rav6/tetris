#ifndef PIECE_H
#define PIECE_H

#include "definitions.h"

class Board;
const int MIDDLE_X = COLS / 2;
const char shapes_Name[7] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};

class Piece {
public:
    Piece();
    ~Piece();
    void init(Board* board, char type);
    void PlaceOnBoard(Board* b);
    void handleEvent(SDL_Event &e);
    void update();
    void render(SDL_Renderer *r, Board* board);
    void rotate();
private:
    char type;       // I, O, T, S, Z, J, L
    int rotation;   // 0–3
    int xpos, ypos;
    void rotateLeft();
    void rotateRight();
};



#endif