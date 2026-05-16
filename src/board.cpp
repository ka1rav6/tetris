#include "../include/board.h"

enum class Fill {
    EMPTY, // 0
    FILLED, // 1 
    FIXED // 2
};


void Board::renderGrid(SDL_Renderer *rend){
    SDL_Rect block;

    for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLS; col++){
            if(grid[row][col]){
                block.x = col * TILE_WIDTH;
                block.y = row * TILE_HEIGHT;
                SDL_RenderFillRect(rend, &block);
            }
        }
    }
}