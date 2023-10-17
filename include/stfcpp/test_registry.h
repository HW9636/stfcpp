#pragma once

#include "test_suite.h"

#include <string>
#include <vector>
#include <utility>
#include <functional>
#include <memory>

namespace stfcpp
{
	using basic_test_entry = std::pair<std::string, std::function<void()>>;
	using suite_test_entry = std::pair<std::string, std::shared_ptr<test_suite>>;

	class suite_test_registry
	{
	public:
        static suite_test_registry& get_instance()
        {
            static suite_test_registry registry;
            return registry;
        }
        
		bool register_suite(const std::string& suite_name, std::shared_ptr<test_suite> test_suite)
		{
			m_registered_test_suites.push_back(std::make_pair(suite_name, test_suite));
			return true;
		}

		std::vector<suite_test_entry> m_registered_test_suites;
	};

	class basic_test_registry
	{
	public:
        static basic_test_registry& get_instance()
        {
            static basic_test_registry registry;
            return registry;
        }
        
        bool register_test(const std::string& test_name, std::function<void()> function)
		{
			m_registered_tests.push_back(std::make_pair(test_name, function));
			return true;
		}

		std::vector<basic_test_entry> m_registered_tests;
	};
}
