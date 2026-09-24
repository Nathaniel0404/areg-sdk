#ifndef AREG_LOG_BENCHMARK_RUNNER
#define AREG_LOG_BENCHMARK_RUNNER

#include "areg/base/areg_global.h"
#include "areg/base/ThreadConsumer.hpp"
#include "areg/base/String.hpp"
#include "areg/base/Thread.hpp"

#include "areg/logging/areg_log.h"

#include <vector>
#include <cstdint>

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
 * Stores raw data from a benchmark session
 */
struct SessionResult
{
    std::vector<u_int64_t> sampleLatency; // Stores the latency recorded for each sample
};


/**
 * Runs logging performance benchmarks and collects their results.
 */

class BenchmarkRunner

{

private:

    int nSessions; // Number of benchmark sessions to run
    int nSamples; // Number of samples per benchmark session
    SampleType sampleType; // Type of sample being collected

    std::vector<uint64_t> sessionResult; // Holds result of each sample in a single sessions

public:

    // Constructor

    BenchmarkRunner(int nSessions, int nSamples, SampleType sType);

    // Benchmarking Functions

    void init_benchmark();

    SessionResult run_single_session();

    uint64_t run_sample(SampleType sType);

    void run_benchmark();

    // Sample Functions

    uint64_t now_ns();

    uint64_t bench_log_scope();

    uint64_t bench_dbg_string();

    uint64_t bench_dbg_1_arg();




};



#endif