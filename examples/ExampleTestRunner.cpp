#ifdef STFCPP_BUILD_EXAMPLES
#include "stfcpp/stfcpp.h"

STF_BASIC_TEST(test_basic_assert_1, []() {
	STF_BASIC_ASSERT(true, true);
	});

STF_BASIC_TEST(test_basic_assert_2, []() {
	STF_BASIC_ASSERT(true, false, "Args do not match");
	});

STF_BASIC_TEST(test_basic_assert_3, []() {
	throw std::runtime_error("Error test");
	});

STF_BASIC_TEST(test_basic_assert_onfail_1, []() {
    STF_BASIC_ASSERT_ONFAIL(1, 1, []() {
        stfcpp::logger::normal("This code should never be ran.");
    });
});

STF_BASIC_TEST(test_basic_assert_onfail_2, []() {
    STF_BASIC_ASSERT_ONFAIL(1, 2, []() {
        
    });
});

int main(int argc, char** argv)
{
    stfcpp::test_result results = STF_RUN_BASIC_TESTS();
    stfcpp::print_test_details(results);

    const auto& suite_results = STF_RUN_SUITE_TESTS();
    stfcpp::print_suite_test_details(suite_results);
}
#endif
