#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "src/engine/board.cpp"




TEST_CASE("Testing normal moves, is occupied, and inside board") {
    Board chessBoard;
    
    chessBoard.board[6][0] = new Pawn(PAWN, Black, 6, 0); // Black pawn at initial position
    chessBoard.board[1][0] = new Pawn(PAWN, White, 1, 0); // White pawn at initial position
    CHECK((chessBoard.board[6][0]->color == Black) == true);
    CHECK((chessBoard.board[6][0]->color == White) == false);
    CHECK((chessBoard.board[1][0]->color == Black) == false);
    CHECK((chessBoard.board[1][0]->color == White) == true);

    CHECK((chessBoard.board[6][0]->piece == PAWN) == true);
    CHECK((chessBoard.board[1][0]->piece == PAWN) == true);
    CHECK((chessBoard.board[6][0]->piece == ROOK) == false);
    CHECK((chessBoard.board[1][0]->piece == KING) == false);
    CHECK((chessBoard.board[1][0]->row == 1) == true);
    CHECK((chessBoard.board[1][0]->col == 0) == true);
    CHECK((chessBoard.board[1][0]->row == 2) == false);
    CHECK((chessBoard.board[6][0]->col == 1) == false);

    //Test normal moves
    CHECK(chessBoard.board[6][0]->isNormalMove(4, 0) == true); // Black pawn two steps
    CHECK(chessBoard.board[1][0]->isNormalMove(3, 0) == true); // White pawn two steps
    CHECK(chessBoard.board[6][0]->isNormalMove(5, 0) == true); // Black pawn one step
    CHECK(chessBoard.board[1][0]->isNormalMove(2, 0) == true); // White pawn one step

    CHECK(chessBoard.board[6][0]->isNormalMove(3, 0) == false); // Black pawn three steps
    CHECK(chessBoard.board[1][0]->isNormalMove(4, 0) == false); // White pawn three steps
    CHECK(chessBoard.board[1][0]->isNormalMove(1, 0) == false); // White pawn to same spot
    CHECK(chessBoard.board[6][0]->isNormalMove(6, 0) == false); // Black pawn to same spot
    CHECK(chessBoard.board[6][0]->isNormalMove(5, 1) == false); // Black pawn diagonal move
    CHECK(chessBoard.board[1][0]->isNormalMove(2, 1) == false); // White pawn diagonal move
    CHECK(chessBoard.board[6][0]->isNormalMove(7, 0) == false); // Black pawn backward move
    CHECK(chessBoard.board[1][0]->isNormalMove(0, 0) == false); // White pawn backward move
    CHECK(chessBoard.board[6][0]->isNormalMove(7, 1) == false); // Black pawn diagonal backward move
    CHECK(chessBoard.board[1][0]->isNormalMove(0, 1) == false); // White pawn diagonal backward move



    chessBoard.board[5][4] = new Rook(ROOK, Black, 5, 4); // Place white pawn in front of black pawn
    CHECK(chessBoard.board[5][4]->row == 5); // Rook row location
    CHECK(chessBoard.board[5][4]->col == 4); // Rook column location
    CHECK(chessBoard.board[5][4]->isinRow(5, 7) == true); // Rook in same row
    CHECK(chessBoard.board[5][4]->isinRow(4, 4) == false); // Rook not in same row
    CHECK(chessBoard.board[5][4]->isinColumn(2, 4) == true); // Rook in same column
    CHECK(chessBoard.board[5][4]->isinColumn(5, 3) == false); // Rook not in same column
    CHECK(chessBoard.board[5][4]->isNormalMove(0, 4) == true); // Rook vertical move
    CHECK(chessBoard.board[5][4]->isNormalMove(7, 4) == true); // Rook vertical move
    CHECK(chessBoard.board[5][4]->isNormalMove(5, 0) == true); // Rook horizontal move
    CHECK(chessBoard.board[5][4]->isNormalMove(5, 7) == true); // Rook horizontal move
    CHECK(chessBoard.board[5][4]->isNormalMove(7, 6) == false); // Rook diagonal move
    CHECK(chessBoard.board[5][4]->isNormalMove(4, 3) == false); // Rook non-linear move
    


    chessBoard.board[5][5] = new Bishop(BISHOP, White, 5, 5); // Place white bishop
    CHECK(chessBoard.board[5][5]->row == 5); // Bishop row location
    CHECK(chessBoard.board[5][5]->col == 5); // Bishop column location
    CHECK(chessBoard.board[5][5]->isdiagonal(7, 7) == true); // Bishop diagonal move
    CHECK(chessBoard.board[5][5]->isdiagonal(3, 3) == true); // Bishop diagonal move
    CHECK(chessBoard.board[5][5]->isdiagonal(7, 3) == true); // Bishop diagonal move
    CHECK(chessBoard.board[5][5]->isdiagonal(3, 7) == true); // Bishop diagonal move
    CHECK(chessBoard.board[5][5]->isdiagonal(5, 7) == false); // Bishop non-diagonal move
    CHECK(chessBoard.board[5][5]->isdiagonal(6, 5) == false); // Bishop non-diagonal move
    CHECK(chessBoard.board[5][5]->isNormalMove(1, 4) == false); // Bishop non-diagonal move

    chessBoard.board[1][4] = new Bishop(BISHOP, Black, 1, 4);
    CHECK(chessBoard.board[1][4]->isNormalMove(3, 2) == true);

    


    chessBoard.board[4][4] = new Queen(QUEEN, White, 4, 4); // Place white queen
    CHECK(chessBoard.board[4][4]->row == 4); // Queen row location
    CHECK(chessBoard.board[4][4]->col == 4); // Queen column location
    CHECK(chessBoard.board[4][4]->isNormalMove(4, 7) == true); // Queen horizontal move
    CHECK(chessBoard.board[4][4]->isNormalMove(7, 4) == true); // Queen vertical move
    CHECK(chessBoard.board[4][4]->isNormalMove(7, 7) == true); // Queen diagonal move
    CHECK(chessBoard.board[4][4]->isNormalMove(2, 6) == true); // Queen diagonal move
    CHECK(chessBoard.board[4][4]->isNormalMove(5, 6) == false); // Queen non-linear move

    chessBoard.board[3][3] = new Knight(KNIGHT, Black, 3, 3); // Place black knight
    CHECK((chessBoard.board[3][3]->piece == KNIGHT) == true);
    CHECK(chessBoard.board[3][3]->row == 3); // Knight row location
    CHECK(chessBoard.board[3][3]->col == 3); // Knight column
    CHECK(chessBoard.board[3][3]->isNormalMove(5, 4) == true); // Knight L move
    CHECK(chessBoard.board[3][3]->isNormalMove(5, 2) == true); // Knight L move
    CHECK(chessBoard.board[3][3]->isNormalMove(1, 4) == true); // Knight L move
    CHECK(chessBoard.board[3][3]->isNormalMove(1, 2) == true); // Knight L move
    CHECK(chessBoard.board[3][3]->isNormalMove(4, 5) == true); // Knight L move
    CHECK(chessBoard.board[3][3]->isNormalMove(4, 1) == true); // Knight L move
    CHECK(chessBoard.board[3][3]->isNormalMove(2, 5) == true); // Knight L move
    CHECK(chessBoard.board[3][3]->isNormalMove(2, 1) == true); // Knight L move
    CHECK(chessBoard.board[3][3]->isNormalMove(4, 6) == false); // Knight non-L move
    CHECK(chessBoard.board[3][3]->isNormalMove(5, 5) == false); // Knight non-L move
    CHECK(chessBoard.board[3][3]->isNormalMove(3, 5) == false); // Knight non-L move


    chessBoard.board[1][4] = new King(KING, White, 1, 4); // Place white king
    CHECK((chessBoard.board[1][4]->piece == KING) == true);
    CHECK(chessBoard.board[1][4]->row == 1); // King row
    CHECK(chessBoard.board[1][4]->col == 4); // King column
    CHECK(chessBoard.board[1][4]->isNormalMove(2, 4) == true); // King one step forward
    CHECK(chessBoard.board[1][4]->isNormalMove(0, 4) == true); // King one step backward
    CHECK(chessBoard.board[1][4]->isNormalMove(1, 5) == true); // King one step right
    CHECK(chessBoard.board[1][4]->isNormalMove(1, 3) == true); // King one step left
    CHECK(chessBoard.board[1][4]->isNormalMove(2, 5) == true); // King one step diagonal
    CHECK(chessBoard.board[1][4]->isNormalMove(3, 4) == false); // King two steps forward
    CHECK(chessBoard.board[1][4]->isNormalMove(1, 6) == false); // King two steps right
    CHECK(chessBoard.board[1][4]->isNormalMove(4, 3) == false); // King two steps diagonal
    CHECK(chessBoard.board[1][4]->isNormalMove(0, 2) == false); // King non-one step move
    

    

    //Test isOccupied
    chessBoard.board[5][1] = new Pawn(PAWN, Black, 5, 1); // Black pawn in front of black pawn
    chessBoard.board[2][1] = new Pawn(PAWN, White, 2, 1); // White pawn in front of black pawn
    CHECK(chessBoard.isOccupied(Black, 5, 1) == true); // Black pawn occupied by friendly
    CHECK(chessBoard.isOccupied(White, 2, 1) == true); // White pawn occupied by friendly

    //Test insideBoard
    CHECK(chessBoard.isInsideBoard(4, 4) == true); // Inside board
    CHECK(chessBoard.isInsideBoard(-1, 4) == false); // Row out of bounds
    CHECK(chessBoard.isInsideBoard(4, -1) == false); // Column
    CHECK(chessBoard.isInsideBoard(8, 4) == false); // Row out of bounds
    CHECK(chessBoard.isInsideBoard(4, 8) == false); // Column

}

