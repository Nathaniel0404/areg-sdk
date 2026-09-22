#include "areg/base/areg_global.h"
#include "areg/base/ThreadConsumer.hpp"
#include "areg/base/String.hpp"
#include "areg/base/Thread.hpp"

#include "areg/logging/areg_log.h"
#include "BenchmarkRunner.hpp"


int main(int argc, char * argv[]) 
{
    BenchmarkRunner runner(5,1000);
    runner.init_benchmark();
    runner.run_benchmark();
    return 0;
}