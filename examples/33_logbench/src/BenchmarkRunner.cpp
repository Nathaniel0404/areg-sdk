#include "src/BenchmarkRunner.hpp"
#include "src/ResultProcessor.hpp"

#include <chrono>
#include <iostream>
#include <numeric>

DEF_LOG_SCOPE(logging_bench, bench_log_scope);
DEF_LOG_SCOPE(logging_bench, bench_dbg_string);
DEF_LOG_SCOPE(logging_bench, bench_dbg_1_arg);

namespace {
    void visualise_results(SessionResult results) {
        std::cout << "--------------------------------" << std::endl;
        std::cout << "Session ID: " << results.sessionID << std::endl;
        std::cout << "Min: " << results._min << std::endl;
        std::cout << "Max: " << results._max << std::endl;
        std::cout << "Mean: " << results._mean << std::endl;
        std::cout << "P50: " << results._p50 << std::endl;
        std::cout << "P90: " << results._p90 << std::endl;
        std::cout << "P99: " << results._p99 << std::endl;
        std::cout << "P999: " << results._p999 << std::endl;
        std::cout << "SD: " << results._sd << std::endl;
        std::cout << "--------------------------------" << std::endl;
    }
}
BenchmarkRunner::BenchmarkRunner(BenchmarkConfig cfg)
    : cfg(cfg)
{
}

void BenchmarkRunner::init_benchmark() {
    samples = {};
}

void BenchmarkRunner::run_benchmark() {
    for (int i = 0; i < cfg.nSessions; i++) {
        run_single_session();
        SessionResult results = ResultProcessor::summarize(samples, cfg, i+1);
        visualise_results(results);
        init_benchmark();
    }
}

void BenchmarkRunner::run_single_session() {
    for (int i = 0; i < cfg.nSamples; i++) {
        uint64_t sampleTime = run_sample(cfg.sampleType);
        samples.push_back(sampleTime);
    }
    
}

uint64_t BenchmarkRunner::run_sample(SampleType sType) {
    uint64_t sample;
    switch (sType)
    {
    case SampleType::LogScope:
        sample = bench_log_scope();
        break;

    case SampleType::DebugString:
        sample = bench_dbg_string();
        break;
    
    case SampleType::DebugOneArg:
        sample = bench_dbg_1_arg();
        break;
    
    default:
        break;
    }
    return sample;
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
