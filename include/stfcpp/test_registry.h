#pragma once

#include <string>
#include <vector>
#include <utility>

namespace stfcpp
{
	class suite_test_registry
	{
	public:

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