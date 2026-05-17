#include "../include/piece.h"
#include "../include/board.h"

static const std::map<char, shapeGrid> shapes = {
    {'I', {{
        {0,0,0,0},
        {1,1,1,1},
        {0,0,0,0},
        {0,0,0,0},
    }}},
    {'T', {{
        {0,1,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0},
    }}},
    {'J', {{
        {1,0,0,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0},
    }}},
    {'Z', {{
        {1,1,0,0},
        {0,1,1,0},
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
    {'L', {{
        {0,0,1,0},
        {1,1,1,0},
        {0,0,0,0},
        {0,0,0,0},
    }}}
};

Piece::Piece(){
    rotation = 0;
    xpos = 0;
    ypos = 0;
    lastFallTime = 0;
    fallDelay = 500;
}
Piece::~Piece(){}

void Piece::init(Board* board, char t){
    type = t;
    xpos = MIDDLE_X - 2;
    ypos = 0;
    rotation = 0;
    currentShape = shapes.at(type);
    lastFallTime = SDL_GetTicks();
}

bool Piece::canMove(Board* b, int newX, int newY){
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            if(currentShape[row][col]){
                int boardX = newX + col;
                int boardY = newY + row;
                if(boardX < 0 || boardX >= COLS || boardY >= ROWS)
                    return false;
                if(boardY >= 0 && b->grid[boardY][boardX] == FIXED)
                    return false;
            }
        }
    }
    return true;
}

bool Piece::canRotate(Board* b){
    shapeGrid rotated(4, std::vector<int>(4, 0));
    for(int row = 0; row < 4; row++)
        for(int col = 0; col < 4; col++)
            rotated[col][3 - row] = currentShape[row][col];
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            if(rotated[row][col]){
                int boardX = xpos + col;
                int boardY = ypos + row;
                if(boardX < 0 || boardX >= COLS || boardY >= ROWS)
                    return false;
                if(boardY >= 0 && b->grid[boardY][boardX] == FIXED)
                    return false;
            }
        }
    }
    return true;
}

void Piece::lockToBoard(Board* b){
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            if(currentShape[row][col]){
                int boardX = xpos + col;
                int boardY = ypos + row;
                if(boardX >= 0 && boardX < COLS && boardY >= 0 && boardY < ROWS)
                    b->grid[boardY][boardX] = FIXED;
            }
        }
    }
}

int Piece::getGhostY(Board* b){
    int ghostY = ypos;
    while(canMove(b, xpos, ghostY + 1))
        ghostY++;
    return ghostY;
}

void Piece::hardDrop(Board* b){
    ypos = getGhostY(b);
    lockToBoard(b);
    b->clearLines();
    b->generatePiece();
}

void Piece::handleEvent(SDL_Event &e, Board* board) {
    if(e.type == SDL_KEYDOWN) {
        switch(e.key.keysym.sym) {
            case SDLK_LEFT:
                if(canMove(board, xpos - 1, ypos))
                    xpos--;
                break;
            case SDLK_RIGHT:
                if(canMove(board, xpos + 1, ypos))
                    xpos++;
                break;
            case SDLK_DOWN:
                if(canMove(board, xpos, ypos + 1))
                    ypos++;
                break;
            case SDLK_UP:
                rotate(board);
                break;
            case SDLK_SPACE:
                hardDrop(board);
                break;
        }
    }
}

void Piece::update(Board* board){
    Uint32 now = SDL_GetTicks();
    if(now - lastFallTime >= fallDelay){
        if(canMove(board, xpos, ypos + 1)){
            ypos++;
        } else {
            lockToBoard(board);
            board->clearLines();
            board->generatePiece();
        }
        lastFallTime = now;
    }
}

void Piece::render(SDL_Renderer *r, Board* board){
    int ghostY = getGhostY(board);

    SDL_Rect block;
    block.w = CELL_SIZE - 1;
    block.h = CELL_SIZE - 1;

    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            if(currentShape[row][col]){
                if(ghostY != ypos){
                    block.x = BOARD_X + (xpos + col) * CELL_SIZE;
                    block.y = BOARD_Y + (ghostY + row) * CELL_SIZE;
                    SDL_SetRenderDrawColor(r, 60, 60, 60, 255);
                    SDL_RenderFillRect(r, &block);
                }
                block.x = BOARD_X + (xpos + col) * CELL_SIZE;
                block.y = BOARD_Y + (ypos + row) * CELL_SIZE;
                SDL_SetRenderDrawColor(r, 255, 255, 255, 255);
                SDL_RenderFillRect(r, &block);
                SDL_SetRenderDrawColor(r, 0, 0, 0, 255);
                SDL_RenderDrawRect(r, &block);
            }
        }
    }
}

void Piece::rotate(Board* b){
    if(canRotate(b))
        rotateRight();
}

void Piece::rotateRight() {
    shapeGrid rotated(4, std::vector<int>(4, 0));
    for(int row = 0; row < 4; row++)
        for(int col = 0; col < 4; col++)
            rotated[col][3 - row] = currentShape[row][col];
    currentShape = rotated;
    rotation = (rotation + 1) % 4;
}