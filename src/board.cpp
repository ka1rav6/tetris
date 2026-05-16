#include "../include/board.h"

enum Fill {
    EMPTY, // 0
    FILLED, // 1 
    FIXED // 2
};

Board::Board(){};
Board::~Board(){};

void Board::initGrid(SDL_Renderer *rend){

    for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLS; col++){
            grid[row][col] = EMPTY;
        }
    }

    renderGrid(rend);

}


void Board::renderGrid(SDL_Renderer *rend){
    SDL_Rect block;
    block.w = TILE_WIDTH;
    block.h = TILE_HEIGHT;
    SDL_SetRenderDrawColor(rend, 255,255,255,255);
    for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLS; col++){
            block.x = col * TILE_WIDTH;
            block.y = row * TILE_HEIGHT;
            SDL_RenderFillRect(rend, &block);
        }
    }
}