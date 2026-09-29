#include "src/ResultProcessor.hpp"
#include <numeric>

namespace {
    constexpr double NS_PER_US{ 1000.0 };

    double _percentile_us(const std::vector<uint64_t> & sorted, double fraction)
    {
        if (sorted.empty())
            return 0.0;

        size_t index{ static_cast<size_t>(fraction * static_cast<double>(sorted.size())) };
        if (index >= sorted.size())
            index = sorted.size() - 1u;

        return static_cast<double>(sorted[index]) / NS_PER_US;
    }
}

SessionResult ResultProcessor::summarize(std::vector<uint64_t> samples, BenchmarkConfig cfg, SampleType sType, double clockSpeedNs) {
    sort(samples.begin(), samples.end()); 
    SessionResult result;
    result._max = samples.back() / NS_PER_US;
    result._min = samples.front() / NS_PER_US;
    result._mean = (std::accumulate(samples.begin(),samples.end(),0) / cfg.nSamples) / NS_PER_US;
    result._p50 = _percentile_us(samples, 0.5);
    result._p90 = _percentile_us(samples, 0.9);
    result._p99 = _percentile_us(samples, 0.99);
    result._p999 = _percentile_us(samples, 0.999);
    result.cfg = cfg;
    result.sType = sType;
    result.clockSpeedNs = clockSpeedNs / NS_PER_US;

    double squaredDiffSum = 0.0;

    for (uint64_t sample : samples)
    {
        double diff = static_cast<double>(sample) - result._mean;
        squaredDiffSum += diff * diff;
    }

    result._sd = std::sqrt(squaredDiffSum / samples.size());

    return result;
}

