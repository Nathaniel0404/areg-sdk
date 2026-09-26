#include "src/ResultProcessor.hpp"
#include <numeric>

namespace {
    double _percentile(const std::vector<uint64_t> & sorted, double fraction)
    {
        if (sorted.empty())
            return 0.0;

        size_t index{ static_cast<size_t>(fraction * static_cast<double>(sorted.size())) };
        if (index >= sorted.size())
            index = sorted.size() - 1u;

        return static_cast<double>(sorted[index]);
    }
}

SessionResult ResultProcessor::summarize(std::vector<uint64_t> samples, BenchmarkConfig cfg) {
    sort(samples.begin(), samples.end()); 
    SessionResult result;
    result._max = samples.back();
    result._min = samples.front();
    result._mean = std::accumulate(samples.begin(),samples.end(),0) / cfg.nSamples;
    result._p50 = _percentile(samples, 0.5);
    result._p90 = _percentile(samples, 0.9);
    result._p99 = _percentile(samples, 0.99);
    result._p999 = _percentile(samples, 0.999);
    result.cfg = cfg;
    return result;
}

