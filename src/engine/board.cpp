#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>
#include <cmath>
#include <functional>
#include <sstream>


enum Piece {
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING,
    EMPTY
};

enum Color {
    White,
    Black,
    None
};

struct ChessPiece {
    Piece piece;
    Color color;
    const char* symbol;
    int row;
    int col;
    bool enPassantSquare = false; 
    virtual bool returnCastlingRights() const { 
        return false; 
    }


    std::unordered_map<Piece, const char> pieceNames = {
        {PAWN, 'P'},
        {KNIGHT, 'N'},
        {BISHOP, 'B'},
        {ROOK, 'R'},
        {QUEEN, 'Q'},
        {KING, 'K'},
    };

    std::unordered_map<Piece, const char*> whitePieceSymbols = {
        {PAWN, "♙"},
        {KNIGHT, "♘"},
        {BISHOP, "♗"},
        {ROOK, "♖"},
        {QUEEN, "♕"},
        {KING, "♔"}
    };

    std::unordered_map<Piece, const char*> blackPieceSymbols = {
        {PAWN, "♟"},
        {KNIGHT, "♞"},
        {BISHOP, "♝"},
        {ROOK, "♜"},
        {QUEEN, "♛"},
        {KING, "♚"}
    };
    
    ChessPiece(Piece p, Color c, int x, int y) : piece(p), color(c), row(x), col(y) {
        symbol = "  ";
        if (c == White) {
            symbol = whitePieceSymbols[p];
        } else if (c == Black) {
            symbol = blackPieceSymbols[p];
        } else {
            symbol = "  ";
        }
    }

    std::string returnSymbol() {
        if (color == White) {
            return whitePieceSymbols[piece];
        } else if (color == Black) {
            return blackPieceSymbols[piece];
        } else {
            return " ";
        }
    }

    virtual bool isNormalMove(int endRow, int endColumn) {
        return true;
    }

    bool isdiagonal(int endRow, int endColumn) {
        if (abs(endRow - this->row) == abs(endColumn - this->col)) {
            return true;
        }
        return false;
    }

    bool isinRow(int endRow, int endColumn) {
        if (this->col != endColumn && this->row == endRow) {
            return true;
        }
        return false;
    }

    bool isinColumn(int endRow, int endColumn) {
        if (this->row != endRow && this->col == endColumn) {
            return true;
        }
        return false;
    }

    virtual bool canCapture(int endRow, int endColumn) {

        return true;
    }

    virtual void move(int endRow, int endColumn) {
    }

    virtual int getValue() {
        return 0;
    }
};

struct King : public ChessPiece {
    bool hasCastlingRights = true;
    bool isInCheck = false;
    bool isInCheckmate = false;
    using ChessPiece::ChessPiece;   

    virtual bool returnCastlingRights() const { 
        return hasCastlingRights; 
    }

    bool isNormalMove(int endRow, int endColumn) {
        if (abs(endRow - this->row) <= 1 && abs(endColumn - this->col) <= 1) {
                return true;
        } else {
            return false;
        }
    }

    virtual void move(int endRow, int endColumn) {
        this->row = endRow;
        this->col = endColumn;
        this->hasCastlingRights = false;
    }
};

struct Rook : public ChessPiece {
    bool hasCastlingRights = true;
    using ChessPiece::ChessPiece;

    virtual bool returnCastlingRights() const { 
        return hasCastlingRights; 
    }
    bool isNormalMove(int endRow, int endColumn) {
        if (isinRow(endRow, endColumn) || isinColumn(endRow, endColumn)) {
            return true;
        } else {
            return false;
        }
    }

    virtual void move(int endRow, int endColumn) {
        this->row = endRow;
        this->col = endColumn;
        this->hasCastlingRights = false;
    }

    virtual int getValue() {
        return 5;
    }

};

struct Bishop : public ChessPiece {
    using ChessPiece::ChessPiece;

    bool isNormalMove(int endRow, int endColumn) {
        if (isdiagonal(endRow, endColumn)) {
            return true;
        } else {
            return false;
        }
    }

    virtual void move(int endRow, int endColumn) {
        this->row = endRow;
        this->col = endColumn;
    }

    virtual int getValue() {
        return 3;
    }
};

struct Pawn : public ChessPiece {
    using ChessPiece::ChessPiece;

    Pawn(Piece piece, Color c, int x, int y) : ChessPiece(piece, c, x, y) {}

