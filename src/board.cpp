#include "../include/board.h"
#include "../include/piece.h"

static void drawRect(SDL_Renderer *r, int x, int y, int w, int h, int rr, int g, int b){
    SDL_Rect rect = {x, y, w, h};
    SDL_SetRenderDrawColor(r, rr, g, b, 255);
    SDL_RenderFillRect(r, &rect);
}

static void drawDigit(SDL_Renderer *r, int digit, int x, int y, int scale){
    static const bool digits[10][5][3] = {
        {{1,1,1},{1,0,1},{1,0,1},{1,0,1},{1,1,1}},
        {{0,1,0},{1,1,0},{0,1,0},{0,1,0},{1,1,1}},
        {{1,1,1},{0,0,1},{1,1,1},{1,0,0},{1,1,1}},
        {{1,1,1},{0,0,1},{1,1,1},{0,0,1},{1,1,1}},
        {{1,0,1},{1,0,1},{1,1,1},{0,0,1},{0,0,1}},
        {{1,1,1},{1,0,0},{1,1,1},{0,0,1},{1,1,1}},
        {{1,1,1},{1,0,0},{1,1,1},{1,0,1},{1,1,1}},
        {{1,1,1},{0,0,1},{0,0,1},{0,0,1},{0,0,1}},
        {{1,1,1},{1,0,1},{1,1,1},{1,0,1},{1,1,1}},
        {{1,1,1},{1,0,1},{1,1,1},{0,0,1},{1,1,1}},
    };
    for(int row = 0; row < 5; row++)
        for(int col = 0; col < 3; col++)
            if(digits[digit][row][col])
                drawRect(r, x + col * scale, y + row * scale, scale - 1, scale - 1, 255, 255, 255);
}

static void drawNumber(SDL_Renderer *r, int num, int x, int y, int scale){
    std::string s = std::to_string(num);
    for(int i = 0; i < (int)s.size(); i++)
        drawDigit(r, s[i] - '0', x + i * (3 * scale + 2), y, scale);
}

Board::Board(){
    score = 0;
    level = 1;
    linesCleared = 0;
    gameOver = false;
    nextType = shapes_Name[rand() % 7];
}
Board::~Board(){}

void Board::initGrid(SDL_Renderer *rend){
    for(int row = 0; row < ROWS; row++)
        for(int col = 0; col < COLS; col++)
            grid[row][col] = EMPTY;
    generatePiece();
}

int Board::clearLines(){
    int cleared = 0;
    for(int row = ROWS - 1; row >= 0; row--){
        bool full = true;
        for(int col = 0; col < COLS; col++)
            if(grid[row][col] != FIXED){ full = false; break; }
        if(full){
            for(int r = row; r > 0; r--)
                for(int col = 0; col < COLS; col++)
                    grid[r][col] = grid[r-1][col];
            for(int col = 0; col < COLS; col++)
                grid[0][col] = EMPTY;
            cleared++;
            row++;
        }
    }
    if(cleared > 0){
        static const int pts[5] = {0, 100, 300, 500, 800};
        score += pts[cleared] * level;
        linesCleared += cleared;
        level = linesCleared / 10 + 1;
        int newDelay = 500 - (level - 1) * 40;
        if(newDelay < 80) newDelay = 80;
        currentPiece.fallDelay = newDelay;
    }
    return cleared;
}

void Board::generatePiece(){
    char type = nextType;
    nextType = shapes_Name[rand() % 7];
    currentPiece.init(this, type);
    if(!currentPiece.canMove(this, MIDDLE_X - 2, 0))
        gameOver = true;
}

void Board::renderGrid(SDL_Renderer *rend){
    SDL_Rect boardRect = {BOARD_X - 1, BOARD_Y - 1, COLS * CELL_SIZE + 2, ROWS * CELL_SIZE + 2};
    SDL_SetRenderDrawColor(rend, 80, 80, 80, 255);
    SDL_RenderDrawRect(rend, &boardRect);

    for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLS; col++){
            int x = BOARD_X + col * CELL_SIZE;
            int y = BOARD_Y + row * CELL_SIZE;
            if(grid[row][col] == FIXED){
                drawRect(rend, x, y, CELL_SIZE - 1, CELL_SIZE - 1, 180, 180, 180);
                SDL_Rect outline = {x, y, CELL_SIZE - 1, CELL_SIZE - 1};
                SDL_SetRenderDrawColor(rend, 100, 100, 100, 255);
                SDL_RenderDrawRect(rend, &outline);
            } else {
                SDL_Rect cell = {x, y, CELL_SIZE - 1, CELL_SIZE - 1};
                SDL_SetRenderDrawColor(rend, 15, 15, 15, 255);
                SDL_RenderFillRect(rend, &cell);
            }
        }
    }

    currentPiece.render(rend, this);

    int px = PANEL_X;
    int py = BOARD_Y;

    drawRect(rend, px, py, 120, 1, 80, 80, 80);
    py += 10;
    drawNumber(rend, score, px, py, 4);
    py += 30;
    drawRect(rend, px, py, 120, 1, 80, 80, 80);
    py += 10;
    drawNumber(rend, level, px, py, 4);
    py += 30;
    drawRect(rend, px, py, 120, 1, 80, 80, 80);
    py += 10;
    drawNumber(rend, linesCleared, px, py, 4);
    py += 40;

    drawRect(rend, px, py, 120, 1, 80, 80, 80);
    py += 10;
    shapeGrid ns = shapes_Name[0] == nextType ? currentPiece.getShape() : currentPiece.getShape();
    Piece preview;
    preview.init(nullptr, nextType);
    shapeGrid ps = preview.getShape();
    for(int row = 0; row < 4; row++){
        for(int col = 0; col < 4; col++){
            if(ps[row][col]){
                SDL_Rect b = {px + col * (CELL_SIZE - 4), py + row * (CELL_SIZE - 4), CELL_SIZE - 5, CELL_SIZE - 5};
                SDL_SetRenderDrawColor(rend, 200, 200, 200, 255);
                SDL_RenderFillRect(rend, &b);
            }
        }
    }

    if(gameOver){
        SDL_Rect overlay = {BOARD_X, BOARD_Y, COLS * CELL_SIZE, ROWS * CELL_SIZE};
        SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(rend, 0, 0, 0, 180);
        SDL_RenderFillRect(rend, &overlay);
        SDL_SetRenderDrawBlendMode(rend, SDL_BLENDMODE_NONE);
        int gox = BOARD_X + 10;
        int goy = BOARD_Y + ROWS * CELL_SIZE / 2 - 30;
        int digits_go[] = {6, 0, 10, 15, 10, 22, 5};
        int nums[] = {1,0};
        drawNumber(rend, score, gox, goy + 40, 4);
        (void)digits_go; (void)nums;
    }
}

void Board::handleEvent(SDL_Event &e){
    if(gameOver){
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r){
            for(int row = 0; row < ROWS; row++)
                for(int col = 0; col < COLS; col++)
                    grid[row][col] = EMPTY;
            score = 0;
            level = 1;
            linesCleared = 0;
            gameOver = false;
            nextType = shapes_Name[rand() % 7];
            generatePiece();
        }
        return;
    }
    currentPiece.handleEvent(e, this);
}

void Board::update(){
    if(gameOver) return;
    currentPiece.update(this);
}