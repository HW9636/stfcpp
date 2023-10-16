#pragma once

#include "test_result.h"
#include "stf_log.h"
#include "test_registry.h"
#include "except.h"

#include <algorithm>
#include <execution>
#include <vector>
#include <utility>
#include <sstream>
#include <atomic>
#include <chrono>
#include <memory>

namespace stfcpp
{
	enum class RunMode
	{
		SEQUENCE,
		PARALLEL
	};

	class suite_test_runner
	{
	private:
		static inline unsigned int s_suite_passed;
		static inline unsigned int s_suite_failed;
		static inline unsigned int s_suite_total;
		static inline std::vector<std::pair<std::string, test_result>> s_suite_results;

		static void test_suite(std::pair<std::string, std::shared_ptr<test_suite>> pair)
		{
			std::stringstream ss;
			ss << "Testing suite '" << pair.first << "' (Suite " << (s_suite_passed + s_suite_failed + 1) << "/" << s_suite_total << ")";
			logger::normal(ss.str());
			test_result results = pair.second->run_tests();
			s_suite_results.push_back(std::make_pair(pair.first, results));
			
		}
	public:
		static const std::vector<std::pair<std::string, test_result>>& run_suite_tests(RunMode mode = RunMode::SEQUENCE)
		{
			auto& suites = suite_test_registry::s_registered_test_suites;
			s_suite_total = suites.size();
			if (mode == RunMode::SEQUENCE)
			{
				std::for_each(suites.begin(), suites.end(), test_suite);
			}
			else if (mode == RunMode::PARALLEL)
			{
				logger::error("Parallel not implemented yet, defaulting to sequence.");
				std::for_each(suites.begin(), suites.end(), test_suite);
			}

			return s_suite_results;
		}
	};

	class basic_test_runner
	{
	private:
		inline static std::atomic<unsigned int> s_test_passed;
		inline static std::atomic<unsigned int> s_test_failed;
		inline static std::atomic<unsigned int> s_test_total;

		static void test(std::pair<std::string, void(*)()> pair)
		{
			std::stringstream ss;
			ss << "Testing test '" << pair.first << "' (Test " << (s_test_passed + s_test_failed + 1) << "/" << s_test_total << ")";
			logger::normal(ss.str());
			try
			{
				pair.second();
				logger::fine("\tTest passed!");
				s_test_passed++;
			}
			catch (const assertion_failed_exception& e)
			{
				std::stringstream error;
				error << "\tTest failed - " << e.what();
				logger::warn(error.str());
				s_test_failed++;
			}
			catch (const std::exception& e)
			{
				std::stringstream error;
				error << "\tTest crashed - " << e.what();
				logger::error(error.str());
				s_test_failed++;
			}
		}

	public:
		static test_result run_tests(RunMode mode = RunMode::SEQUENCE)
		{
			auto start = std::chrono::high_resolution_clock::now();
			auto& basic_tests = basic_test_registry::s_registered_tests;
			s_test_total = (unsigned int)basic_tests.size();
			s_test_passed = 0;
			s_test_failed = 0;

			if (mode == RunMode::SEQUENCE)
			{
				std::for_each(basic_tests.begin(), basic_tests.end(), test);
			}
			else if (mode == RunMode::PARALLEL)
			{
#ifdef __APPLE__
				logger::warn("Parallel test execution is not supported on macOS..");
                std::for_each(basic_tests.begin(), basic_tests.end(), test);
#else
				std::for_each(std::execution::par, basic_tests.begin(), basic_tests.end(), test);
#endif
			}

			auto end = std::chrono::high_resolution_clock::now();
			return test_result{
				s_test_passed,
				s_test_failed,
				s_test_total,
				static_cast<unsigned long long>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count())
			};
		}
		
	};
}
