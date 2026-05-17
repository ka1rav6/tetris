#include "../include/piece.h"
#include "../include/board.h"

static const std::map<char, shapeGrid> shapes ={
    {'I' , {{
        {0,0,0,1},
        {0,0,0,1},
        {0,0,0,1},
        {0,0,0,1},
    }}},
    {'T', {{
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0},
    }}},
    {'J', {{
        {0,1,1,1},
        {0,0,0,1},
        {0,0,0,0},
        {0,0,0,0},
    }}},
    {'Z', {{
        {0,1,1,0},
        {0,0,1,1},
        {0,0,0,0},
        {0,0,0,0},
    }}},
    {'O', {{
        {0,1,1,0},
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0},
    }}},
    {'S', {{
        {0,1,1,0},
        {1,1,0,0},
        {0,0,0,0},
        {0,0,0,0},
    }}},
    {'L' , {{
        {1,0,0,0},
        {1,0,0,0},
        {1,1,0,0},
        {0,0,0,0},
    }}}
};
Piece::Piece(){
    rotation = 0;
    xpos = 0;
    ypos = 0;
}
Piece::~Piece(){}
void Piece::init(Board* board, char t){
    type = t;
    xpos = MIDDLE_X - 2;
    ypos = 0;
    rotation = rand() % 4;
    for(int i = 0; i < rotation; i++)
        rotateRight();
    PlaceOnBoard(board);
}

void Piece::PlaceOnBoard(Board* b){
    shapeGrid shape = shapes.at(type);
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++) {
            if(shape[row][col]) {
                int boardX = xpos + col;
                int boardY = ypos + row;
                if(boardX >= 0 && boardX < COLS && boardY >= 0 && boardY < ROWS) {
                    b->grid[boardY][boardX] = FILLED;
                }
            }
        }
    }
}
void Piece::handleEvent(SDL_Event &e) {
    if(e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
            case SDLK_LEFT:
                xpos--;
                break;
            case SDLK_RIGHT:
                xpos++;
                break;
            case SDLK_DOWN:
                ypos++;
                break;
            case SDLK_UP:
                rotate();
                break;
        }
    }
}
void Piece::update(){
    ypos++;
}
void Piece::render(SDL_Renderer *r, Board* board){
    shapeGrid shape = shapes.at(type);
    SDL_Rect block;
    block.w = WIN_WIDTH;
    block.h = WIN_HEIGHT;
    SDL_SetRenderDrawColor(r, 255,255,255,255);
    for(int row = 0; row < 4; row++) {
        for(int col = 0; col < 4; col++) {
            if(shape[row][col]) {
                block.x = (xpos + col) * WIN_WIDTH;
                block.y = (ypos + row) * WIN_HEIGHT;
                SDL_RenderFillRect(r, &block);
            }
        }
    }
}
void Piece::rotate(){
    rotateRight();
}
void Piece::rotateRight() {
    shapeGrid shape = shapes.at(type);
    shapeGrid rotated{};
    for(int row = 0; row < 4; row++) {
        for(int col = 0; col < 4; col++) {
            rotated[col][3 - row] = shape[row][col];
        }
    }
    const_cast<shapeGrid&>(shapes.at(type)) = rotated;
    rotation = (rotation + 1) % 4;
}
void Piece::rotateLeft() {
    shapeGrid shape = shapes.at(type);
    shapeGrid rotated{};
    for(int row = 0; row < 4; row++) {
        for(int col = 0; col < 4; col++) {
            rotated[3 - col][row] = shape[row][col];
        }
    }
    const_cast<shapeGrid&>(shapes.at(type)) = rotated;
    rotation--;
    if(rotation < 0)
        rotation = 3;
}