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

/**
 * Contains the settings of the benchmark, used in the construction of the BenchmarkRunner object
 */
struct BenchmarkConfig 
{
    int nSessions = 1;
    int nSamples = 1000;
    int nWarmUps = 0;
    SampleType sampleType = SampleType::LogScope;
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
};


#endif