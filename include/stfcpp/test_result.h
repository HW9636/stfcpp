#pragma once

#include <vector>
#include <utility>
#include <chrono>

#include "stf_log.h"

namespace stfcpp
{
	struct test_result
	{
		unsigned int passed;
		unsigned int failed;
		unsigned int total;
		std::chrono::nanoseconds duration;
	};

	inline std::string convert_duration_to_readable_string(const std::chrono::nanoseconds& duration)
	{
		long long nanoseconds = duration.count();
		std::stringstream ss;
		ss << std::to_string(nanoseconds) + "ns";

		if (nanoseconds > 1000000000ll)		ss << " (" << std::to_string((nanoseconds / 10000000) / 100.0f) << "s)";
		else if (nanoseconds > 1000000ll)	ss << " (" << std::to_string((nanoseconds / 10000) / 100.0f) << "ms)";
		else if (nanoseconds > 1000ll)		ss << " (" << std::to_string((nanoseconds / 10) / 100.0f) << "us)";
		return ss.str();
	}

    using suite_test_results = std::vector<std::pair<std::string, test_result>>;

	inline void print_test_details(const test_result& results)
	{
		logger::normal("Test results:");
		logger::fine("\tTests passed: " + std::to_string(results.passed));
		logger::error("\tTests failed: " + std::to_string(results.failed));
		logger::normal("\tTests total: " + std::to_string(results.total));
		logger::normal("\tTime taken: " + convert_duration_to_readable_string(results.duration));
	}

	inline void print_suite_test_details(const suite_test_results& results)
	{
		unsigned int total = static_cast<unsigned int>(results.size()), printed = 0;
		for (const auto& pair : results) {
			std::stringstream ss;
			ss << "Suite test results for '" << pair.first << "' (Suite test " << ++printed << "/" << total << ")";
			logger::normal(ss.str());
			logger::fine("\tTests passed: " + std::to_string(pair.second.passed));
			logger::error("\tTests failed: " + std::to_string(pair.second.failed));
			logger::normal("\tTests total: " + std::to_string(pair.second.total));
			logger::normal("\tTime taken: " + convert_duration_to_readable_string(pair.second.duration));
		}
	}
}