//need to test non-normal move for rook bishop
TEST_CASE("Testing is not blocked") {
    Board chessBoard;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 

    //test rook
    chessBoard.board[4][4] = new Rook(ROOK, White, 4, 4);
    chessBoard.board[4][5] = new Pawn(PAWN, White, 4, 5);
    chessBoard.board[1][4] = new Pawn(PAWN, White, 1, 4);
    CHECK(chessBoard.isNotBlocked(4, 4, 4, 6) == false);
    CHECK(chessBoard.isNotBlocked(4, 4, 4, 2) == true);
    CHECK(chessBoard.isNotBlocked(4, 4, 0, 4) == false);
    CHECK(chessBoard.isNotBlocked(4, 4, 7, 4) == true);
    CHECK(chessBoard.isNotBlocked(4, 4, 2, 4) == true);
    //non-normal move
    CHECK(chessBoard.isNotBlocked(4, 4, 2, 3) == false);

    //test bishop
    Board chessBoard2;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard2.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 

    chessBoard2.board[4][4] = new Bishop(BISHOP, White, 4, 4);
    chessBoard2.board[3][3] = new Pawn(PAWN, White, 4, 5);
    chessBoard2.board[3][5] = new Pawn(PAWN, Black, 3, 5);

    CHECK(chessBoard2.isNotBlocked(4, 4, 3, 3) == true); //not blocked by piece on target square
    CHECK(chessBoard2.isNotBlocked(4, 4, 3, 5) == true);
    CHECK(chessBoard2.isNotBlocked(4, 4, 2, 2) == false);
    CHECK(chessBoard2.isNotBlocked(4, 4, 2, 6) == false);
    CHECK(chessBoard2.isNotBlocked(4, 4, 5, 3) == true);
    //non-normal move, is not blocked on non-normal move
    CHECK(chessBoard2.isNotBlocked(4, 4, 4, 3) == true);


    //test queen
    Board chessBoard3;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard3.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 

    chessBoard3.board[4][4] = new Queen(QUEEN, White, 4, 4);
    chessBoard3.board[4][5] = new King(KING, White, 4, 5);
    chessBoard3.board[5][4] = new Pawn(PAWN, Black, 5, 4);
    chessBoard3.board[3][3] = new Knight(KNIGHT, Black, 3, 3);
    CHECK(chessBoard3.isNotBlocked(4, 4, 2, 2) == false);
    CHECK(chessBoard3.isNotBlocked(4, 4, 2, 6) == true);
    CHECK(chessBoard3.isNotBlocked(4, 4, 4, 6) == false);
    CHECK(chessBoard3.isNotBlocked(4, 4, 7, 4) == false);
    CHECK(chessBoard3.isNotBlocked(4, 4, 7, 1) == true);

    //check if doesn't crash on non-normal move
    CHECK(chessBoard3.isNotBlocked(4, 4, 5, 6) == false);
    //check if doesn't crash on outside the board
    CHECK(chessBoard3.isNotBlocked(4, 4, 8, 5) == false);

    //check if pawn is blocked on moving two squares
    Board chessBoard4;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard4.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 

    chessBoard4.board[1][5] = new Pawn(PAWN, White, 1, 5);
    chessBoard4.board[1][4] = new Pawn(PAWN, White, 1, 4);
    chessBoard4.board[2][5] = new Pawn(PAWN, Black, 2, 5);

    CHECK(chessBoard4.isNotBlocked(1, 5, 3, 5) == false);
    CHECK(chessBoard4.isNotBlockedColumn(1, 4, 3, 4) == true);
    CHECK(chessBoard4.isNotBlocked(1, 4, 3, 4) == true);

    //checking if empty piece returns false
    CHECK(chessBoard4.isNotBlocked(1, 7, 3, 4) == false);

}


