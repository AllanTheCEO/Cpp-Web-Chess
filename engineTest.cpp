#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "src/engine/engine.cpp"

//Will comment and uncomment testcases to run specific tests.
//We will debug on depth 3-4 only before the engine gets faster.
//Will test certain edge cases separately until engine gets faster.

//Test engine with perft results of known positions from https://www.chessprogramming.org/Perft_Results
TEST_CASE("Test #nodes correctness") {
    Board chessBoard = Board();
    //starting position
    chessBoard.initializeBoard();
    chessBoard.parseFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    Engine engine = Engine();
    CHECK(engine.perft(chessBoard, engine, 1) == 20);
    CHECK(engine.perft(chessBoard, engine, 2) == 400);
    CHECK(engine.perft(chessBoard, engine, 3) == 8902);
    CHECK(engine.perft(chessBoard, engine, 4) == 197281);

    const std::uint64_t got4 = engine.perft(chessBoard, engine, 4);
    const std::uint64_t exp4 = 197281;

    if (got4 != exp4) {
        std::cout << "Perft depth 4 mismatch: got " << got4 << " expected " << exp4 << "\n";
        engine.divide(chessBoard, engine, 4);
    }

}

TEST_CASE("Test #nodes correctness Position 2") {
    Board chessBoard = Board();
    //position 2
    chessBoard.initializeBoard();
    chessBoard.parseFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
    Engine engine = Engine();
    CHECK(engine.perft(chessBoard, engine, 1) == 48);
    CHECK(engine.perft(chessBoard, engine, 2) == 2039);
    CHECK(engine.perft(chessBoard, engine, 3) == 97862);

    const std::uint64_t got3 = engine.perft(chessBoard, engine, 3);
    const std::uint64_t exp3 = 97862;
    if (got3 != exp3) {
        std::cout << "Perft depth 3 mismatch: got " << got3 << " expected " << exp3 << "\n";
        engine.divide(chessBoard, engine, 3);
    }

    //CHECK(engine.perft(chessBoard, engine, 4) == 4085603);
}