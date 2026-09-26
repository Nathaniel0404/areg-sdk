#include "src/InputParser.hpp"


BenchmarkConfig InputParser::parseInput(int argc, char* argv[]) {
    std::vector<std::string> args;
    for (int i = 1; i < argc; i++) {
            if (argv[i][0] != '-' || argv[i][1] < 'a' || argv[i][1] > 'z') {
                throw std::invalid_argument("Invalid input!");
            } else {
                args.push_back(std::string(argv[i]));
            }
        }
    std::vector<ParsedArg> pList;
    for (std::string arg : args) {
        int pos = 1;
        while (pos < arg.size() && arg[pos] >= 'a' && arg[pos] <= 'z') {
            pos++;
        }
        ParsedArg p;
        p.flag = arg.substr(1,pos-1);
        if (arg[pos] == '=') {
            pos++;
            while (pos < arg.size()) {
                p.value.push_back(arg[pos]);
                pos++;
            }
        }
        pList.push_back(p);
    }
    return buildConfig(pList);
}

BenchmarkConfig InputParser::buildConfig(std::vector<ParsedArg> pList) {
    BenchmarkConfig cfg;
    for (ParsedArg p : pList) {
        int argVal;
        if (p.flag == "l" || p.flag == "sn" || p.flag == "msg" || p.flag == "w") {
            try {
                argVal = stoi(p.value);
            } catch (const std::invalid_argument&) {
                throw std::invalid_argument("Flag value must be an integer!");
            } catch (const std::out_of_range&) {
                throw std::invalid_argument("Integer is too large!");
            }
        }
        if (p.flag == "l") {
            argVal = stoi(p.value);
            if (argVal < 1000 || argVal > 100000) {
                throw std::out_of_range("Number of loops must be between 1000 and 100,000!");
            }
            cfg.nSamples = argVal;
        } else if (p.flag == "sn") {
            argVal = stoi(p.value);
            if (argVal < 1 || argVal > 20) {
                throw std::out_of_range("Number of sessions must be between 1 and 20!");
            }
            cfg.nSessions = argVal;
        } else if (p.flag == "msg") {
            argVal = stoi(p.value);
            switch(argVal) {
                case 1: 
                    cfg.sampleType = SampleType::LogScope;
                    break;
                case 2:
                    cfg.sampleType = SampleType::DebugString;
                    break;
                case 3:
                    cfg.sampleType = SampleType::DebugOneArg;
                    break;
                default:
                    throw std::invalid_argument("Invalid message type");
                    break;
            }
        } else if (p.flag == "w") {
            argVal = stoi(p.value);
            if (argVal < 0 || argVal > 100) {
                throw std::out_of_range("Number of warm-up sessions must be between 0 and 100!");
            }
            cfg.nWarmUps = argVal;
        } else {
            throw std::invalid_argument("Unknown flag found!");
        }
    }    
    return cfg;
}