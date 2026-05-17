#include "../include/board.h"
#include "../include/piece.h"

Board::Board(){}
Board::~Board(){}

void Board::initGrid(SDL_Renderer *rend){
    for(int row = 0; row < ROWS; row++) {
        for(int col = 0; col < COLS; col++)     
            grid[row][col] = EMPTY;
    }
    generatePiece();
}
void Board::renderGrid(SDL_Renderer *rend) {
    SDL_Rect block;
    block.w = WIN_WIDTH;
    block.h = WIN_HEIGHT;
    SDL_SetRenderDrawColor(rend, 255, 255, 255, 255);
    for(int row = 0; row < ROWS; row++) {
        for(int col = 0; col < COLS; col++) {
            if(grid[row][col] == FILLED) {
                block.x = col * WIN_WIDTH;
                block.y = row * WIN_HEIGHT;
                SDL_RenderFillRect(rend, &block);
            }
        }
    }
    currentPiece.render(rend, this);
}
void Board::generatePiece() {
    int num = rand() % 7;
    char type = shapes_Name[num];
    currentPiece.init(this, type);
}
void Board::handleEvent(SDL_Event &e) {
    currentPiece.handleEvent(e);
}
void Board::update() {
    currentPiece.update();
}