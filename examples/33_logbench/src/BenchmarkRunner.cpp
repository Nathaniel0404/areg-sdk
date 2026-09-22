#include "BenchmarkRunner.hpp"

#include <chrono>
#include <iostream>
#include <numeric>

DEF_LOG_SCOPE(logging_bench, bench_log_scope);
DEF_LOG_SCOPE(logging_bench, bench_dbg_string);
DEF_LOG_SCOPE(logging_bench, bench_dbg_1_arg);

BenchmarkRunner::BenchmarkRunner(int nSessions, int nSamples)
    : nSessions(nSessions),
      nSamples(nSamples)
{
}

void BenchmarkRunner::init_benchmark() {
    sessionResult = {};
}

void BenchmarkRunner::run_benchmark() {
    for (int i = 0; i < nSessions; i++) {
        run_single_session();
        uint64_t aveTime = std::accumulate(sessionResult.begin(),sessionResult.end(),0) / nSamples;
        std::cout << i+1 << " session: "<< aveTime << std::endl;
        init_benchmark();
    }
}

void BenchmarkRunner::run_single_session() {
    for (int i = 0; i < nSamples; i++) {
        uint64_t sampleTime = run_sample();
        sessionResult.push_back(sampleTime);
    }
}

uint64_t BenchmarkRunner::run_sample() {
    return bench_log_scope();
}


uint64_t BenchmarkRunner::now_ns() {
    return static_cast<uint64_t>(
        std::chrono::duration_cast<std::chrono::nanoseconds>(
            std::chrono::steady_clock::now().time_since_epoch()
        ).count()
        );
}

uint64_t BenchmarkRunner::bench_log_scope() {
    uint64_t begin = now_ns();
    LOG_SCOPE(logging_bench, bench_log_scope);
    uint64_t end = now_ns();
    return end - begin;
}

uint64_t BenchmarkRunner::bench_dbg_string() 
{
    LOG_SCOPE(logging_bench, bench_dbg_string);
    uint64_t begin = now_ns();
    LOG_DBG("Hello World!");
    uint64_t end = now_ns();
    return end - begin;
}

uint64_t BenchmarkRunner::bench_dbg_1_arg() 
{
    LOG_SCOPE(logging_bench, bench_dbg_1_arg);
    int num1 = 11;
    uint64_t begin = now_ns();
    LOG_DBG("Value = %d",num1);
    uint64_t end = now_ns();
    return end - begin;
}
