#include "src/BenchmarkRunner.hpp"
#include "src/ResultProcessor.hpp"

#include <chrono>
#include <iostream>
#include <numeric>
#include <iomanip>


DEF_LOG_SCOPE(logging_bench, bench_log_scope);
DEF_LOG_SCOPE(logging_bench, bench_dbg_string);
DEF_LOG_SCOPE(logging_bench, bench_dbg_1_arg);

namespace {

void visualise_header()
{
    std::cout
        << "+-----+----------+----------+----------+----------+----------+----------+----------+----------+\n"
        << "|  #  |  Min(ns) |  Max(ns) | Mean(ns) |  P50(ns) |  P90(ns) |  P99(ns)   P999(ns) |       SD |\n"
        << "+-----+----------+----------+----------+----------+----------+----------+----------+----------+\n";
}

void visualise_results(const SessionResult& results)
{
    std::cout
        << "| " << std::setw(3) << results.sessionID
        << " | " << std::setw(8) << results._min
        << " | " << std::setw(8) << results._max
        << " | " << std::setw(8) << std::fixed << std::setprecision(2) << results._mean
        << " | " << std::setw(8) << results._p50
        << " | " << std::setw(8) << results._p90
        << " | " << std::setw(8) << results._p99
        << " | " << std::setw(8) << results._p999
        << " | " << std::setw(8) << results._sd
        << " |\n";
}

void visualise_footer()
{
    std::cout
        << "+-----+----------+----------+----------+----------+----------+----------+----------+----------+\n";
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
    visualise_header();
    for (int i = 0; i < cfg.nWarmUps; i++) {
        run_single_session();
        init_benchmark();
    }

    for (int i = 0; i < cfg.nSessions; i++) {
        run_single_session();
        SessionResult results = ResultProcessor::summarize(samples, cfg, i+1);
        visualise_results(results);
        init_benchmark();
    }
    visualise_footer();
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
