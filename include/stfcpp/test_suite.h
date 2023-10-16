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
		test_suite() : m_test_passed(0), m_test_failed(0), m_test_total(0)
		{

		}

		test_result run_tests()
		{
			auto start = std::chrono::high_resolution_clock::now();
			std::for_each(m_registered_tests.begin(), m_registered_tests.end(), [this](const auto& pair) { test(pair); });
			auto end = std::chrono::high_resolution_clock::now();
			return test_result{
				m_test_passed,
				m_test_failed,
				m_test_total,
				static_cast<unsigned long long>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count())
			};
		}

		bool register_suite_test(const std::string& test_name, std::function<void()> test_func)
		{
			m_registered_tests.push_back(std::make_pair(test_name, test_func));
			return true;
		}
	

		// Called before every test
		virtual void setup()
		{

		}

		// Called after every test
		virtual void finish()
		{

		}

	private:
		void test(std::pair<std::string, std::function<void()>> pair)
		{
			std::stringstream ss;
			ss << "\tTesting suite test '" << pair.first << "' (Test " << (m_test_passed + m_test_failed + 1) << "/" << m_test_total << ")";
			logger::normal(ss.str());
			try
			{
				setup();
				pair.second();
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