    bool isNormalMove(int endRow, int endColumn) override {
        if (color == White) {
            if (this->row == 1 && endRow == this->row + 2 && endColumn == this->col) {
                return true;
            }
            else if (endColumn == this->col && endRow == this->row + 1) {
                return true;
            } else {
                return false;
            }
        } else if (color == Black) {
            if (this->row == 6 && endRow == this->row - 2 && endColumn == this->col) {
                return true;
            }
            else if (endRow == this->row - 1 && endColumn == this->col) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    bool canCapture(int endRow, int endColumn) override {
        if (this->color == White &&
            (endRow == this->row + 1 &&
            abs(endColumn - this->col) == 1)) {
            return true;
        } else if (this->color == Black &&
            (endRow == this->row - 1 &&
            abs(endColumn - this->col) == 1)) {
            return true;
        }
        return false;
    }

    virtual void move(int endRow, int endColumn) override{
        this->row = endRow;
        this->col = endColumn;
    }

    bool checkPromotion() {
        if (color == White && this->row == 7) {
            return true;
        } else if (color == Black && this->row == 0) {
            return true;
        } else {
            return false;
        }
    }

    virtual int getValue() override {
        return 1;
    }

};

struct Knight : public ChessPiece {
    using ChessPiece::ChessPiece;

    bool isNormalMove(int endRow, int endColumn) {
        if ((abs(endRow - this->row) == 2 && abs(endColumn - this->col) == 1) ||
            (abs(endRow - this->row) == 1 && abs(endColumn - this->col) == 2)) {
            return true;
        } else {
            return false;
        }
    }

    virtual void move(int endRow, int endColumn) {
        this->row = endRow;
        this->col = endColumn;
    }

    virtual int getValue() {
        return 3;
    }

};

struct Queen : public ChessPiece {
    using ChessPiece::ChessPiece;

    bool isNormalMove(int endRow, int endColumn) {
        if(isdiagonal(endRow, endColumn) ||
            isinRow(endRow, endColumn) ||
            isinColumn(endRow, endColumn)) {
            return true;
        } else {
            return false;
        }
    }

    virtual void move(int endRow, int endColumn) {
        this->row = endRow;
        this->col = endColumn;
    }

    virtual int getValue() {
        return 9;
    }

};

struct Empty : public ChessPiece {
    bool enPassantSquare = false;
    using ChessPiece::ChessPiece;

    Empty() : ChessPiece(Piece::EMPTY, Color::None, row, col) {}

    bool isNormalMove(int endRow, int endColumn) {
        return false;
    }

};

class Board {
    public:
        //variables for controlling game action
        ChessPiece* board[8][8];
        bool isGameOver = false;
        bool isGameDraw = false;
        bool isWhiteTurn = true;

        //variables for game over conditions
        bool whiteKingisCheckmated = false;
        bool blackKingisCheckmated = false;
        bool isStalemate = false; //No legal moves, 50 move rule, 3rd same position, insufficient material
        std::unordered_map<std::string, int> positionCount = {}; //Check for threefold repetition 
        int half_move_count = 0; //If 50 moves without a capture, game is drawn
        int full_move_count = 0;
        std::string gameOverMessage = "";


        //Handle piece values and captured pieces
        std::vector<char> whiteCapturedPieces;
        std::vector<char> blackCapturedPieces;

        Board() {

        }

        //Constructor for new board with fen string
        Board(std::string) {

        }

        ~Board() {
            
        }

        void initializeBoard() {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    board[i][j] = new ChessPiece(EMPTY, None, i, j); 
                }
            }
            for (int i = 0; i < 8; i++) {
                for (int j = 2; j < 6; j++) {
                        board[i][j] = new Empty(EMPTY, None, i, j); 
                }
            }
            for (int j = 0; j < 8; j++) {
                board[1][j] = new Pawn(PAWN, White, 1, j); 
                board[6][j] = new Pawn(PAWN, Black, 6, j); 
            }
            board[0][0] = new Rook(ROOK, White, 0, 0);
            board[0][7] = new Rook(ROOK, White, 0, 7);
            board[0][1] = new Knight(KNIGHT, White, 0, 1);
            board[0][6] = new Knight(KNIGHT, White, 0, 6);
            board[0][2] = new Bishop(BISHOP, White, 0, 2);
            board[0][5] = new Bishop(BISHOP, White, 0, 5);
            board[0][3] = new Queen(QUEEN, White, 0, 3);
            board[0][4] = new King(KING, White, 0, 4);
            board[7][0] = new Rook(ROOK, Black, 7, 0);
            board[7][7] = new Rook(ROOK, Black, 7, 7);
            board[7][1] = new Knight(KNIGHT, Black, 7, 1);
            board[7][6] = new Knight(KNIGHT, Black, 7, 6);
            board[7][2] = new Bishop(BISHOP, Black, 7, 2);
            board[7][5] = new Bishop(BISHOP, Black, 7, 5);
            board[7][3] = new Queen(QUEEN, Black, 7, 3);
            board[7][4] = new King(KING, Black, 7, 4);
        }

