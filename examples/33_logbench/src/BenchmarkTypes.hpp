#ifndef AREG_LOG_BENCHMARK_TYPES
#define AREG_LOG_BENCHMARK_TYPES

/**
 * Indicates the sampling function to use
 */
enum class SampleType
{
    LogScope,
    DebugString,
    DebugOneArg
};

/**
 * Contains the settings of the benchmark, used in the construction of the BenchmarkRunner object
 */
struct BenchmarkConfig 
{
    int nSessions=1;
    int nSamples=1000;
    SampleType sampleType=SampleType::LogScope;
};

#endif