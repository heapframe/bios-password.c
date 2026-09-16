#include "unity.h"
#include "hpmini.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void test_hpminiKeygen(void)
{
    static const struct {
        const char *serial;
        const char *expected;
    } cases[] = {
        { "CNU1234ABC", "e9l37fvcpe" },
        { "CNU1234567", "e9l37fvqgx" },
        { "CNU1234ABX", "e9l37fvcp4, e9l37fvcpr" },
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        char *result = hpminiKeygen(cases[i].serial);

        TEST_ASSERT_NOT_NULL(result);
        TEST_ASSERT_EQUAL_STRING(cases[i].expected, result);

        free(result);
    }
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_hpminiKeygen);
    return UNITY_END();
}