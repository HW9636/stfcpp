#pragma once

#include "test_result.h"
#include "stf_log.h"
#include "test_registry.h"
#include "except.h"

#include <functional>
#include <vector>
#include <utility>
#include <sstream>
#include <chrono>
#include <memory>

namespace stfcpp
{
	class suite_test_runner
	{
	private:
        suite_test_runner() {}
        
		unsigned int m_suite_tested;
		unsigned int m_suite_total;
		suite_test_results m_suite_results;

        void test_suite(std::string name, std::shared_ptr<test_suite> test_suite)
		{
			std::stringstream ss;
			ss << "Testing suite '" << name << "' (Suite " << ++m_suite_tested << "/" << m_suite_total << ")";
			logger::normal(ss.str());
			m_suite_results.push_back(std::make_pair(name, test_suite->run_tests()));
			
		}
	public:
        //const test_result& run_single_suite_test(const std::string& suite_name)
        
        const suite_test_results& run_suite_tests()
		{
			m_suite_tested = 0;
            m_suite_results.clear();
            m_suite_total = static_cast<unsigned int>(suite_test_registry::get_instance().m_registered_test_suites.size());
            m_suite_results.reserve(m_suite_total);

            for (const auto& test_entry : suite_test_registry::get_instance().m_registered_test_suites)
            {
                test_suite(test_entry.first, test_entry.second);
            }
			
			return m_suite_results;
		}
        
        static suite_test_runner& get_instance()
        {
            static suite_test_runner runner;
            return runner;
        }
	};

	class basic_test_runner
	{
	private:
		basic_test_runner() {}

		unsigned int m_test_passed;
		unsigned int m_test_failed;
		unsigned int m_test_total;

        void test(std::string name, std::function<void()> function)
		{
			std::stringstream ss;
			ss << "Testing test '" << name << "' (Test " << (m_test_passed + m_test_failed + 1) << "/" << m_test_total << ")";
			logger::normal(ss.str());
			try
			{
                function();
				logger::fine("\tTest passed!");
				m_test_passed++;
			}
			catch (const assertion_failed_exception& e)
			{
				std::stringstream error;
				error << "\tTest failed - " << e.what();
				logger::warn(error.str());
				m_test_failed++;
			}
			catch (const std::exception& e)
			{
				std::stringstream error;
				error << "\tTest crashed - " << e.what();
				logger::error(error.str());
				m_test_failed++;
			}
		}

	public:
        inline static basic_test_runner& get_instance()
        {
            static basic_test_runner runner;
            return runner;
        }

                                            
        inline test_result run_tests()
		{
			auto start = std::chrono::high_resolution_clock::now();
			m_test_total = static_cast<unsigned int>(basic_test_registry::get_instance().m_registered_tests.size());
			m_test_passed = 0;
			m_test_failed = 0;

            for (const auto& test_entry : basic_test_registry::get_instance().m_registered_tests)
            {
                test(test_entry.first, test_entry.second);
            }
    
			auto end = std::chrono::high_resolution_clock::now();
			return test_result{
				m_test_passed,
				m_test_failed,
				m_test_total,
				end - start
			};
		}
		
		inline void run_test(const std::string& test_name, std::function<void()> function) noexcept
		{
			test(test_name, function);
		}
	};
}

// Returns stfcpp::test_result, use stfcpp::print_test_details to print
#define STF_RUN_BASIC_TESTS ::stfcpp::basic_test_runner::get_instance().run_tests()

// Returns stfcpp::suite_test_results, use stfcpp:print_suite_test_details to print
#define STF_RUN_SUITE_TESTS ::stfcpp::suite_test_runner::get_instance().run_suite_tests()
