#include "game.h"

int main()
{
    LGame chess;

    chess.loadGame();

    chess.playGame();

    std::cout << "No error found!\n";
    
    return 0;
}