TEST_CASE("Testing isLegalMove"){
    Board chessBoard;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 

    ChessPiece* pawn1 = chessBoard.board[1][5] = new Pawn(PAWN, White, 1, 5);
    ChessPiece* pawn2 = chessBoard.board[1][4] = new Pawn(PAWN, White, 1, 4);
    ChessPiece* pawn3 = chessBoard.board[2][4] = new Pawn(PAWN, Black, 2, 4);
    ChessPiece* bishop1 = chessBoard.board[3][3] = new Bishop(BISHOP, Black, 3, 3);
    ChessPiece* rook1 = chessBoard.board[3][0] = new Rook(ROOK, White, 3, 0);
    ChessPiece* rook2 = chessBoard.board[3][6] = new Rook(ROOK, Black, 3, 6);

    CHECK(chessBoard.isLegalMove(1, 5, 3, 5) == true);
    CHECK(chessBoard.isLegalMove(1, 5, 2, 5) == true);
    CHECK(chessBoard.isLegalMove(1, 5, 4, 5) == false);
    CHECK(chessBoard.isLegalMove(1, 4, 3, 4) == false);

    CHECK(chessBoard.isLegalMove(3, 0, 3, 3) == true);
    CHECK(chessBoard.isLegalMove(3, 0, 3, 4) == false);
    CHECK(chessBoard.isLegalMove(3, 6, 3, 3) == false);

}


TEST_CASE("Testing isinchecksquare and isincheck and isnotpinned") {
    Board chessBoard;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 

    chessBoard.board[0][4] = new King(KING, White, 0, 4);
    chessBoard.board[5][4] = new Rook(ROOK, Black, 5, 4);

    CHECK(chessBoard.isinCheckSquare(White, 0, 4) == true);
    CHECK(chessBoard.isinCheck(0, 4) == true);

    Board chessBoard2;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard2.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 
    //is not pinned initially
    ChessPiece* pawn1 = chessBoard2.board[1][4] = new Pawn(PAWN, White, 1, 4);
    CHECK(chessBoard2.isNotPinned(1, 4, 2, 4) == true);

    //is pinned by rook
    ChessPiece* king1 = chessBoard2.board[1][6] = new King(KING, White, 1, 6);
    ChessPiece* rook1 = chessBoard2.board[1][1] = new Rook(ROOK, Black, 1, 1);
    CHECK(chessBoard2.isNotPinned(1, 4, 2, 4) == false);

    //is not pinned by rook of same color
    ChessPiece* rook2 = chessBoard2.board[1][1] = new Rook(ROOK, White, 1, 1);
    CHECK(chessBoard2.isNotPinned(1, 4, 2, 4) == true);

    //is not pinned if friendly piece to right
    ChessPiece* rook3 = chessBoard2.board[1][1] = new Rook(ROOK, Black, 1, 1);
    ChessPiece* pawn2 = chessBoard2.board[1][5] = new Pawn(PAWN, White, 1, 5);
    CHECK(chessBoard2.isNotPinned(1, 4, 2, 4) == true);

    //is not pinned if enemy piece to right
    ChessPiece* pawn3 = chessBoard2.board[1][5] = new Pawn(PAWN, Black, 1, 5);
    CHECK(chessBoard2.isNotPinned(1, 4, 2, 4) == true);
    pawn3 = chessBoard2.board[1][5] = new Empty(EMPTY, Black, 1, 5);
    CHECK(chessBoard2.isNotPinned(1, 4, 2, 4) == false);

    //is not pinned if enemy piece to left
    pawn3 = chessBoard2.board[1][3] = new Pawn(PAWN, Black, 1, 3);
    CHECK(chessBoard2.isNotPinned(1, 4, 2, 4) == true);

}

//full suite of legal move tests 

