#include "bitboard.cpp"

class Engine {
    public:
        unsigned long long bitboard[64];

        Engine() {

        }

        int getValue(ChessPiece piece, int row, int col) {
            //placeholder
            return piece.getValue();
        }

        int getColorValue(Board b, Color c) {
            //placeholder
            int total = 0;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (b.board[i][j]->color == c) {
                        total += getValue(*b.board[i][j], i, j);
                    }
                }
            } 
            return total;
        }

        int evaluateBoard(BitBoard b) {
            if (b.whiteKingisCheckmated)  {
                return 1000;
            } else if (b.blackKingisCheckmated) {
                return -1000;
            } else {
                return getColorValue(b, White) - getColorValue(b, Black);
            }
        }

        int minimax(BitBoard b, int depth) {
            if (b.isGameOver || depth == 0) {
                return evaluateBoard(b);
            } 

            if (b.isWhiteTurn) {
                int best = -1000;

                for (std::string move : b.getLegalMoves(White)) {
                    int sr = std::stoi(move.substr(0, 1));
                    int sc = std::stoi(move.substr(1, 2));
                    int er = std::stoi(move.substr(2, 3));
                    int ec = std::stoi(move.substr(3, 4));

                    //deep copy board
                    Board newBoard = b;
                    newBoard.movePiece(sr, sc, er, ec);

                    int val = minimax(newBoard, depth - 1);
                    if (val > best) {
                        best = val;
                    }
                }
            } else {
                int best = 1000;

                for (std::string move : b.getLegalMoves(Black)) {
                    int sr = std::stoi(move.substr(0, 1));
                    int sc = std::stoi(move.substr(1, 2));
                    int er = std::stoi(move.substr(2, 3));
                    int ec = std::stoi(move.substr(3, 4));

                    //deep copy board
                    Board newBoard = b;
                    newBoard.movePiece(sr, sc, er, ec);

                    int val = minimax(newBoard, depth - 1);
                    if (val < best) {
                        best = val;
                    }
                }
            }
        }

};

