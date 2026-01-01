#include "bitboard.cpp"
#include <ctime>

class Engine {
    public:
        unsigned long long bitboard[64];

        Engine() {

        }

        std::array<std::array<double, 8>, 8> getPieceSquareTable(Piece piece) {
            switch (piece) {
                case PAWN:
                    return std::array<std::array<double, 8>, 8>{{
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {5, 5, 5, 5, 5, 5, 5, 5},
                        {1, 1, 2, 3, 3, 2, 1, 1},
                        {0.5, 0.7, 0.1, 2.7, 2.7, 0.1, 0.7, 0.5},
                        {0, 0, 0.3, 2.5, 2.5, 0.3, 0, 0},
                        {0.5, -0.5, -1, 0, 0, -1, -0.5, 0.5},
                        {.5, 1, 1, -2.5, -2.5, 1, 1, 0.5},
                        {0, 0, 0, 0, 0, 0, 0, 0}
                    }};
                case BISHOP:
                    return std::array<std::array<double, 8>, 8>{{
                        {-2, -1, -1, -1, -1, -1, -1, -2},
                        {-1, 0, 0, 0, 0, 0, 0, -1},
                        {-1, 0, 0.5, 1, 1, 0.5, 0, -1},
                        {-1, 0.5, 0.5, 1, 1, 0.5, 0.5, -1},
                        {-1, 0, 1, 1, 1, 1, 0, -1},
                        {-1, 1, 1, 1, 1, 1, 1, -1},
                        {-1, 0.5, 0, 0, 0, 0, 0.5, -1},
                        {-2, -1, -1, -1, -1, -1, -1, -2}
                    }};
                case KNIGHT:
                    return std::array<std::array<double, 8>, 8>{{
                        {-5, -4, -3, -3, -3, -3, -4, -5},
                        {-4, -2, 0, 0, 0, 0, -2, -4},
                        {-3, 0.5, 1, 1.5, 1.5, 1, 0.5, -3},
                        {-3, 0, 1.5, 2, 2, 1.5, 0, -3},
                        {-3, 0.75, 1.5, 2, 2, 1.5, 0.75, -3},
                        {-3, 0.5, 1, 1.5, 1.5, 1, 0.5, -3},
                        {-4, -2, 0, 0.5, 0.5, 0, -2, -4},
                        {-5, -4, -3, -3, -3, -3, -4, -5}
                    }};
                case KING:
                    //early-mid game
                    return std::array<std::array<double, 8>, 8>{{
                        {-3, -4, -4, -5, -5, -4, -4, -3},
                        {-3, -4, -4, -5, -5, -4, -4, -3},
                        {-3, -4, -4, -5, -5, -4, -4, -3},
                        {-3, -4, -4, -5, -5, -4, -4, -3},
                        {-2, -3, -3, -4, -4, -3, -3, -2},
                        {-1, -2, -2, -2, -2, -2, -2, -1},
                        {2, 2, 0, 0, 0, 0, 2, 2},
                        {2, 3, 1, 0, 0, 1, 3, 2}
                    }};

                    //late game
                    // return std::array<std::array<double, 8>, 8>{{
                    //     {-5, -4, -3, -2, -2, -3, -4, -5},
                    //     {-3, -2, -1, 0, 0, -1, -2, -3},
                    //     {-3, -1, 2, 3, 3, 2, -1, -3},
                    //     {-3, -1, 3, 4, 4, 3, -1, -3},
                    //     {-3, -1, 3, 4, 4, 3, -1, -3},
                    //     {-3, -1, 2, 3, 3, 2, -1, -3},
                    //     {-3, -3, 0, 0, 0, 0, -3, -3},
                    //     {-5, -3, -3, -3, -3, -3, -3, -5}
                    // }};
                default:
                    return std::array<std::array<double, 8>, 8>{{
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0},
                        {0, 0, 0, 0, 0, 0, 0, 0}
                    }};
            }
        }
        

        double getValue(ChessPiece& piece, int row, int col) {
            //placeholder
            if (piece.color == White) {
                return piece.getValue() + getPieceSquareTable(piece.piece)[7 - row][col];
            } else if (piece.color == Black) {
                return 1 * (piece.getValue() + getPieceSquareTable(piece.piece)[row][col]);
            } else {
                return 0.0;
            }
        }

        double getColorValue(Board b, Color c) {
            //placeholder
            double total = 0.0;
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (b.board[i][j]->color == c) {
                        total += getValue(*b.board[i][j], i, j);
                    }
                }
            } 
            return total;
        }

        double evaluateBoard(Board b) {
            if (b.whiteKingisCheckmated)  {
                return -1000;
            } else if (b.blackKingisCheckmated) {
                return 1000;
            } else if (b.isGameDraw) {
                return 0;
            } else {
                return getColorValue(b, White) - getColorValue(b, Black);
            }
        }

        std::tuple<double, std::string> minimax(Board b, int depth) {
            if (b.isGameOver || depth == 0) {
                return std::make_tuple(evaluateBoard(b), "");
            } 

            double best = 0;
            std::string move = "";

            if (b.isWhiteTurn) {
                best = -1000;

                for (std::string m : b.getLegalMoves(White)) {

                    //deep copy board
                    Board newBoard = b;
                    Board postMove = engineMove(newBoard, m, White);
                    

                    auto result = minimax(postMove, depth - 1);
                    if (std::get<0>(result) > best) {
                        best = std::get<0>(result);
                        move = m;
                    }
                }
            } else {
                best = 1000;

                for (std::string m : b.getLegalMoves(Black)) {


                    //deep copy board
                    Board newBoard = b;
                    Board postMove = engineMove(newBoard, m, Black);

                    auto result = minimax(postMove, depth - 1);
                    if (std::get<0>(result) < best) {
                        best = std::get<0>(result);
                        move = m;
                    }
                }
            }

            //b.printBoard();
            return std::make_tuple(best, move);
        }

        Board engineMove(Board &b, std::string m, Color c) {
            if (c != White && c != Black) {
                return b;
            }
            if (c == White) {
                if (m == "O-O-W") {
                    b.castle(0, 4, 0, 7); 
                } else if (m == "O-O-O-W") {
                    b.castle(0, 4, 0, 0);
                } else if (m.size() == 5) {
                    char promo = m[4];
                    int sr = std::stoi(m.substr(0, 1));
                    int sc = std::stoi(m.substr(1, 1));
                    int er = std::stoi(m.substr(2, 1));
                    int ec = std::stoi(m.substr(3, 1));
                    b.movePiece(sr, sc, er, ec);
                    b.promotePawn(er, ec, promo);
                } else {
                    int sr = std::stoi(m.substr(0, 1));
                    int sc = std::stoi(m.substr(1, 1));
                    int er = std::stoi(m.substr(2, 1));
                    int ec = std::stoi(m.substr(3, 1));
                    b.movePiece(sr, sc, er, ec);
                }
            } else if (c == Black) {
                if (m == "O-O-B") {
                    b.castle(7, 4, 7, 7); 
                } else if (m == "O-O-O-B") {
                    b.castle(7, 4, 7, 0);
                } else if (m.size() == 5) {
                    int sr = std::stoi(m.substr(0, 1));
                    int sc = std::stoi(m.substr(1, 1));
                    int er = std::stoi(m.substr(2, 1));
                    int ec = std::stoi(m.substr(3, 1));
                    char promo = m[4];
                    b.movePiece(sr, sc, er, ec);
                    b.promotePawn(er, ec, promo);
                } else {
                    int sr = std::stoi(m.substr(0, 1));
                    int sc = std::stoi(m.substr(1, 1));
                    int er = std::stoi(m.substr(2, 1));
                    int ec = std::stoi(m.substr(3, 1));
                    b.movePiece(sr, sc, er, ec);
                }

            }
            return b;
        }
};

int main() {
    int depth = 2;
    clock_t start = clock();
    Board b = Board();
    b.initializeBoard();
    Engine engine = Engine();
    std::tuple<double, std::string> result = engine.minimax(b, depth);
    std::cout << "Best move: " << std::get<1>(result) << ", Best value: " << std::get<0>(result);
    std::cout << std::endl;
    engine.engineMove(b, std::get<1>(result), b.isWhiteTurn ? White : Black);
    b.printBoard();

    std::tuple<double, std::string> result2 = engine.minimax(b, depth);
    std::cout << "Best move: " << std::get<1>(result2) << ", Best value: " << std::get<0>(result2);
    std::cout << std::endl;
    engine.engineMove(b, std::get<1>(result2), b.isWhiteTurn ? White : Black);
    b.printBoard();
    clock_t end = clock();
    double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    std::cout << "Execution time: " << elapsed_time << " seconds" << std::endl;

    return 0;
}