//pawn
TEST_CASE("Testing pawn legal moves"){
    Board chessBoard;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    }

    ChessPiece* pawn1 = chessBoard.board[1][4] = new Pawn(PAWN, White, 1, 4);
    ChessPiece* pawn2 = chessBoard.board[6][4] = new Pawn(PAWN, Black, 6, 4);

    
    

    CHECK(chessBoard.isLegalMove(1, 4, 2, 4));
    CHECK(chessBoard.isLegalMove(1, 4, 3, 4));
    CHECK(!chessBoard.isLegalMove(1, 4, 4, 4));
    CHECK(!chessBoard.isLegalMove(1, 4, 1, 5));
    CHECK(!chessBoard.isLegalMove(1, 4, 0, 4)); 
    CHECK(!chessBoard.isLegalMove(1, 4, 2, 5));

    CHECK(chessBoard.isLegalMove(6, 4, 5, 4));
    CHECK(chessBoard.isLegalMove(6, 4, 4, 4));
    CHECK(!chessBoard.isLegalMove(6, 4, 6, 5));
    CHECK(!chessBoard.isLegalMove(6, 4, 3, 4));
    CHECK(!chessBoard.isLegalMove(6, 4, 7, 4));
    CHECK(!chessBoard.isLegalMove(6, 4, 5, 3));

    ChessPiece* king1 = chessBoard.board[6][6] = new King(KING, Black, 6, 6);
    ChessPiece* rook1 = chessBoard.board[6][2] = new Rook(ROOK, White, 6, 2);

    CHECK(!chessBoard.isLegalMove(6, 4, 5, 4));
    CHECK(!chessBoard.isLegalMove(6, 4, 4, 4));
    CHECK(!chessBoard.isLegalMove(6, 4, 6, 5));
    CHECK(!chessBoard.isLegalMove(6, 4, 3, 4));
    CHECK(!chessBoard.isLegalMove(6, 4, 7, 4));
    CHECK(!chessBoard.isLegalMove(6, 4, 5, 3));



    ChessPiece* king2 = chessBoard.board[7][2] = new King(KING, White, 7, 2);
    ChessPiece* rook2 = chessBoard.board[5][2] = new Rook(ROOK, Black, 5, 2);

    
    CHECK(!chessBoard.isLegalMove(6, 4, 5, 4));
    CHECK(!chessBoard.isLegalMove(6, 4, 4, 4));
    CHECK(!chessBoard.isLegalMove(6, 4, 6, 5));
    CHECK(!chessBoard.isLegalMove(6, 4, 3, 4));
    CHECK(!chessBoard.isLegalMove(6, 4, 7, 4));
    CHECK(!chessBoard.isLegalMove(6, 4, 5, 3));

    //checking if moving a non-pinned piece is okay
    CHECK(!chessBoard.isinCheck(7, 2));
    CHECK(chessBoard.isLegalMove(1, 4, 3, 4));

    //test is blocked from moving by an enemy piece on the target square
    ChessPiece* pawn3 = chessBoard.board[3][4] = new Pawn(PAWN, Black, 3, 4);
    CHECK(!chessBoard.isLegalMove(1, 4, 3, 4));

    ChessPiece* pawn4 = chessBoard.board[3][4] = new Pawn(PAWN, White, 3, 4);
    CHECK(!chessBoard.isLegalMove(1, 4, 3, 4));

    //reinitializing blocked square to empty
    ChessPiece* empty1 = chessBoard.board[3][4] = new Empty(EMPTY, None, 3, 4);
    CHECK(chessBoard.isOccupied(pawn1->color, 3, 4) == false);
    CHECK(chessBoard.isOccupied(pawn1->color, 2, 4) == false);

    //can't move through a piece
    CHECK(chessBoard.isLegalMove(1, 4, 3, 4));
    ChessPiece* pawn5 = chessBoard.board[2][4] = new Pawn(PAWN, Black, 2, 4);
    CHECK(!chessBoard.isLegalMove(1, 4, 3, 4));

    //test capture and enpassant capture next
    Board chessBoard2;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard2.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    }

    pawn1 = chessBoard2.board[1][4] = new Pawn(PAWN, White, 1, 4);
    pawn2 = chessBoard2.board[2][5] = new Pawn(PAWN, Black, 2, 5);


    CHECK(chessBoard2.isLegalMove(1, 4, 2, 5));
    CHECK(chessBoard2.isLegalMove(1, 4, 2, 4));
    CHECK(chessBoard2.isLegalMove(1, 4, 3, 4));
    CHECK(!chessBoard2.isLegalMove(1, 4, 2, 3));
    CHECK(!chessBoard2.isLegalMove(1, 4, 3, 5));

    pawn3 = chessBoard2.board[4][4] = new Pawn(PAWN, White, 4, 4);
    pawn4 = chessBoard2.board[4][5] = new Pawn(PAWN, Black, 4, 5);
    chessBoard2.board[5][5]->enPassantSquare = true;
    CHECK(chessBoard2.isLegalMove(4, 4, 5, 5));
    CHECK(!chessBoard2.isLegalMove(4, 4, 5, 3));
    CHECK(!chessBoard2.isLegalMove(4, 4, 4, 5));

}


//knight
TEST_CASE("Testing knight legal moves") {
    Board chessBoard;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 

    ChessPiece* knight1 = chessBoard.board[4][4] = new Knight(KNIGHT, White, 4, 4);  
    
    //normal moves
    CHECK(chessBoard.isLegalMove(4, 4, 6, 5));
    CHECK(chessBoard.isLegalMove(4, 4, 5, 6));
    CHECK(chessBoard.isLegalMove(4, 4, 3, 6));
    CHECK(chessBoard.isLegalMove(4, 4, 2, 5));
    CHECK(chessBoard.isLegalMove(4, 4, 2, 3));
    CHECK(chessBoard.isLegalMove(4, 4, 3, 2));
    CHECK(chessBoard.isLegalMove(4, 4, 5, 2));
    CHECK(chessBoard.isLegalMove(4, 4, 6, 3));

    //non-normal moves, diagonal, row, column, non-linear, outside
    CHECK(!chessBoard.isLegalMove(4, 4, 3, 3));
    CHECK(!chessBoard.isLegalMove(4, 4, 3, 5));
    CHECK(!chessBoard.isLegalMove(4, 4, 4, 5));
    CHECK(!chessBoard.isLegalMove(4, 4, 5, 4));
    CHECK(!chessBoard.isLegalMove(4, 4, 8, 3));
    CHECK(!chessBoard.isLegalMove(4, 4, 6, 6));
    CHECK(!chessBoard.isLegalMove(4, 4, 0, 2));
    CHECK(!chessBoard.isLegalMove(4, 4, 7, 4));

    ChessPiece* king1 = chessBoard.board[4][5] = new King(KING, White, 4, 5);
    ChessPiece* rook1 = chessBoard.board[4][1] = new Rook(ROOK, Black, 4, 1);
    
    //is pinned
    CHECK(!chessBoard.isNotPinned(4, 4, 6, 5));
    CHECK(!chessBoard.isLegalMove(4, 4, 6, 5));
    CHECK(!chessBoard.isLegalMove(4, 4, 5, 6));
    CHECK(!chessBoard.isLegalMove(4, 4, 3, 6));
    CHECK(!chessBoard.isLegalMove(4, 4, 2, 5));
    CHECK(!chessBoard.isLegalMove(4, 4, 2, 3));
    CHECK(!chessBoard.isLegalMove(4, 4, 3, 2));
    CHECK(!chessBoard.isLegalMove(4, 4, 5, 2));
    CHECK(!chessBoard.isLegalMove(4, 4, 6, 3));

    //not pinned by rook of same color
    ChessPiece* rook2 = chessBoard.board[4][1] = new Rook(ROOK, White, 4, 1);
    CHECK(chessBoard.isLegalMove(4, 4, 6, 5));
    CHECK(chessBoard.isLegalMove(4, 4, 5, 6));
    CHECK(chessBoard.isLegalMove(4, 4, 3, 6));
    CHECK(chessBoard.isLegalMove(4, 4, 2, 5));
    CHECK(chessBoard.isLegalMove(4, 4, 2, 3));
    CHECK(chessBoard.isLegalMove(4, 4, 3, 2));
    CHECK(chessBoard.isLegalMove(4, 4, 5, 2));
    CHECK(chessBoard.isLegalMove(4, 4, 6, 3));

    //not pinned if piece next to it 
    ChessPiece* rook3 = chessBoard.board[4][1] = new Rook(ROOK, Black, 4, 1);
    ChessPiece* pawn1 = chessBoard.board[4][3] = new Pawn(PAWN, Black, 4, 3);
    CHECK(chessBoard.isLegalMove(4, 4, 6, 3));

    //is pinned even if attacking piece is pinned
    chessBoard.board[4][3] = new Empty(EMPTY, None, 4, 3);
    ChessPiece* rook4 = chessBoard.board[6][1] = new Rook(ROOK, White, 6, 1);
    ChessPiece* king2 = chessBoard.board[3][1] = new King(KING, Black, 3, 1);
    CHECK(chessBoard.isLegalMove(6, 1, rook3->row, rook3->col) == true);
    CHECK(chessBoard.isNotPinned(4, 1, 4, 4) == false);
    CHECK(chessBoard.isNotPinned(4, 4, 6, 5) == false);
    
}


