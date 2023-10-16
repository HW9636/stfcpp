#pragma once

#include "test_suite.h"

#include <string>
#include <vector>
#include <utility>
#include <memory>

namespace stfcpp
{
	class suite_test_registry
	{
	public:
		inline static bool register_suite(const std::string& suite_name, std::shared_ptr<test_suite> test_suite)
		{
			s_registered_test_suites.push_back(std::make_pair(suite_name, test_suite));
			return true;
		}

		inline static std::vector<std::pair<std::string, std::shared_ptr<test_suite>>> s_registered_test_suites;
	};

	class basic_test_registry
	{
	public:
		inline static bool register_test(const std::string& test_name, void(*function)()) 
		{ 
			s_registered_tests.push_back(std::make_pair(test_name, function));
			return true;
		}

		inline static std::vector<std::pair<std::string, void (*)()>> s_registered_tests;
	};
}