#ifdef STFCPP_BUILD_TESTS
#include "stfcpp/stfcpp.h"

STF_CREATE_AND_REGISTER_SUITE(AssertionTest, {
    void BasicAssertTest()
    {
        STF_BASIC_ASSERT(true, true);
        STF_BASIC_ASSERT(false, false);
        for (int i = 0 ;i < 100; i++) STF_BASIC_ASSERT(i, i);
    }
    
    
    void BasicAssertOnFailTest()
    {
        STF_BASIC_ASSERT_ONFAIL(true, true, [](){ STF_ASSERT_FAIL("Assert Onfail called, so test failed."); });
        STF_BASIC_ASSERT_ONFAIL(false, false, [](){ STF_ASSERT_FAIL("Assert Onfail called, so test failed."); });
        for (int i = 0 ;i < 100; i++) STF_BASIC_ASSERT_ONFAIL(i, i, [](){ STF_ASSERT_FAIL("Assert Onfail called, so test failed."); });
    }
    
    STF_SUITE_TEST(BasicAssertTest, BasicAssertTest);
    STF_SUITE_TEST(BasicAssertOnFailTest, BasicAssertOnFailTest);
    
});
#endif
