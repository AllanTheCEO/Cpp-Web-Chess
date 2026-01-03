#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "src/engine/engine.cpp"

//Will comment and uncomment testcases to run specific tests.
//We will debug on depth 3-4 only before the engine gets faster.
//Will test certain edge cases separately until engine gets faster.

//Test engine with perft results of known positions from https://www.chessprogramming.org/Perft_Results
// TEST_CASE("Test #nodes correctness") {
//     Board chessBoard = Board();
//     //starting position
//     chessBoard.initializeBoard();
//     chessBoard.parseFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
//     Engine engine = Engine();
//     CHECK(engine.perft(chessBoard, engine, 1) == 20);
//     CHECK(engine.perft(chessBoard, engine, 2) == 400);
//     CHECK(engine.perft(chessBoard, engine, 3) == 8902);
//     CHECK(engine.perft(chessBoard, engine, 4) == 197281);
// }

// TEST_CASE("Test #nodes correctness Position 2") {
//     Board chessBoard = Board();
//     //position 2
//     chessBoard.initializeBoard();
//     chessBoard.parseFEN("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1");
//     Engine engine = Engine();
//     CHECK(engine.perft(chessBoard, engine, 1) == 48);
//     CHECK(engine.perft(chessBoard, engine, 2) == 2039);
    

//     const std::uint64_t got3 = engine.perft(chessBoard, engine, 3);
//     CHECK(got3 == 97862);
//     const std::uint64_t exp3 = 97862;
//     if (got3 != exp3) {
//         std::cout << "Perft depth 3 mismatch: got " << got3 << " expected " << exp3 << "\n";
//         engine.divide(chessBoard, engine, 3);
//     }

//     //CHECK(engine.perft(chessBoard, engine, 4) == 4085603);
// }

// TEST_CASE("Test #nodes correctness Position 3") {
//     Board chessBoard = Board();
//     //position 3
//     chessBoard.initializeBoard();
//     chessBoard.parseFEN("8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - - 0 1");
//     Engine engine = Engine();
//     CHECK(engine.perft(chessBoard, engine, 1) == 14);
//     CHECK(engine.perft(chessBoard, engine, 2) == 191);
//     CHECK(engine.perft(chessBoard, engine, 3) == 2812);
//     CHECK(engine.perft(chessBoard, engine, 4) == 43238);
// }

// TEST_CASE("Test #nodes correctness Position 4") {
//     Board chessBoard = Board();
//     //position 4
//     chessBoard.initializeBoard();
//     chessBoard.parseFEN("r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1");
//     Engine engine = Engine();
//     CHECK(engine.perft(chessBoard, engine, 1) == 6);
//     CHECK(engine.perft(chessBoard, engine, 2) == 264);
//     CHECK(engine.perft(chessBoard, engine, 3) == 9467);
//     //CHECK(engine.perft(chessBoard, engine, 4) == 422333);
// }

TEST_CASE("Test #nodes correctness Position 5") {
    Board chessBoard = Board();
    //position 5
    chessBoard.initializeBoard();
    chessBoard.parseFEN("rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8");
    Engine engine = Engine();
    CHECK(engine.perft(chessBoard, engine, 1) == 44);
    CHECK(engine.perft(chessBoard, engine, 2) == 1486);
    
    const std::uint64_t got3 = engine.perft(chessBoard, engine, 3);
    CHECK(got3 == 62379);
    const std::uint64_t exp3 = 62379;
    if (got3 != exp3) {
        std::cout << "Perft depth 3 mismatch: got " << got3 << " expected " << exp3 << "\n";
        engine.divide(chessBoard, engine, 3);
    }
}

// TEST_CASE("Test #nodes correctness Position 6") {
//     Board chessBoard = Board();
//     //position 6
//     chessBoard.initializeBoard();
//     chessBoard.parseFEN("r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10");
//     Engine engine = Engine();
//     CHECK(engine.perft(chessBoard, engine, 1) == 46);
//     CHECK(engine.perft(chessBoard, engine, 2) == 2079);
//     CHECK(engine.perft(chessBoard, engine, 3) == 89890);
//     //CHECK(engine.perft(chessBoard, engine, 4) == 3894594);
// }