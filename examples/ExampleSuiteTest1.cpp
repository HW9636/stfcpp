#ifdef STFCPP_BUILD_EXAMPLES
#include "stfcpp/stfcpp.h"
STF_TEST_SUITE(ExampleSuiteTest1)
{
public:
	void suite_test_1()
	{
		STF_BASIC_ASSERT_ONFAIL(true, false, []() {
			stfcpp::logger::normal("Subtest onfail function called!");
		});
	}
	STF_SUITE_TEST(suite_subtest_1, suite_test_1);

	STF_SUITE_TEST_LAMBDA(suite_subtest_2, [this]() {
		STF_BASIC_ASSERT(true, true);
		});
};
STF_REGISTER_SUITE(ExampleSuiteTest1);
#endif