        void printBoard() {
            for (int i = 7; i >= 0; i--) {
                for (int j = 0; j < 8; j++) {
                    std::cout << "[" << board[i][j]->returnSymbol() << " ]";
                }
                std::cout << std::endl;
            }
        }
        
        char getPiece(int row, int col) {
            if (board[row][col]->piece == EMPTY) {
                return ' ';
            }
            char pieceName = board[row][col]->pieceNames[board[row][col]->piece];
            if(board[row][col]->color == White){
                return pieceName;
            } else {
                return std::tolower(pieceName);
            }
            
        }

        std::string getPosition() {
            std::string fen;
            for(int i = 7; i >= 0; i--) {
                int emptyCount = 0;
                for(int j = 0; j < 8; j++) {
                    if(board[i][j]->piece == EMPTY) {
                        emptyCount++;
                    } else {
                        if (emptyCount > 0) {
                            fen.push_back('0' + emptyCount);
                            emptyCount = 0;
                        }
                        if(board[i][j]->color == White) {
                            fen.push_back(board[i][j]->pieceNames[board[i][j]->piece]);
                        } else if (board[i][j]->color == Black) {
                            fen.push_back(tolower(board[i][j]->pieceNames[board[i][j]->piece]));
                        }
                    }
                }
                if (emptyCount > 0) {
                    fen.push_back('0' + emptyCount);
                }
                if (i != 0) {
                    fen.push_back('/');
                }
            }
            return fen;
        }

