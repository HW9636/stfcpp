#pragma once

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

	void print_test_details(const test_result& results)
	{
		logger::normal("Test results:");
		logger::fine("\tTests passed: " + std::to_string(results.passed));
		logger::error("\tTests failed: " + std::to_string(results.failed));
		logger::normal("\tTests total: " + std::to_string(results.total));
		logger::normal("\tTime taken: " + std::to_string(results.microseconds_taken) + " microseconds");
	}
}