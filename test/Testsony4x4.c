#include "unity.h"
#include "sony4x4.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void test_sony4x4Keygen(void)
{
    static const struct {
        const char *serial;
        const char *expected;
    } cases[] = {
        { "73KR3FP9PVKHK29R", "32799624" },
        { "73KR3FP9PVKHK299", "69423778" },
        { "9DPK73KR8JHXF3RT", "54746568" },
        { "3RT68JV26HX8K7FX", "32969527" },
        { "K29RPVKH3FP973KR", "65395983" },
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        char *result = sony4x4Keygen(cases[i].serial);

        TEST_ASSERT_NOT_NULL(result);
        TEST_ASSERT_EQUAL_STRING(cases[i].expected, result);

        free(result);
    }
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_sony4x4Keygen);
    return UNITY_END();
}