TEST_CASE("Testing king legal moves and isincheckmate"){
    Board chessBoard;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 
    
    ChessPiece* king1 = chessBoard.board[4][4] = new King(KING, White, 4, 4);
    ChessPiece* rook1 = chessBoard.board[4][0] = new Rook(ROOK, White, 4, 0);
    

    CHECK(king1->isNormalMove(4, 5));
    
    CHECK(chessBoard.isLegalMove(4, 4, 4, 5));
    CHECK(chessBoard.isLegalMove(4, 4, 4, 3));
    CHECK(chessBoard.isLegalMove(4, 4, 5, 4));
    CHECK(chessBoard.isLegalMove(4, 4, 3, 5));
    CHECK(chessBoard.isLegalMove(4, 4, 5, 5));
    CHECK(chessBoard.isLegalMove(4, 4, 3, 3));
    CHECK(chessBoard.isLegalMove(4, 4, 3, 5));
    CHECK(chessBoard.isLegalMove(4, 4, 5, 3));
    
    CHECK(!chessBoard.isLegalMove(4, 4, 4, 6));
    CHECK(!chessBoard.isLegalMove(4, 4, 6, 6));
    CHECK(!chessBoard.isLegalMove(4, 4, 3, 2));
    CHECK(!chessBoard.isLegalMove(4, 4, 2, 6));
    CHECK(!chessBoard.isLegalMove(4, 4, 6, 4));

    
    //can move while in check to safe square
    ChessPiece* rook2 = chessBoard.board[4][0] = new Rook(ROOK, Black, 4, 0);
    CHECK(!chessBoard.isLegalMove(4, 4, 4, 5));
    CHECK(!chessBoard.isLegalMove(4, 4, 4, 3));
    CHECK(chessBoard.isLegalMove(4, 4, 5, 4));
    CHECK(chessBoard.isLegalMove(4, 4, 3, 5));
    CHECK(chessBoard.isLegalMove(4, 4, 5, 5));
    CHECK(chessBoard.isLegalMove(4, 4, 3, 3));
    CHECK(chessBoard.isLegalMove(4, 4, 3, 5));
    CHECK(chessBoard.isLegalMove(4, 4, 5, 3));

    CHECK(!chessBoard.isLegalMove(4, 4, 4, 6));
    CHECK(!chessBoard.isLegalMove(4, 4, 6, 6));
    CHECK(!chessBoard.isLegalMove(4, 4, 3, 2));
    CHECK(!chessBoard.isLegalMove(4, 4, 2, 6));
    CHECK(!chessBoard.isLegalMove(4, 4, 6, 4));

    
    //can't move into check
    ChessPiece* queen1 = chessBoard.board[3][0] = new Queen(QUEEN, Black, 3, 0);
    ChessPiece* rook3 = chessBoard.board[4][0] = new Rook(ROOK, Black, 4, 0);
    CHECK(!chessBoard.isLegalMove(4, 4, 4, 5));
    CHECK(!chessBoard.isLegalMove(4, 4, 4, 3));
    CHECK(chessBoard.isLegalMove(4, 4, 5, 4));
    CHECK(!chessBoard.isLegalMove(4, 4, 3, 5));
    CHECK(chessBoard.isLegalMove(4, 4, 5, 5));
    CHECK(!chessBoard.isLegalMove(4, 4, 3, 3));
    CHECK(!chessBoard.isLegalMove(4, 4, 3, 5));
    CHECK(chessBoard.isLegalMove(4, 4, 5, 3));

    CHECK(!chessBoard.isLegalMove(4, 4, 4, 6));
    CHECK(!chessBoard.isLegalMove(4, 4, 6, 6));
    CHECK(!chessBoard.isLegalMove(4, 4, 3, 2));
    CHECK(!chessBoard.isLegalMove(4, 4, 2, 6));
    CHECK(!chessBoard.isLegalMove(4, 4, 6, 4));
    
    //friendly piece is allowed to move in between or capture attacking piece
    ChessPiece* queen2 = chessBoard.board[6][0] = new Queen(QUEEN, White, 6, 0);
    CHECK(chessBoard.isLegalMove(6, 0, 4, 0));
    CHECK(chessBoard.isLegalMove(6, 0, 4, 2));
    
}

