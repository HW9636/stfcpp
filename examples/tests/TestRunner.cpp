#ifdef STFCPP_BUILD_TESTS
#ifdef STFCPP_BUILD_EXAMPLES
#error Cannot build both tests and examples
#endif
#include "stfcpp/stfcpp.h"
#include "stfcpp/benchmark.h"

int main(int argc, char** argv)
{
    const auto& suite_results = STF_RUN_SUITE_TESTS();
    stfcpp::print_suite_test_details(suite_results);
    
    // Benchmark
    stfcpp::benchmark::run_benchmarks();
}

#endif
