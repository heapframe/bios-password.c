#include "unity.h"
#include "hpami.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void test_hpAmiKeygen(void)
{
    static const struct {
        const char *serial;
        const char *expected;
    } cases[] = {
        { "A7AF422F", "49163252" },
        { "12345678", "2ae211b4" },
        { "48A02676", "27545092" },
        { "B60BD282", "489b5bf9" },
        { "757EDC82", "edfe2edd" },
        { "7d94422f", "e4eea2c4" },
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        char *result = hpAmiKeygen(cases[i].serial);

        TEST_ASSERT_NOT_NULL(result);
        TEST_ASSERT_EQUAL_STRING(cases[i].expected, result);

        free(result);
    }
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_hpAmiKeygen);
    return UNITY_END();
}