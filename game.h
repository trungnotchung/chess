#ifndef _GAME_H
#define _GAME_H
#include "ltexture.h"
#include "lbutton.h"
#include "variable.h"
#include <iostream>

enum ChessPiece
{
    BLACK_PAWN = 0,
    WHITE_PAWN = 1,
    BLACK_BISHOP = 2,
    WHITE_BISHOP = 3,
    BLACK_KNIGHT = 4,
    WHITE_KNIGHT = 5,
    BLACK_ROOK = 6,
    WHITE_ROOK = 7,
    BLACK_QUEEN = 8,
    WHITE_QUEEN = 9,
    BLACK_KING = 10,
    WHITE_KING = 11,
    EMPTY = 12,
    TOTALPIECE = 13
};

class LGame
{
    public:

    LGame();

    ~LGame();

    bool init();

    void loadGame();

    void playGame();

    bool loadString(LTexture &curTexture, const std::string &path, const std::string &str);

    bool loadMedia(LTexture &curTexture, const std::string &path);

    void setCellPosition();

    void setCellType();

    void reset();

    private:

    SDL_Window *gWindow;

    SDL_Renderer *gRenderer;

    LTexture gCell[TOTALPIECE]; // pieces

    LTexture blackCell, whiteCell; // background

    SDL_Point topLeftCellPosition[SIZE][SIZE];
    
    int cellType[SIZE][SIZE];
};

#endif