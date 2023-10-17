#pragma once

#include <string>
#include <memory>

#include "test_result.h"
#include "test_suite.h"
#include "test_registry.h"

// Defines a test suite, but registration is done with STF_REGISTER_SUITE
#define STF_TEST_SUITE(test_suite_name) class __stf__test_suite_##test_suite_name : public ::stfcpp::test_suite

// Registers a suite, depends on class definition, call after class definition
#define STF_REGISTER_SUITE(test_suite_name) const static bool __stf__test_obj__##test_suite_name = ::stfcpp::suite_test_registry::get_instance().register_suite(#test_suite_name, std::make_shared<__stf__test_suite_##test_suite_name>())

// Defines and registers a suite inline, but the class code needs to go inside the macro __VA_ARGS__
#define STF_CREATE_AND_REGISTER_SUITE(test_suite_name, ...) STF_TEST_SUITE(test_suite_name) __VA_ARGS__; \
STF_REGISTER_SUITE(test_suite_name)

// Registers a basic test, can take in functions or lambdas that take no parameters and return nothing
#define STF_BASIC_TEST(test_name, test_func) const static bool __stf_basic_test_obj__##test_name = ::stfcpp::basic_test_registry::get_instance().register_test(#test_name, test_func)

// This macro only works with lambdas, to use member functions use STF_SUITE_TEST. Make sure to capture [this]
#define STF_SUITE_TEST_LAMBDA(test_name, test_lambda) const bool __stf_internal_obj__##test_name = register_suite_test(#test_name, test_lambda)

// If you want to use lambdas, use STF_SUITE_TEST_LAMBDA
#define STF_SUITE_TEST(test_name, test_func) const bool __stf_internal_obj__##test_name = register_suite_test(#test_name, [this](){ this->test_func(); })
