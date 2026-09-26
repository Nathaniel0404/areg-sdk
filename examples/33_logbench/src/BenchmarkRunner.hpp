#ifndef AREG_LOG_BENCHMARK_RUNNER
#define AREG_LOG_BENCHMARK_RUNNER


#include "areg/logging/areg_log.h"
#include "src/BenchmarkTypes.hpp"

#include <vector>
#include <cstdint>





/**
 * Runs logging performance benchmarks and collects their results.
 */

class BenchmarkRunner

{

private:

    BenchmarkConfig cfg;

    std::vector<uint64_t> samples; // Holds result of each sample in a single sessions


public:

    // Constructor
    
    BenchmarkRunner(BenchmarkConfig cfg);

    // Benchmarking Functions

    void init_benchmark();

    void run_single_session();

    uint64_t run_sample(SampleType sType);

    void run_benchmark();

    // Sample Functions
private:
    uint64_t now_ns();

    uint64_t bench_log_scope();

    uint64_t bench_dbg_string();

    uint64_t bench_dbg_1_arg();

    uint64_t bench_dbg_2_arg();

    uint64_t bench_dbg_3_mixed();

    uint64_t bench_dbg_10_mixed();

    uint64_t bench_long_string();


};



#endif