//test castling logic
TEST_CASE("Testing castling logic"){
    Board chessBoard;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 

    //white castling kingside
    ChessPiece* rook1 = chessBoard.board[0][7] = new Rook(ROOK, White, 0, 7);
    ChessPiece* king1 = chessBoard.board[0][4] = new King(KING, White, 0, 4);
    CHECK(chessBoard.canCastle(0, 4, 0, 7) == true);

    //white castling queenside
    ChessPiece* rook2 = chessBoard.board[0][0] = new Rook(ROOK, White, 0, 0);
    CHECK(chessBoard.canCastle(0, 4, 0, 0) == true);

    //check if can't castle in check
    ChessPiece* rook3 = chessBoard.board[7][4] = new Rook(ROOK, Black, 7, 4);
    CHECK(chessBoard.canCastle(0, 4, 0, 7) == false);
    CHECK(chessBoard.canCastle(0, 4, 0, 0) == false);

    ChessPiece* empty1 = chessBoard.board[7][4] = new Empty(EMPTY, None, 7, 4);
    CHECK(chessBoard.canCastle(0, 4, 0, 7) == true);

    //can't castle through check
    ChessPiece* rook4 = chessBoard.board[7][5] = new Rook(ROOK, Black, 7, 5);
    CHECK(chessBoard.canCastle(0, 4, 0, 7) == false);
    CHECK(chessBoard.canCastle(0, 4, 0, 0) == true);

    //can't castle through queen diagonal attack
    ChessPiece* queen1 = chessBoard.board[6][7] = new Queen(QUEEN, Black, 6, 7);

    CHECK(chessBoard.isLegalMove(6, 7, 0, 1));
    CHECK(chessBoard.isinCheckSquare(White, 0, 1));
    CHECK(chessBoard.canCastle(0, 4, 0, 0) == false);


    Board chessBoard2;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard2.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 
    ChessPiece* rook5 = chessBoard2.board[0][7] = new Rook(ROOK, White, 0, 7);
    ChessPiece* king2 = chessBoard2.board[0][4] = new King(KING, White, 0, 4);

    //check if doesn't break when trying to castle with non king and rook
    CHECK(!chessBoard2.canCastle(0, 4, 0, 0));

    //check if can't castle when blocked 
    ChessPiece* pawn1 = chessBoard2.board[0][6] = new Pawn(PAWN, White, 0, 6);
    CHECK(!chessBoard2.isNotBlockedForCastle(0, 4, 0, 7));
    CHECK(chessBoard2.notThroughCheck(0, 4, 0, 7));
    CHECK(!chessBoard2.canCastle(0, 4, 0, 7));

    ChessPiece* empty2 = chessBoard2.board[0][6] = new Empty(EMPTY, White, 0, 6);
    ChessPiece* pawn2 = chessBoard2.board[0][6] = new Pawn(PAWN, Black, 0, 6);
    CHECK(!chessBoard2.canCastle(0, 4, 0, 7));
}

TEST_CASE("Testing castling logic for black") {
    Board chessBoard;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 

    // black castling kingside
    ChessPiece* rook1 = chessBoard.board[7][7] = new Rook(ROOK, Black, 7, 7);
    ChessPiece* king1 = chessBoard.board[7][4] = new King(KING, Black, 7, 4);
    CHECK(chessBoard.canCastle(7, 4, 7, 7) == true);

    // black castling queenside
    ChessPiece* rook2 = chessBoard.board[7][0] = new Rook(ROOK, Black, 7, 0);
    CHECK(chessBoard.canCastle(7, 4, 7, 0) == true);

    // check if can't castle in check
    ChessPiece* rook3 = chessBoard.board[0][4] = new Rook(ROOK, White, 0, 4);
    CHECK(chessBoard.canCastle(7, 4, 7, 7) == false);
    CHECK(chessBoard.canCastle(7, 4, 7, 0) == false);

    ChessPiece* empty1 = chessBoard.board[0][4] = new Empty(EMPTY, None, 0, 4);
    CHECK(chessBoard.canCastle(7, 4, 7, 7) == true);

    // can't castle through check
    ChessPiece* rook4 = chessBoard.board[0][5] = new Rook(ROOK, White, 0, 5);
    CHECK(chessBoard.canCastle(7, 4, 7, 7) == false);
    CHECK(chessBoard.canCastle(7, 4, 7, 0) == true);

    // can't castle through queen diagonal attack
    ChessPiece* queen1 = chessBoard.board[1][7] = new Queen(QUEEN, White, 1, 7);

    CHECK(chessBoard.isLegalMove(1, 7, 7, 1));
    CHECK(chessBoard.isinCheckSquare(Black, 7, 1));
    CHECK(chessBoard.canCastle(7, 4, 7, 0) == false);


    Board chessBoard2;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard2.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 
    ChessPiece* rook5 = chessBoard2.board[7][7] = new Rook(ROOK, Black, 7, 7);
    ChessPiece* king2 = chessBoard2.board[7][4] = new King(KING, Black, 7, 4);

    // check if doesn't break when trying to castle with non king and rook
    CHECK(!chessBoard2.canCastle(7, 4, 7, 0));

    // check if can't castle when blocked 
    ChessPiece* pawn1 = chessBoard2.board[7][6] = new Pawn(PAWN, Black, 7, 6);
    CHECK(!chessBoard2.isNotBlockedForCastle(7, 4, 7, 7));
    CHECK(chessBoard2.notThroughCheck(7, 4, 7, 7));
    CHECK(!chessBoard2.canCastle(7, 4, 7, 7));

    ChessPiece* empty2 = chessBoard2.board[7][6] = new Empty(EMPTY, None, 7, 6);
    ChessPiece* pawn2 = chessBoard2.board[7][6] = new Pawn(PAWN, White, 7, 6);
    CHECK(!chessBoard2.canCastle(7, 4, 7, 7));
}

