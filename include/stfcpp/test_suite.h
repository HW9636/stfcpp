#pragma once

#include "test_result.h"

#include <functional>
#include <vector>
#include <utility>
#include <string>
#include <chrono>
#include <algorithm>

namespace stfcpp
{
	class test_suite
	{
	public:
		test_suite() {}

		test_result run_tests()
		{
			m_test_total = static_cast<unsigned int>(m_registered_tests.size());
			auto start = std::chrono::high_resolution_clock::now();
			for (const auto& pair : m_registered_tests)
			{
				test(pair.first, pair.second);
			}
			auto end = std::chrono::high_resolution_clock::now();
			return test_result{
				m_test_passed,
				m_test_failed,
				m_test_total,
				end - start
			};
		}

		bool register_suite_test(const std::string& test_name, std::function<void()> test_func)
		{
			m_registered_tests.push_back(std::make_pair(test_name, test_func));
			return true;
		}

		// Called before every test
		virtual void setup() {}

		// Called after every test
		virtual void finish() {}

	private:
		void test(std::string test_name, std::function<void()> test_function)
		{
			std::stringstream ss;
			ss << "\tTesting suite test '" << test_name << "' (Test " << (m_test_passed + m_test_failed + 1) << "/" << m_test_total << ")";
			logger::normal(ss.str());
			try
			{
				setup();
				test_function();
				finish();
				logger::fine("\t\tTest passed!");
				m_test_passed++;
			}
			catch (const assertion_failed_exception& e)
			{
				std::stringstream error;
				error << "\t\tTest failed - " << e.what();
				logger::warn(error.str());
				m_test_failed++;
			}
			catch (const std::exception& e)
			{
				std::stringstream error;
				error << "\t\tTest crashed - " << e.what();
				logger::error(error.str());
				m_test_failed++;
			}
		}

		std::vector<std::pair<std::string, std::function<void()>>> m_registered_tests;
		unsigned int m_test_passed;
		unsigned int m_test_failed;
		unsigned int m_test_total;

	};
}