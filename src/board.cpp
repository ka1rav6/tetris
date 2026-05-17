#include "../include/board.h"
#include "../include/piece.h"

static const int CELL_W = WIN_WIDTH / COLS;
static const int CELL_H = WIN_HEIGHT / ROWS;

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
    block.w = CELL_W;
    block.h = CELL_H;
    for(int row = 0; row < ROWS; row++) {
        for(int col = 0; col < COLS; col++) {
            if(grid[row][col] == FIXED) {
                SDL_SetRenderDrawColor(rend, 128, 128, 128, 255);
                block.x = col * CELL_W;
                block.y = row * CELL_H;
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
    currentPiece.handleEvent(e, this);
}
void Board::update() {
    currentPiece.update(this);
}