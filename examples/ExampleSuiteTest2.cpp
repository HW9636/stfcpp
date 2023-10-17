#ifdef STFCPP_BUILD_EXAMPLES
#include "stfcpp/stfcpp.h"

// Inline definition and register
STF_CREATE_AND_REGISTER_SUITE(ExampleSuiteTest2, {
	void example_suite_test_1()
	{
		STF_BASIC_ASSERT(true, true);
	}
	STF_SUITE_TEST(example_suite_subtest_1, example_suite_test_1);

	STF_SUITE_TEST_LAMBDA(suite_subtest_2, [this]() {
		STF_BASIC_ASSERT(true, true);
		});
	});
#endif
