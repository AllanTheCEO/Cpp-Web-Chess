#include "wasm_api.h"
#include "../engine/board.h"
#include <utility>

WasmBoard::WasmBoard() : p_(new Board()) {}
WasmBoard::~WasmBoard() { delete p_; }

void WasmBoard::initializeBoard() { p_->initializeBoard(); }
char WasmBoard::getPiece(int r, int c) const { return p_->getPiece(r, c); }
void WasmBoard::movePiece(int startRow, int startCol, int endRow, int endCol)
 {p_->movePiece(startRow, startCol, endRow, endCol);} 
void WasmBoard::castle(int kingRow, int kingCol, int rookRow, int rookCol) 
{(p_->castle(kingRow, kingCol, rookRow, rookCol));}
std::string WasmBoard::consumeGameOver() { return p_->consumeGameOver(); }
bool WasmBoard::parseFEN(std::string fen) { return p_->parseFEN(fen); }
std::string WasmBoard::consumePendingPromotion() 
{return "";}
void WasmBoard::promotePawn(int row, int col, char newPiece)
{p_->promotePawn(row, col, newPiece); }
void WasmBoard::finalizeAfterPromotion(std::string color)
{p_->finalizeAfterPromotion(color); }
std::string WasmBoard::getFEN() {return p_->getFEN();}

