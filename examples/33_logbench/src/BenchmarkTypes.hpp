#ifndef AREG_LOG_BENCHMARK_TYPES
#define AREG_LOG_BENCHMARK_TYPES


#include <vector>
#include <cstdint>
/**
 * Indicates the sampling function to use
 */
enum class SampleType
{
    LogScope,
    DebugString,
    DebugOneArg,
    DebugTwoArg,
    DebugThreeMixedArg,
    DebugTenMixedArg,
    DebugLongString,

};

enum class OutputDestination
{
    File,
    Database,
    Collector,
    All
};

/**
 * Contains the settings of the benchmark, used in the construction of the BenchmarkRunner object
 */
struct BenchmarkConfig 
{
    int nSessions = 1;
    int nSamples = 10000;
    int nThreads = 8;
    int nWarmUps = 0;
    OutputDestination outDest = OutputDestination::All;

    SampleType sampleType = SampleType::LogScope;
    int maxArgs = 8;
    int nIntArgs = 4;
    int nFloatArgs = 2;
    int nStringArgs = 2;
    int strArgLen = 16;
    
};


/**
 * Stores stats from a single session
 */
struct SessionResult
{
    
    BenchmarkConfig cfg;
    int sessionID = -1;
    double _min = { 0.0 };
    double _max = { 0.0 };
    double _mean = { 0.0 };
    double _p50 = { 0.0 };
    double _p90 = { 0.0 };
    double _p99 = { 0.0 };
    double _p999 = { 0.0 };
    double _sd = { 0.0 };
    double clockSpeedNs = { 0.0 };
};


#endif