//TEST MOVING PIECE, CAPTURING, AND CASTLING NEXT
TEST_CASE("Moving pieces"){
    Board chessBoard;
    chessBoard.initializeBoard();
    chessBoard.board[1][4] = new Pawn(PAWN, White, 1, 4);
    CHECK(chessBoard.isLegalMove(1, 4, 3, 4));
    
    CHECK((chessBoard.board[1][4]->piece == PAWN) == true);
    CHECK((chessBoard.board[1][4]->color == White) == true);
    CHECK(chessBoard.isWhiteTurn);
    // REFACTORED: Use coordinates instead of pointers
    chessBoard.movePiece(1, 4, 3, 4);
    CHECK((chessBoard.board[3][4]->piece == PAWN) == true);
    CHECK((chessBoard.board[3][4]->color == White) == true);
    CHECK((chessBoard.board[1][4]->piece == EMPTY) == true);
    CHECK((chessBoard.board[1][4]->color == None) == true);
    

    //can't move out of turn 
    CHECK(!chessBoard.isWhiteTurn);
    // REFACTORED: Use coordinates instead of pointers
    chessBoard.movePiece(1, 3, 3, 3);
    CHECK((chessBoard.board[1][3]->piece == PAWN) == true);
    CHECK((chessBoard.board[1][3]->color == White) == true);
    CHECK((chessBoard.board[3][3]->piece == EMPTY) == true);
    CHECK((chessBoard.board[3][3]->color == None) == true);
    

    //black move then white pawn capture
    // REFACTORED: Use coordinates instead of pointers
    chessBoard.movePiece(6, 3, 4, 3);
    CHECK((chessBoard.board[4][3]->piece == PAWN) == true);
    CHECK((chessBoard.board[4][3]->color == Black) == true);
    CHECK((chessBoard.board[6][3]->piece == EMPTY) == true);
    CHECK((chessBoard.board[6][3]->color == None) == true);
    
    // REFACTORED: Use coordinates instead of pointers
    chessBoard.movePiece(3, 4, 4, 3);
    CHECK((chessBoard.board[4][3]->piece == PAWN) == true);
    CHECK((chessBoard.board[4][3]->color == White) == true);
    CHECK((chessBoard.board[3][4]->piece == EMPTY) == true);
    CHECK((chessBoard.board[3][4]->color == None) == true);
    

    //qxd5 
    // REFACTORED: Use coordinates instead of pointers
    chessBoard.movePiece(7, 3, 4, 3);
    CHECK((chessBoard.board[4][3]->piece == QUEEN) == true);
    CHECK((chessBoard.board[4][3]->color == Black) == true);
    CHECK((chessBoard.board[7][3]->piece == EMPTY) == true);
    CHECK((chessBoard.board[7][3]->color == None) == true);
}

TEST_CASE("Testing more moves"){
    //can't move to own piece
    Board chessBoard;
    chessBoard.initializeBoard();
    // REFACTORED: Use coordinates instead of pointers
    chessBoard.movePiece(0, 3, 1, 3);
    CHECK((chessBoard.board[0][3]->piece == QUEEN) == true);
    CHECK((chessBoard.board[0][3]->color == White) == true);
    CHECK((chessBoard.board[1][3]->piece == PAWN) == true);
    CHECK((chessBoard.board[1][3]->color == White) == true);
    
    // REFACTORED: Use coordinates instead of pointers
    chessBoard.movePiece(1, 3, 3, 3);
    chessBoard.movePiece(6, 4, 4, 4);
    chessBoard.movePiece(0, 3, 2, 3);
    chessBoard.movePiece(7, 6, 5, 5);
    chessBoard.movePiece(0, 2, 2, 4);
    chessBoard.movePiece(7, 5, 6, 4);
    chessBoard.movePiece(0, 1, 2, 2);
    //testing if making an illegal move just returns and doesn't end the turn
    // REFACTORED: Use coordinates instead of pointers
    chessBoard.castle(7, 4, 7, 0);
    chessBoard.castle(7, 4, 7, 7);
    chessBoard.castle(0, 4, 0, 0);
    chessBoard.movePiece(4, 4, 3, 3);
    //chessBoard.printBoard();
    

    //chessBoard.castle();

}

TEST_CASE("Test enpassant"){
    Board chessBoard;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 
    chessBoard.isWhiteTurn = false;

    ChessPiece* pawn1 = chessBoard.board[4][4] = new Pawn(PAWN, White, 4, 4);
    ChessPiece* pawn2 = chessBoard.board[6][5] = new Pawn(PAWN, Black, 6, 5);
    CHECK(!chessBoard.isLegalMove(4, 4, 5, 5));
    // REFACTORED: Use coordinates instead of pointers
    chessBoard.movePiece(6, 5, 4, 5);
    CHECK(chessBoard.board[5][5]->piece == EMPTY);
    CHECK(chessBoard.board[5][5]->color == None);
    CHECK(chessBoard.board[5][5]->enPassantSquare == true);
    CHECK(chessBoard.isLegalMove(4, 4, 5, 5));
    // REFACTORED: Use coordinates instead of pointers
    chessBoard.movePiece(4, 4, 5, 5);
    CHECK(chessBoard.board[5][5]->piece == PAWN);
    CHECK(chessBoard.board[5][5]->color == White);
    CHECK(chessBoard.board[4][5]->piece == EMPTY);
    CHECK(chessBoard.board[4][5]->color == None);

    Board chessBoard2;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard2.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 
    
    chessBoard2.isWhiteTurn = false;

    ChessPiece* pawn3 = chessBoard2.board[4][4] = new Pawn(PAWN, White, 4, 4);
    ChessPiece* pawn4 = chessBoard2.board[6][5] = new Pawn(PAWN, Black, 6, 5);
    ChessPiece* rook1 = chessBoard2.board[7][7] = new Rook(ROOK, White, 7, 7);
    ChessPiece* rook2 = chessBoard2.board[0][0] = new Rook(ROOK, Black, 0, 0);

    // REFACTORED: Use coordinates instead of pointers
    chessBoard2.movePiece(6, 5, 4, 5);
    CHECK(chessBoard2.isLegalMove(4, 4, 5, 5));
    chessBoard2.movePiece(7, 7, 7, 0);
    chessBoard2.movePiece(0, 0, 0, 7);
    CHECK(!chessBoard2.isLegalMove(4, 4, 5, 5));
    chessBoard2.movePiece(4, 4, 5, 5);
    CHECK(chessBoard2.isWhiteTurn == true);
}

