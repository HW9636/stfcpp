#pragma once


#include <string>
#include <sstream>

#include "stf_log.h"
#include "except.h"

namespace stfcpp
{

    template<typename T>
    inline std::string __stf__internal_basic_assert_msg(const std::string& file, const int& line, const std::string& message, const T& expected, const T& actual)
    {
        std::stringstream ss;
        ss << "Assertion failed at: " << file << ":" << line << " - " << message << " (Expected: " << expected << ", Actual: " << actual << ")";
        return ss.str();
    }

    template<typename T>
    inline std::string __stf_basic_assert_msg(const std::string& file, const int& line, const std::string& message, const T& expected, const T& actual);

    
    template<typename T>
    inline std::string __stf_basic_assert_msg(const std::string& file, const int& line, const std::string& message, const T& expected, const T& actual)
    {
        return __stf__internal_basic_assert_msg(file, line, message, expected, actual);
    }

    template<>
    inline std::string __stf_basic_assert_msg<bool>(const std::string& file, const int& line, const std::string& message, const bool& expected, const bool& actual)
    {
        return __stf__internal_basic_assert_msg(file, line, message, expected ? "true" : "false", actual ? "true" : "false");
    }


    using basic_assert_fail_func = void(*)();

	template<typename T>
	inline void __basic_assert(const T& expected, const T& actual, const char* file, const int& line, const std::string& message = "Expected and actual values are different")
	{
		if (expected == actual) return;
		throw assertion_failed_exception(__stf_basic_assert_msg(file, line, message, expected, actual));
	}

    template<typename T>
    inline void __basic_assert_onfail(const T& expected, const T& actual, const char* file, const int& line, const basic_assert_fail_func& failFunc = [](){ logger::normal("On failed function triggered. If you don't want an on fail function please use STF_BASIC_ASSERT instead."); })
    {
        if (expected == actual) return;
        failFunc();
        throw assertion_failed_exception(__stf_basic_assert_msg(file, line, "Expected and actual values are different", expected, actual));
    }

    inline void __assert_fail(const std::string& file, const int& line, const std::string& message = "Assertion failed.")
    {
        std::stringstream ss;
        ss << message << "\tAt: " << file << ":" << line;
        throw assertion_failed_exception(ss.str());
    }
}

// Takes expected, actual, and optional message
#define STF_BASIC_ASSERT(expected, actual, ...) ::stfcpp::__basic_assert((expected), (actual), __FILE__, __LINE__, ##__VA_ARGS__)

// Take expected, actual, and on fail code, of type stfcpp::basic_assert_fail_func
#define STF_BASIC_ASSERT_ONFAIL(expected, actual, ...) ::stfcpp::__basic_assert_onfail((expected), (actual), __FILE__, __LINE__, ##__VA_ARGS__)

#define STF_ASSERT_FAIL(...) ::stfcpp::__assert_fail(__FILE__, __LINE__, ##__VA_ARGS__)
