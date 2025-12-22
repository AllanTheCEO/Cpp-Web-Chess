#pragma once
#include <string>
#include <functional>
class Board;  // forward declare; binder won't see the real definition

class WasmBoard {
public:
  WasmBoard();
  ~WasmBoard();

  void initializeBoard();
  char getPiece(int r, int c) const;   // adjust to your engine API
  void movePiece(int startRow, int startCol, int endRow, int endCol);
  void castle(int kingRow, int kingCol, int rookRow, int rookCol);
  std::string consumeGameOver();
  bool parseFEN(std::string fen);
  std::string consumePendingPromotion();
  void promotePawn(int row, int col, char newPiece);
  void finalizeAfterPromotion(std::string color);
  std::string getFEN();
  
private:
  Board* p_;
  std::function<void(std::string)> onGameOver_; 
};
