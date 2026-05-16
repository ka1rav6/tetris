#ifndef PIECE_H
#define PIECE_H

#include "definitions.h"

class Piece {
public:
    Piece();
    void init(int type);
    void handleEvent(SDL_Event &e);
    void update();
    void render(SDL_Renderer *r);
private:
    int type;       // I, O, T, S, Z, J, L
    int rotation;   // 0–3
    int xpos, ypos;
    static const shapeGrid shapes[7][4][4][4];
    void rotateLeft();
    void rotateRight();
};



#endif