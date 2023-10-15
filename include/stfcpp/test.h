#pragma once

#include <string>

#include "test_registry.h"

namespace stfcpp
{
	
}

#define STF_BASIC_TEST(test_name, test_func) const static bool __stf_test_obj__##test_name = ::stfcpp::basic_test_registry::register_test(#test_name, test_func)