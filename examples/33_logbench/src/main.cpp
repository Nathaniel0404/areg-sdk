#include "BenchmarkRunner.hpp"
#include "InputParser.hpp"


int main(int argc, char * argv[]) 
{
    std::vector<std::string> argList;
    if (argc > 1) { 
        for (int i = 1; i < argc; i++) {
            if (argv[i][0] != '-' || argv[i][1] < 'a' || argv[i][1] > 'z') {
                std::cout << "Input error, try again." << std::endl;
                return 1;
            } else {
                argList.push_back(std::string(argv[i]));
            }
        }
    }
    BenchmarkConfig cfg = InputParser::parseInput(argList);
    
    std::cout << cfg.nSessions << " " << cfg.nSamples << std::endl;
    BenchmarkRunner runner(5, 1000, SampleType::DebugString);
    runner.init_benchmark();
    runner.run_benchmark();
    return 0;
}