        std::string getFEN() {
            std::string fen;
            fen.append(getPosition());

            if (isWhiteTurn) {
                fen.append(" w");
            } else {
                fen.append(" b");
            }

            //castling rights
            fen.push_back(' ');
            std::string castlingRights = "";
            if(board[0][4]->returnCastlingRights() && board[0][7]->returnCastlingRights()) {
                castlingRights.push_back('K');
            } 
            if (board[0][4]->returnCastlingRights() && board[0][0]->returnCastlingRights()) {
                castlingRights.push_back('Q');
            } 
            if (board[7][4]->returnCastlingRights() && board[7][7]->returnCastlingRights()) {
                castlingRights.push_back('k');
            } 
            if (board[7][4]->returnCastlingRights() && board[7][0]->returnCastlingRights()) {
                castlingRights.push_back('q');
            } 
            if (castlingRights.empty()) {
                fen.push_back('-');
            } else {
                fen.append(castlingRights);
            }

            

            //enpassant available
            fen.push_back(' ');
            bool isEnPassantSquare = false;
            for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    if(board[i][j]->enPassantSquare == true) {
                        fen.push_back('a' + j);
                        fen.push_back('1' + i);
                        isEnPassantSquare = true;
                        break;
                    }
                }
            }
            if (!isEnPassantSquare) {
                fen.push_back('-');
            }

            //halfmove clock and fullmove number
            fen.push_back(' ');
            fen.append(std::to_string(half_move_count));
            fen.push_back(' ');
            fen.append(std::to_string((full_move_count / 2) + 1));
            return fen;
        }

        bool isValidCastlingRights(const std::string& s) {
            if (s == "-") return true;

            bool seenK=false, seenQ=false, seenk=false, seenq=false;

            for (char c : s) {
                switch (c) {
                    case 'K': if (seenK) return false; seenK = true; break;
                    case 'Q': if (seenQ) return false; seenQ = true; break;
                    case 'k': if (seenk) return false; seenk = true; break;
                    case 'q': if (seenq) return false; seenq = true; break;
                    default: return false; // invalid char
                }
            }

            return true;
        }


        bool parseFEN(std::string fen) {
            Board newBoard = Board();

            std::stringstream ss(fen);
            std::string part;
            std::vector<std::string> parts;
            while (std::getline(ss, part, ' ')) {
                parts.push_back(part);
            }

            if (parts.size() != 6) {
                return false;
            }

            std::stringstream rowss(parts[0]);
            std::string row;
            std::vector<std::string> rows;

            while (std::getline(rowss, row, '/')) {
                rows.push_back(row);
            }
            if (rows.size() != 8) {
                return false;
            }

            for (int i = 0; i < 8; i++) {
                int col = 0;
                for (char c : rows[7 - i]) {
                    if (isdigit(c)) {
                        int emptySquares = c - '0';
                        for (int j = 0; j < emptySquares; j++) {
                            newBoard.board[i][col] = new Empty(EMPTY, None, i, col);
                            col++;
                        }
                    } else {
                        Color color = isupper(c) ? White : Black;
                        Piece piece;
                        switch (tolower(c)) {
                            case 'p': piece = PAWN; break;
                            case 'n': piece = KNIGHT; break;
                            case 'b': piece = BISHOP; break;
                            case 'r': piece = ROOK; break;
                            case 'q': piece = QUEEN; break;
                            case 'k': piece = KING; break;
                            default: return false;
                        }
                        switch (piece) {
                            case PAWN:
                                newBoard.board[i][col] = new Pawn(piece, color, i, col);
                                break;
                            case KNIGHT:
                                newBoard.board[i][col] = new Knight(piece, color, i, col);
                                break;
                            case BISHOP:
                                newBoard.board[i][col] = new Bishop(piece, color, i, col);
                                break;
                            case ROOK:
                                newBoard.board[i][col] = new Rook(piece, color, i, col);
                                break;
                            case QUEEN:
                                newBoard.board[i][col] = new Queen(piece, color, i, col);
                                break;
                            case KING:
                                newBoard.board[i][col] = new King(piece, color, i, col);
                                break;
                            default:
                                break;
                        }
                        col++;
                    }
                }
                if (col != 8) {
                    return false;
                }
            }

            if (parts[1] != "w" && parts[1] != "b") {
                return false;
            }
            if (parts[1] == "w") {
                newBoard.isWhiteTurn = true;
            } else {
                newBoard.isWhiteTurn = false;
            }

            //castling rights
            if (parts[2].length() != '-' && !isValidCastlingRights(parts[2])) {
                return false;
            }
            for (char c : parts[2]) {
                switch (c) {
                    case 'K':
                        if (newBoard.board[0][4]->piece != KING || newBoard.board[0][4]->color != White ||
                            newBoard.board[0][7]->piece != ROOK || newBoard.board[0][7]->color != White) {
                            return false;
                        } else {
                            dynamic_cast<struct King*>(newBoard.board[0][4])->hasCastlingRights = true;
                            dynamic_cast<struct Rook*>(newBoard.board[0][7])->hasCastlingRights = true;
                        }
                        break;
                    case 'Q':
                        if (newBoard.board[0][4]->piece != KING || newBoard.board[0][4]->color != White ||
                            newBoard.board[0][0]->piece != ROOK || newBoard.board[0][0]->color != White) {
                            return false;
                        } else {
                            dynamic_cast<struct King*>(newBoard.board[0][4])->hasCastlingRights = true;
                            dynamic_cast<struct Rook*>(newBoard.board[0][0])->hasCastlingRights = true;
                        }
                        // White queenside
                        break;
                    case 'k':
                        if (newBoard.board[7][4]->piece != KING || newBoard.board[7][4]->color != Black ||
                            newBoard.board[7][7]->piece != ROOK || newBoard.board[7][7]->color != Black) {
                            return false;
                        } else {
                            dynamic_cast<struct King*>(newBoard.board[7][4])->hasCastlingRights = true;
                            dynamic_cast<struct Rook*>(newBoard.board[7][7])->hasCastlingRights = true;
                        }
                        // Black kingside
                        break;
                    case 'q':
                        if (newBoard.board[7][4]->piece != KING || newBoard.board[7][4]->color != Black ||
                            newBoard.board[7][0]->piece != ROOK || newBoard.board[7][0]->color != Black) {
                            return false;
                        } else {
                            dynamic_cast<struct King*>(newBoard.board[7][4])->hasCastlingRights = true;
                            dynamic_cast<struct Rook*>(newBoard.board[7][0])->hasCastlingRights = true;
                        }
                        // Black queenside
                        break;
                    case '-':
                        // No castling rights
                        break;
                }
            }

            //enpassant square
            if (parts[3].length() != 2 && parts[3] != "-") {
                return false;
            } else {
                if (parts[3] != "-") {
                    char file = parts[3][0];
                    char rank = parts[3][1];
                    if (file < 'a' || file > 'h' || (rank != '3' && rank != '6')) {
                        return false;
                    }
                    int col = file - 'a';
                    int row = rank - '1';
                    newBoard.board[row][col]->enPassantSquare = true;
                }
            }

            //halfmove clock
            try {
                newBoard.half_move_count = std::stoi(parts[4]);
            } catch (...) {
                return false;
            }
            if (newBoard.half_move_count < 0) {
                return false;
            }

            //fullmove number
            try {
                newBoard.full_move_count = std::stoi(parts[5]);
            } catch (...) {
                return false;
            }
            if (newBoard.full_move_count <= 0) {
                return false;
            }

            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    delete board[i][j];
                    board[i][j] = newBoard.board[i][j];
                    newBoard.board[i][j] = nullptr;
                } 
            }

            isWhiteTurn = newBoard.isWhiteTurn;
            half_move_count = newBoard.half_move_count;
            full_move_count = newBoard.full_move_count;
            positionCount = newBoard.positionCount;
            return true;
        }
        
        void gameOver() {
            isGameOver = true;
            if(whiteKingisCheckmated) {
                gameOverMessage = "Black Checkmate";
            } else if (blackKingisCheckmated) {
                gameOverMessage = "White Checkmate";
            } else if(isStalemate) {
                gameOverMessage = "Stalemate";
            } else if(positionCount[getPosition()] >= 3) {
                gameOverMessage = "Draw by Threefold Repetition";
            } else if(half_move_count >= 100) {
                gameOverMessage = "Draw by 50-Move Rule";
            }
        }

        std::string consumeGameOver() {
            std::string out = std::move(gameOverMessage);
            gameOverMessage.clear();
            return out;
        }
        
        void movePiece(int startRow, int startCol, int endRow, int endCol) {
            // Get the pieces from the board
            ChessPiece* Piece = board[startRow][startCol];
            ChessPiece* target = board[endRow][endCol];
            
            if(!isLegalMove(startRow, startCol, endRow, endCol)){
                return;
            }
            if((Piece->color == White && isWhiteTurn == false) ||
               (Piece->color == Black && isWhiteTurn == true)) {
                return;
            }
            bool isCapture = false;
            if(target->color != Piece->color &&
                 (target->piece != EMPTY || target->enPassantSquare == true)) {
                isCapture = true;
            }
            //logic for removing pawn upon enpassant capture
            if(target->enPassantSquare == true){
                if (Piece->color == White) {
                    delete board[4][target->col];
                    board[4][target->col] = new Empty(EMPTY, None, 4, target->col);
                } else if (Piece->color == Black) {
                    delete board[3][target->col];
                    board[3][target->col] = new Empty(EMPTY, None, 3, target->col);
                }
            }
            if (Piece->color == White) {
                isWhiteTurn = false;
            } else if (Piece->color == Black) {
                isWhiteTurn = true; 
            }
            removeEnpassant();
            if (Piece->piece == PAWN) {
                struct Pawn* pawn = dynamic_cast<struct Pawn*>(Piece);
                if(pawn->color == White && target->row == 3 && pawn->row == 1) {
                    board[2][pawn->col] -> enPassantSquare = true;
                } else if (pawn->color == Black && target->row == 4 && pawn->row == 6) {
                    board[5][pawn->col] -> enPassantSquare = true;
                } 
            }

            handleMove(startRow, startCol, endRow, endCol);

            /*
            if (board[endRow][endCol]->piece == PAWN) {
                board[endRow][endCol]->checkPromotion(endRow, endCol);
            }*/

            positionCount[getPosition()]++;
            half_move_count++;
            if (isCapture) {
                capture(endRow, endCol);
                half_move_count = 0;
            }
            if(Piece->color == White) {
                checkForCheckmate(Black);
            } else if (Piece->color == Black) {
                checkForCheckmate(White);
            }
            full_move_count++;
            checkForDraw();
        }

        void promotePawn(int row, int col, char newPiece) {
            Piece piece = PAWN;
            switch(newPiece) {
                case 'Q':
                case 'q':
                    piece = QUEEN;
                    break;
                case 'R':
                case 'r':
                    piece = ROOK;
                    break;
                case 'B':
                case 'b':
                    piece = BISHOP;
                    break;
                case 'N':
                case 'n':
                    piece = KNIGHT;
                    break;
                default:
                    return; // Invalid piece type
            }
            ChessPiece* pawn = board[row][col];
            if (pawn->piece != PAWN) return;
            Color color = pawn->color;
            delete board[row][col];
            // create a new ChessPiece of the chosen type with correct coordinates
            switch(piece) {
                case QUEEN:
                    board[row][col] = new Queen(piece, color, row, col);
                    break;
                case ROOK:
                    board[row][col] = new Rook(piece, color, row, col);
                    break;
                case BISHOP:
                    board[row][col] = new Bishop(piece, color, row, col);
                    break;
                case KNIGHT:
                    board[row][col] = new Knight(piece, color, row, col);
                    break;
                default:
                    break;
            }
        }

        
        void castle(int kingRow, int kingCol, int rookRow, int rookCol) {
            // Get the pieces from the board
            ChessPiece* king = board[kingRow][kingCol];
            ChessPiece* rook = board[rookRow][rookCol];
            
            if(king->piece != KING && rook->piece != ROOK) {
                return;
            }
            if((king->color == White && isWhiteTurn == false) ||
               (king->color == Black && isWhiteTurn == true)){
                return;
            }
            if(!canCastle(kingRow, kingCol, rookRow, rookCol)) {
                return;
            }
            
            //castle kingside
            if (rook->col == 7) {
                handleMove(kingRow, kingCol, king->row, 6);
                handleMove(rookRow, rookCol, rook->row, 5);
                king->col = 6;
                rook->col = 5;  
            //castle queenside
            } else if (rook->col == 0) {
                handleMove(kingRow, kingCol, king->row, 2);
                handleMove(rookRow, rookCol, rook->row, 3);
                king->col = 2;
                rook->col = 3;
            }
                
            
            if (king->color == White){
                isWhiteTurn = false;
            } else if (rook->color == Black){
                isWhiteTurn = true;
            }

            struct King* kingPiece = static_cast<struct King*>(king);
            struct Rook* rookPiece = static_cast<struct Rook*>(rook);
            kingPiece->hasCastlingRights = false;
            rookPiece->hasCastlingRights = false;
        }

        bool checkForLegalMoves(int pieceRow, int pieceCol, Color color) {
            ChessPiece* Piece = board[pieceRow][pieceCol];
            bool hasLegalMoves = false;
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(isLegalMove(pieceRow, pieceCol, i, j) && Piece->color == color){
                        return true;
                    }
                }
            }
            return false;
        }

        char capture(int row, int col) {
            ChessPiece* target = board[row][col];
            if (target->color == White) {
                whiteCapturedPieces.push_back(target->pieceNames[target->piece]);
            } else if (target->color == Black) {
                blackCapturedPieces.push_back(target->pieceNames[target->piece]);
            }
            if (target->piece == EMPTY) {
                return ' ';
            }
            if (target->color == White) {
                return target->whitePieceSymbols[target->piece][0];
            } else if (target->color == Black) {
                return target->blackPieceSymbols[target->piece][0];
            }
            return ' ';
        }

        //Checks for stalemate due threefold repetition, 50 move rule, insufficient material
        void checkForDraw() {
            for(const auto pair : positionCount) {
                if(pair.second >= 3) {
                    gameOver();
                }
                if(half_move_count >= 100) {
                    gameOver();
                }
            }

        }

        void checkForCheckmate(Color color) {
            for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    if (board[i][j]->piece == KING && isinCheck(i, j) && board[i][j]->color == color) {
                        bool hasLegalMoves = false;
                        for(int k = 0; k < 8; k++) {
                            for(int l = 0; l < 8; l++) {
                                if(checkForLegalMoves(k, l, color) == true) {
                                    hasLegalMoves = true;
                                }
                            }
                        }
                        if(color == White && !hasLegalMoves) {
                            whiteKingisCheckmated = true;
                            break;
                        }
                        if(color == Black && !hasLegalMoves) {
                            blackKingisCheckmated = true;
                            break;
                        }
                    } else if (board[i][j]->piece == KING && !isinCheck(i, j)) {
                        bool hasLegalMoves = false;
                        for(int k = 0; k < 8; k++) {
                            for(int l = 0; l < 8; l++) {
                                if(checkForLegalMoves(k, l, color) == true) {
                                    hasLegalMoves = true;
                                }
                            }
                        }
                        if(color == White && !hasLegalMoves) {
                            isStalemate = true;
                            break;
                        }
                        if(color == Black && !hasLegalMoves) {
                            isStalemate = true;
                            break;
                        }
                    }
                }
            }
            if(whiteKingisCheckmated || blackKingisCheckmated || isStalemate) {
                gameOver();
            }
            return;
        }

        void removeEnpassant() {
            for(int i = 0; i < 8; i++) {
                for(int j = 0; j < 8; j++) {
                    board[i][j]->enPassantSquare = false;
                }
            }
        }

        void handleMove(int startRow, int startCol, int endRow, int endCol) {
            ChessPiece* Piece = board[startRow][startCol];
            ChessPiece* target = board[endRow][endCol];
            
            delete board[endRow][endCol];
            Piece->move(endRow, endCol);
            board[endRow][endCol] = Piece;
            board[startRow][startCol] = new Empty(EMPTY, None, startRow, startCol);
        }
        
        /*
        void checkPromotion(int pawnRow, int pawnCol) {
            if (board[pawnRow][pawnCol]->piece != PAWN) {
                return;
            }
            ChessPiece* piece = board[pawnRow][pawnCol];
            struct Pawn* pawn = dynamic_cast<struct Pawn*>(piece);
            if (pawn->checkPromotion()) {

            }
        }*/

        void finalizeAfterPromotion(std::string color) {
            if (color == "W") {
                checkForCheckmate(Black);
            } else {
                checkForCheckmate(White);
            }
        }


        bool isLegalMoveExceptPinned(int pieceRow, int pieceCol, int endRow, int endColumn) {
            ChessPiece* Piece = board[pieceRow][pieceCol];
            
            //a pawn can't capture a piece normally
            bool canMoveOrCapture = false;
            if(Piece->piece == PAWN && 
                (board[endRow][endColumn]->piece != EMPTY || board[endRow][endColumn]->enPassantSquare == true)) {
                if (Piece->isNormalMove(endRow, endColumn)) {
                    canMoveOrCapture = false;
                } else if (Piece->canCapture(endRow, endColumn)) {
                    canMoveOrCapture = true;
                }
            } else {
                canMoveOrCapture = Piece->isNormalMove(endRow, endColumn);
            }

            return isInsideBoard(endRow, endColumn) &&
               canMoveOrCapture &&
               !isOccupied(Piece->color, endRow, endColumn) &&
               isNotBlocked(pieceRow, pieceCol, endRow, endColumn) &&
               isInsideBoard(endRow, endColumn);
        }
        
        bool isLegalMove(int pieceRow, int pieceCol, int endRow, int endColumn) {
            return isLegalMoveExceptPinned(pieceRow, pieceCol, endRow, endColumn) &&
               isNotPinned(pieceRow, pieceCol, endRow, endColumn);
        }
        
        bool isNotPinned(int pieceRow, int pieceCol, int endRow, int endCol) {
            ChessPiece* piece = board[pieceRow][pieceCol];
            int startRow = piece->row;
            int startCol = piece->col;

            ChessPiece* captured = board[endRow][endCol];
            ChessPiece* originalStart = board[startRow][startCol];

            // Simulate move
            board[endRow][endCol] = piece;
            board[startRow][startCol] = new Empty(EMPTY, None, startRow, startCol);
            piece->row = endRow;
            piece->col = endCol;

            // Find own king
            King* king = nullptr;
            for (int i = 0; i < 8 && !king; ++i) {
                for (int j = 0; j < 8; ++j) {
                    if (board[i][j]->piece == KING && board[i][j]->color == piece->color) {
                        king = static_cast<King*>(board[i][j]);
                        break;
                    }
                }
            }

            bool inCheck = (king != nullptr) && isinCheck(king->row, king->col);

            // Restore board
            delete board[startRow][startCol]; // prevent leak
            board[startRow][startCol] = piece;
            board[endRow][endCol] = captured;
            piece->row = startRow;
            piece->col = startCol;

            return !inCheck; // true if the move does NOT leave king in check
        }
        
        //tested
        bool isInsideBoard(int x, int y) {
            return (x >= 0 && x < 8 && y >= 0 && y < 8);
        }
        
        //tested
        bool isOccupied(Color color, int x, int y) {
            if (board[x][y]->piece != EMPTY && board[x][y]->color == color) { 
                return true;
            }
            return false;
        }
        
        bool isNotBlocked(int friendlyRow, int friendlyCol, int endRow, int endColumn) {
            ChessPiece* friendly = board[friendlyRow][friendlyCol];
            
            if (!isInsideBoard(endRow, endColumn)) {
                return false;
            }

            if(friendly->piece == KNIGHT) {
                return true;
            }
            if(friendly->piece == KING){
                return true;
            }
            if(friendly->piece == PAWN) {
                if(abs(endRow - friendly->row) == 2) {
                    return isNotBlockedColumn(friendly->row, friendly->col, endRow, endColumn);
                } else {
                    return true;
                }
            } else if (friendly->piece == ROOK) {
                if (friendly->isinRow(endRow, endColumn)) {
                    return isNotBlockedRow(friendly->row, friendly->col, endRow, endColumn);
                } else if (friendly->isinColumn(endRow, endColumn)) {
                    return isNotBlockedColumn(friendly->row, friendly->col, endRow, endColumn);
                } else {
                    return false;
                }
            } else if (friendly->piece == BISHOP) {
                return isNotBlockedDiagonal(friendly->row, friendly->col, endRow, endColumn);
            } else if (friendly->piece == QUEEN) {
                if (friendly->isinRow(endRow, endColumn)) {
                    return isNotBlockedRow(friendly->row, friendly->col, endRow, endColumn);
                } else if (friendly->isinColumn(endRow, endColumn)) {
                    return isNotBlockedColumn(friendly->row, friendly->col, endRow, endColumn);
                } else if (friendly->isdiagonal(endRow, endColumn)) {
                    return isNotBlockedDiagonal(friendly->row, friendly->col, endRow, endColumn);
                }
            }
            return false;
        }
        
        //''
        bool isNotBlockedRow(int startRow, int startCol, int endRow, int endCol) {
            int step = (endCol - startCol) > 0 ? 1 : -1;
            for (int col = startCol + step; col != endCol; col += step) {
                if (board[startRow][col]->piece != EMPTY) {
                    return false;
                }
            }
            return true;
        }
        
        //''
        bool isNotBlockedColumn(int startRow, int startCol, int endRow, int endCol) {
            int step = (endRow - startRow) > 0 ? 1 : -1;
            for (int row = startRow + step; row != endRow; row += step) {
                if (board[row][startCol]->piece != EMPTY) {
                    return false;
                }
            }
            return true;
        }
        
        //''
        bool isNotBlockedDiagonal(int startRow, int startCol, int endRow, int endCol) {
            int stepX = (endRow - startRow) > 0 ? 1 : -1;
            int stepY = (endCol - startCol) > 0 ? 1 : -1;
            int x = startRow + stepX;
            int y = startCol + stepY;
            while (x != endRow && y != endCol) {
                if (board[x][y]->piece != EMPTY) {
                    return false;
                }
                x += stepX;
                y += stepY;
            }
            return true;
        }
        
        bool canCastle(int kingRow, int kingCol, int rookRow, int rookCol) {
            ChessPiece* kingPiece = board[kingRow][kingCol];
            ChessPiece* rookPiece = board[rookRow][rookCol];
            
            if(!(kingPiece->piece==KING && rookPiece->piece==ROOK)){
                return false; 
            }
            King* king = static_cast<King*>(kingPiece);
            Rook* rook = static_cast<Rook*>(rookPiece);
            if (king->hasCastlingRights && rook->hasCastlingRights
            && !isinCheckSquare(king->color, king->row, rook->col) &&
             notThroughCheck(kingRow, kingCol, rookRow, rookCol) && 
             isNotBlockedForCastle(kingRow, kingCol, rookRow, rookCol)) {
                return true;
            }
            return false;
        }
        
        bool isNotBlockedForCastle(int kingRow, int kingCol, int rookRow, int rookCol) {
            ChessPiece* king = board[kingRow][kingCol];
            ChessPiece* rook = board[rookRow][rookCol];
            
            if(rook->col != 7 && rook->col != 0){
                return false;
            }
            if (rook -> col == 7) {
                for(int j = 5; j < 7; j++) {
                    if(board[king->row][j]->piece != EMPTY){
                        return false;
                    }
                }
            } else {
                for(int j = 1; j < 4; j++) {
                    if(board[king->row][j]->piece != EMPTY){
                        return false;
                    }
                }
            }
            return true;
        }
        
        //tested
        bool isinCheckSquare(Color color, int endRow, int endColumn) {
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    if (board[i][j]->color != color && board[i][j]->piece != EMPTY) {
                        if (isLegalMoveExceptPinned(i, j, endRow, endColumn)) {
                            return true;
                        }   
                    }
                }
            }
            return false;
        }
        
        bool isinCheck(int pieceRow, int pieceCol) {
            ChessPiece* Piece = board[pieceRow][pieceCol];
            if (Piece->piece == KING) {
                return isinCheckSquare(Piece->color, Piece->row, Piece->col);
            } 
            return false;
        }
        
        bool notThroughCheck(int kingRow, int kingCol, int rookRow, int rookCol) {
            ChessPiece* king = board[kingRow][kingCol];
            ChessPiece* rook = board[rookRow][rookCol];
            
            if(rook->col != 7 && rook->col != 0){
                return false;
            }
            if (rook -> col == 7) {
                for(int j = 4; j <= 7; j++) {
                    if (isinCheckSquare(king->color, king->row, j)) {
                        return false;
                    }
                }
            } else {
                for(int j = 0; j <= 4; j++) {
                    if (isinCheckSquare(king->color, king->row, j)) {
                        return false;
                    }
                }
            }
            return true;
        }
};


