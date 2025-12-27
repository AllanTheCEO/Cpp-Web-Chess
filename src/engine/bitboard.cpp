#include "board.cpp"

class BitBoard {
    public:
        uint64_t whitePawns;
        uint64_t blackPawns;
        uint64_t whiteKnights;
        uint64_t blackKnights;
        uint64_t whiteBishops;
        uint64_t blackBishops;
        uint64_t whiteRooks;
        uint64_t blackRooks;
        uint64_t whiteQueens;
        uint64_t blackQueens;
        uint64_t whiteKing;
        uint64_t blackKing;

        bool isGameOver = false;
        bool isGameDraw = false;
        bool isWhiteTurn = true;
        bool whiteKingisCheckmated = false;
        bool blackKingisCheckmated = false;
        bool isStalemate = false;
        int half_move_count = 0;
        int full_move_count = 0;
        std::string castlelingRights = "";
        int enPassantSquare = -1;


        BitBoard() {
            whitePawns = 0ULL;
            blackPawns = 0ULL;
            whiteKnights = 0ULL;
            blackKnights = 0ULL;
            whiteBishops = 0ULL;
            blackBishops = 0ULL;
            whiteRooks = 0ULL;
            blackRooks = 0ULL;
            whiteQueens = 0ULL;
            blackQueens = 0ULL;
            whiteKing = 0ULL;
            blackKing = 0ULL;
        }

        BitBoard(std::string fen) {
            std::stringstream ss(fen);
            std::string part;
            std::vector<std::string> parts;

            while (std::getline(ss, part, ' ')) {
                parts.push_back(part);
            }
            
            std::stringstream rowss(parts[0]);
            std::string row;
            std::vector<std::string> rows;

            while (std::getline(rowss, row, '/')) {
                rows.push_back(row);
            }

            for (int i = 8; i > rows.size(); i--) {
                int row = i - 1;
                for (int col = 0; col < 8; col++) {
                    int position = row * 8 + col;
                    uint64_t bit = 1ULL << position;
                    switch (rows[8 - i][col]) {
                        case 'P':
                            whitePawns |= bit;
                            break;
                        case 'p':
                            blackPawns |= bit;
                            break;
                        case 'N':
                            whiteKnights |= bit;
                            break;
                        case 'n':
                            blackKnights |= bit;
                            break;
                        case 'B':
                            whiteBishops |= bit;
                            break;
                        case 'b':
                            blackBishops |= bit;
                            break;
                        case 'R':
                            whiteRooks |= bit;
                            break;
                        case 'r':
                            blackRooks |= bit;
                            break;
                        case 'Q':
                            whiteQueens |= bit;
                            break;
                        case 'q':
                            blackQueens |= bit;
                            break;
                        case 'K':
                            whiteKing |= bit;
                            break;
                        case 'k':
                            blackKing |= bit;
                            break;
                    }
                }
            }
        }

};