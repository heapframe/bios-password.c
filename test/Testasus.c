#include "unity.h"
#include "asus.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void test_asusKeygen(void)
{
    static const struct {
        const char *serial;
        const char *expected;
    } cases[] = {
        { "2007-02-01", "AA19BALA" },
        { "2017-10-12", "AABABLAL" },
        { "2020-09-15", "LBD9DBA1" },
        { "2012-03-29", "AOBOBL2B" },
        { "2002-01-02", "ALAA4ABA" },
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        char *result = asusKeygen(cases[i].serial);

        TEST_ASSERT_NOT_NULL(result);
        TEST_ASSERT_EQUAL_STRING(cases[i].expected, result);

        free(result);
    }
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_asusKeygen);
    return UNITY_END();
}