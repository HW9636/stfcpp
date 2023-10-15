#ifdef STFCPP_BUILD_EXAMPLES
#include "stfcpp/stfcpp.h"

STF_BASIC_TEST(test1, []() {
	STF_BASIC_ASSERT(1, 1);
	});

STF_BASIC_TEST(test2, []() {
	STF_BASIC_ASSERT(1, 2, "Args do not match");
	});

STF_BASIC_TEST(test3, []() {
	throw std::runtime_error("Error test");
	});

int main(void)
{
	stfcpp::basic_test_runner::run_tests();
}
#endif