#include "unity.h" 
#include "../logger.h"
#include "unity_internals.h"
void setUp(void)
{
	/*set up stuff*/
}
void tearDown(void)
{
	/*tear down stuff*/
}
void test_same_string(void)
{
	TEST_ASSERT_EQUAL(0, string_compare("testFuction", "testFuction"));
	TEST_ASSERT_EQUAL(0, string_compare("TESTfunction", "TESTfunction"));
	TEST_ASSERT_EQUAL(0, string_compare("Equal", "EQuAl"));
	TEST_ASSERT_NOT_EQUAL(0, string_compare("NotEqual", "notequal2"));
	TEST_ASSERT_NOT_EQUAL(0, string_compare("NotE2ual", "notEqual"));
}
int main (void) 
{
UNITY_BEGIN();	
RUN_TEST(test_same_string);
return(0);
}
