#pragma once
#include "stfcpp.h"

#include <sstream>

#define __STF_SUITE_TO_VAR_NAME(suite_name) __stf__test_suite_##suite_name

namespace stfcpp
{
    namespace benchmark
    {
        void empty_function() {

        }

        void assert_true_function()
        {
            static bool a = true;
            static bool b = true;
            STF_BASIC_ASSERT(a, b);
        }

        void assert_false_function()
        {
            static bool a = true;
            static bool b = false;
            STF_BASIC_ASSERT(a, b);
        }

    // Functions for benchmarking
        STF_TEST_SUITE(empty_suite) {
            
        };

        STF_TEST_SUITE(empty_function_10) {
            
            STF_SUITE_TEST_LAMBDA(empty_test_1, [this]() {});
            STF_SUITE_TEST_LAMBDA(empty_test_2, [this]() {});
            STF_SUITE_TEST_LAMBDA(empty_test_3, [this]() {});
            STF_SUITE_TEST_LAMBDA(empty_test_4, [this]() {});
            STF_SUITE_TEST_LAMBDA(empty_test_5, [this]() {});
            STF_SUITE_TEST_LAMBDA(empty_test_6, [this]() {});
            STF_SUITE_TEST_LAMBDA(empty_test_7, [this]() {});
            STF_SUITE_TEST_LAMBDA(empty_test_8, [this]() {});
            STF_SUITE_TEST_LAMBDA(empty_test_9, [this]() {});
            STF_SUITE_TEST_LAMBDA(empty_test_10, [this]() {});
        };

        struct results
        {
            unsigned int ran_empty;
            unsigned int ran_passed;
            unsigned int ran_failed;
            std::chrono::nanoseconds empty_duration;
            std::chrono::nanoseconds passed_duration;
            std::chrono::nanoseconds failed_duration;
        };
    
        inline void run_benchmarks(unsigned int n = 10000)
        {
            results basic_test_results = {
                0, 0, 0, std::chrono::nanoseconds(0), std::chrono::nanoseconds(0), std::chrono::nanoseconds(0)
            };
            // basic test benchmark 
            std::chrono::steady_clock::time_point start, end;
            for (unsigned int i = 0; i < n; ++i)
            {
                start = std::chrono::high_resolution_clock::now();
                basic_test_runner::get_instance().run_test("empty_function", empty_function);
                end = std::chrono::high_resolution_clock::now();
                basic_test_results.ran_empty++;
                basic_test_results.empty_duration += end - start;

                start = std::chrono::high_resolution_clock::now();
                basic_test_runner::get_instance().run_test("true_function", assert_true_function);
                end = std::chrono::high_resolution_clock::now();
                basic_test_results.ran_passed++;
                basic_test_results.passed_duration += end - start;

                start = std::chrono::high_resolution_clock::now();
                basic_test_runner::get_instance().run_test("false_function", assert_false_function);
                end = std::chrono::high_resolution_clock::now();
                basic_test_results.ran_failed++;
                basic_test_results.failed_duration += end - start;
            }

            __STF_SUITE_TO_VAR_NAME(empty_suite) empty_suite;
            
            std::stringstream ss;
            ss << "Basic Test Benchmark Results (" << n << " repetitions): \n"
                "\tEmpty test function: " << convert_duration_to_readable_string(basic_test_results.empty_duration) << " - " << std::to_string((long double)1000000000 / basic_test_results.empty_duration.count() * n) << " times / second\n"
                "\tPassed test function: " << convert_duration_to_readable_string(basic_test_results.passed_duration) << " - " << std::to_string((long double)1000000000 / basic_test_results.passed_duration.count() * n) << " times / second\n"
                "\tFailed test function: " << convert_duration_to_readable_string(basic_test_results.failed_duration) << " - " << std::to_string((long double)1000000000 / basic_test_results.failed_duration.count() * n) << " times / second\n";
            logger::fine(ss.str());
        }
    }
}
