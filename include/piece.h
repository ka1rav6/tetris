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
    void RemoveFromBoard(Board* b);
    void handleEvent(SDL_Event &e, Board* board);
    void update(Board* board);
    void render(SDL_Renderer *r, Board* board);
    void rotate();
    bool canMove(Board* b, int newX, int newY);
    bool canRotate(Board* b);
    void lockToBoard(Board* b);
private:
    char type;       // I, O, T, S, Z, J, L
    int rotation;   // 0–3
    int xpos, ypos;
    shapeGrid currentShape;
    void rotateLeft();
    void rotateRight();
    Uint32 lastFallTime;
    Uint32 fallDelay;
};



#endif