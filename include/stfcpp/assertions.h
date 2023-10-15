#pragma once


#include <string>
#include <sstream>

#include "except.h"

namespace stfcpp
{
	template<typename T>
	void basic_assert(const T& expected, const T& actual, const char* file, const int& line, const std::string& message = "Expcted and actual values are different")
	{
		if (expected == actual) return;
		std::stringstream ss;
		ss << "Assertion failed in " << file << " at line " << line << ": " << message << " (Expected: " << expected << ", Actual: " << actual << ")";
		throw assertion_failed_exception(ss.str());
	}
}

// Takes expected, actual, and optional message
#define STF_BASIC_ASSERT(expected, actual, ...) ::stfcpp::basic_assert((expected), (actual), __FILE__, __LINE__, ##__VA_ARGS__)