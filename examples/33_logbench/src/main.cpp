#include "BenchmarkRunner.hpp"
#include "InputParser.hpp"


int main(int argc, char * argv[]) 
{
    
    
    try {
        BenchmarkConfig cfg = InputParser::parseInput(argc, argv);
        BenchmarkRunner runner(cfg);
        runner.init_benchmark();
        runner.run_benchmark();
    } catch (const std::exception& e) {
        std::cerr << "Invalid input: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}