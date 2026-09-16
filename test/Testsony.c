#include "unity.h"
#include "sony.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void test_sonyKeygen(void)
{
    char *result = sonyKeygen("1234567");
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING("9648669", result);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_sonyKeygen);
    return UNITY_END();
}