TEST_CASE("Checkmate") {
    Board chessBoard;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 

    //is in checkmate
    chessBoard.board[7][7] = new King(KING, White, 7, 7);
    chessBoard.board[7][0] = new Rook(ROOK, Black, 7, 0);
    chessBoard.board[6][0] = new Rook(ROOK, Black, 6, 0);

    chessBoard.checkForCheckmate(White);
    CHECK(chessBoard.whiteKingisCheckmated == true);

    //can get out of checkmate by capturing with king
    Board chessBoard2;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard2.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 
    chessBoard2.board[7][7] = new King(KING, Black, 7, 7);
    chessBoard2.board[7][0] = new Rook(ROOK, White, 7, 0);
    chessBoard2.board[6][6] = new Rook(ROOK, White, 6, 6);

    chessBoard2.checkForCheckmate(Black);
    CHECK(chessBoard2.blackKingisCheckmated == false);
    CHECK(chessBoard2.isStalemate == false);

    //can get out of checkmate by capturing with another piece

}

TEST_CASE("Fixing problems with basic moves") {
    Board chessBoard;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 

    chessBoard.isWhiteTurn = false;

    ChessPiece* rook1 = chessBoard.board[7][7] = new Rook(ROOK, White, 7, 7);
    ChessPiece* king1 = chessBoard.board[7][4] = new King(KING, Black, 7, 4);
    ChessPiece* bishop1 = chessBoard.board[7][5] = new Bishop(BISHOP, Black, 7, 5);
    ChessPiece* knight1 = chessBoard.board[6][4] = new Knight(KNIGHT, Black, 6, 4);

    CHECK(chessBoard.isLegalMove(6, 4, 7, 6));
    CHECK(rook1->isinRow(7, 4) == true);
    CHECK(chessBoard.isNotBlockedRow(7, 7, 7, 4) == false);
    CHECK(chessBoard.isinCheck(7, 4) == false);
    CHECK(chessBoard.isLegalMove(7, 7, 7, 4) == false);
    CHECK(chessBoard.isNotBlocked(7, 7, 7, 4) == false);

}

//NEED TO IMPLEMENT STALEMATE, CHECKMATE, 
TEST_CASE("Stalemate") {
    Board chessBoard;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 

    //is in stalemate
    chessBoard.board[7][7] = new King(KING, White, 7, 7);
    chessBoard.board[5][6] = new Queen(QUEEN, Black, 5, 6);
    chessBoard.board[6][5] = new Rook(ROOK, Black, 6, 5);

    chessBoard.checkForCheckmate(White);
    CHECK(chessBoard.isStalemate == true);

    Board chessBoard2;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard2.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 

    //is in stalemate
    chessBoard2.board[7][7] = new King(KING, White, 7, 7);
    chessBoard2.board[5][6] = new Queen(QUEEN, Black, 5, 6);
    chessBoard2.board[6][5] = new Rook(ROOK, Black, 6, 5);

    chessBoard2.board[1][1] = new Pawn(PAWN, White, 1, 1);
    chessBoard2.checkForCheckmate(White);
    CHECK(chessBoard2.isStalemate == false);

}

TEST_CASE("FEN Castling Rights") {
    Board chessBoard;
    chessBoard.initializeBoard();
    CHECK(chessBoard.board[0][4]->returnCastlingRights() == true);
    CHECK(chessBoard.board[0][0]->returnCastlingRights() == true);
    CHECK(chessBoard.board[0][7]->returnCastlingRights() == true);
    CHECK(chessBoard.board[7][4]->returnCastlingRights() == true);
    CHECK(chessBoard.board[7][0]->returnCastlingRights() == true);
    CHECK(chessBoard.board[7][7]->returnCastlingRights() == true);
}

TEST_CASE("Test FEN") {
    Board chessBoard;
    for(int row = 0; row < 8; row++) {
        for(int col = 0; col < 8; col++) {
            chessBoard.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    } 

    ChessPiece* pawn1 = chessBoard.board[1][4] = new Pawn(PAWN, White, 1, 4);
    ChessPiece* pawn2 = chessBoard.board[3][5] = new Pawn(PAWN, Black, 3, 5);
    CHECK(chessBoard.board[2][4]->enPassantSquare == false);

    chessBoard.movePiece(1, 4, 3, 4);
    CHECK(chessBoard.board[3][4]->piece == PAWN);
    CHECK(chessBoard.board[2][4]->enPassantSquare == true);
    CHECK(chessBoard.getFEN() == "8/8/8/8/4Pp2/8/8/8 b - e3 1 1");

    chessBoard.movePiece(3, 5, 2, 4);
    CHECK(chessBoard.board[2][4]->piece == PAWN);
    CHECK(chessBoard.board[2][4]->color == Black);
    CHECK(chessBoard.board[2][4]->enPassantSquare == false);
    CHECK(chessBoard.getFEN() == "8/8/8/8/8/4p3/8/8 w - - 0 2");
}

TEST_CASE("Promote Pawn") {
    Board chessBoard;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            chessBoard.board[row][col] = new Empty(EMPTY, None, row, col);
        }
    }

    ChessPiece* pawn1 = chessBoard.board[6][0] = new Pawn(PAWN, White, 6, 0);
    chessBoard.movePiece(6, 0, 7, 0);
    CHECK(chessBoard.board[7][0]->piece == QUEEN);
    CHECK(chessBoard.board[7][0]->color == White);

    //black pawn promotion
    ChessPiece* pawn2 = chessBoard.board[1][7] = new Pawn(PAWN, Black, 1, 7);
    chessBoard.movePiece(1, 7, 0, 7);
    CHECK(chessBoard.board[0][7]->piece == QUEEN);
    CHECK(chessBoard.board[0][7]->color == Black);

    //doesn't promote if piece is not pawn
    ChessPiece* rook1 = chessBoard.board[6][1] = new Rook(ROOK, White, 6, 1);
    chessBoard.movePiece(6, 1, 7, 1);
    CHECK(chessBoard.board[7][1]->piece == ROOK);
    CHECK(chessBoard.board[7][1]->color == White);
}