#include "src/InputParser.hpp"


BenchmarkConfig InputParser::parseInput(std::vector<std::string> args) {
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
        if (p.flag == "l") {
            int n = stoi(p.value);
            cfg.nSamples = n;
        } else if (p.flag == "sn") {
            int n = stoi(p.value);
            cfg.nSessions = n;
        } else if (p.flag == "msg") {
            int n = stoi(p.value);
            switch(n) {
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
                    break;
            }
        }
    }    
    return cfg;
}