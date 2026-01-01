#include <iostream>
#include "src/engine/board.cpp"

int main() {
    Board chessBoard;
    chessBoard.initializeBoard();
    chessBoard.printBoard();
    std::string fen = chessBoard.getFEN();
    std::cout << fen << std::endl;
    return 0;
}