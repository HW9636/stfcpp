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
        suite_test_runner() : s_suite_passed(0), s_suite_failed(0), s_suite_total(0)
        {
            
        }
        
        unsigned int s_suite_passed;
        unsigned int s_suite_failed;
		unsigned int s_suite_total;
		suite_test_results s_suite_results;

        void test_suite(std::string name, std::shared_ptr<test_suite> test_suite)
		{
			std::stringstream ss;
			ss << "Testing suite '" << name << "' (Suite " << (s_suite_passed + s_suite_failed + 1) << "/" << s_suite_total << ")";
			logger::normal(ss.str());
			test_result results = test_suite->run_tests();
			s_suite_results.push_back(std::make_pair(name, results));
			
		}
	public:
        //const test_result& run_single_suite_test(const std::string& suite_name)
        
        const std::vector<std::pair<std::string, test_result>>& run_suite_tests()
		{
            s_suite_results.clear();
            s_suite_total = static_cast<unsigned int>(suite_test_registry::get_instance().m_registered_test_suites.size());
            s_suite_results.reserve(s_suite_total);
			

            for (const auto& test_entry : suite_test_registry::get_instance().m_registered_test_suites)
            {
                test_suite(test_entry.first, test_entry.second);
            }
			

			return s_suite_results;
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
		unsigned int s_test_passed;
		unsigned int s_test_failed;
		unsigned int s_test_total;

        void test(std::string name, std::function<void()> function)
		{
			std::stringstream ss;
			ss << "Testing test '" << name << "' (Test " << (s_test_passed + s_test_failed + 1) << "/" << s_test_total << ")";
			logger::normal(ss.str());
			try
			{
                function();
				logger::fine("\tTest passed!");
				s_test_passed++;
			}
			catch (const assertion_failed_exception& e)
			{
				std::stringstream error;
				error << "\tTest failed - " << e.what();
				logger::warn(error.str());
				s_test_failed++;
			}
			catch (const std::exception& e)
			{
				std::stringstream error;
				error << "\tTest crashed - " << e.what();
				logger::error(error.str());
				s_test_failed++;
			}
		}

	public:
        static basic_test_runner& get_instance()
        {
            static basic_test_runner runner;
            return runner;
        }

                                            
        test_result run_tests()
		{
			auto start = std::chrono::high_resolution_clock::now();
			s_test_total = static_cast<unsigned int>(basic_test_registry::get_instance().m_registered_tests.size());
			s_test_passed = 0;
			s_test_failed = 0;

            for (const auto& test_entry : basic_test_registry::get_instance().m_registered_tests)
            {
                test(test_entry.first, test_entry.second);
            }
    
			auto end = std::chrono::high_resolution_clock::now();
			return test_result{
				s_test_passed,
				s_test_failed,
				s_test_total,
				static_cast<unsigned long long>(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count())
			};
		}
		
	};
}

// Returns stfcpp::test_result, use stfcpp::print_test_details to print
#define STF_RUN_BASIC_TESTS ::stfcpp::basic_test_runner::get_instance().run_tests()

// Returns stfcpp::suite_test_results, use stfcpp:print_suite_test_details to print
#define STF_RUN_SUITE_TESTS ::stfcpp::suite_test_runner::get_instance().run_suite_tests()
