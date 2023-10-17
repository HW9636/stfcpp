#pragma once

#include <vector>
#include <utility>
#include "stf_log.h"

namespace stfcpp
{
	struct test_result
	{
		unsigned int passed;
		unsigned int failed;
		unsigned int total;
		unsigned long long microseconds_taken;
	};

    using suite_test_results = std::vector<std::pair<std::string, test_result>>;

	inline void print_test_details(const test_result& results)
	{
		logger::normal("Test results:");
		logger::fine("\tTests passed: " + std::to_string(results.passed));
		logger::error("\tTests failed: " + std::to_string(results.failed));
		logger::normal("\tTests total: " + std::to_string(results.total));
		logger::normal("\tTime taken: " + std::to_string(results.microseconds_taken) + " microseconds");
	}

	inline void print_suite_test_details(const suite_test_results& results)
	{
		unsigned int total = (unsigned int)results.size(), printed = 0;
		for (auto it = results.begin(); it != results.end(); ++it) {
			std::stringstream ss;
			ss << "Suite test results for '" << it->first << "' (Suite test " << ++printed << "/" << total << ")";
			logger::normal(ss.str());
			logger::fine("\tTests passed: " + std::to_string(it->second.passed));
			logger::error("\tTests failed: " + std::to_string(it->second.failed));
			logger::normal("\tTests total: " + std::to_string(it->second.total));
			logger::normal("\tTime taken: " + std::to_string(it->second.microseconds_taken) + " microseconds");
		}
	}
}
