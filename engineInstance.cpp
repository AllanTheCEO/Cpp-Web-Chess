#include "src/engine/engine.cpp"

int main() {
    int depth = 1;
    clock_t start = clock();
    Board b = Board();
    b.initializeBoard();
    Engine engine = Engine();
    std::tuple<double, std::string> result = engine.minimax(b, depth, -100000, 100000);
    std::cout << "Best move: " << std::get<1>(result) << ", Best value: " << std::get<0>(result);
    std::cout << std::endl;
    engine.engineMove(b, std::get<1>(result), b.isWhiteTurn ? White : Black);
    b.printBoard();

    std::tuple<double, std::string> result2 = engine.minimax(b, depth, -100000, 100000);
    std::cout << "Best move: " << std::get<1>(result2) << ", Best value: " << std::get<0>(result2);
    std::cout << std::endl;
    engine.engineMove(b, std::get<1>(result2), b.isWhiteTurn ? White : Black);
    b.printBoard();
    clock_t end = clock();
    double elapsed_time = ((double)(end - start)) / CLOCKS_PER_SEC;
    std::cout << "Execution time: " << elapsed_time << " seconds" << std::endl;
    
    return 0;
}
