#include "unity.h"
#include "insyde.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void test_acerInsydeKeygen(void)
{
    static const struct {
        const char *serial;
        const char *expected;
    } cases[] = {
        { "0173549286", "e0eac38fdfcfd74a" },
        { "1014206418", "3c0a50907bc2c604" },
        { "1765418418", "5f54e355b83e969c" },
        { "1858408509", "c4791532114cfbab" },
        { "1925715998", "f21cce78c0987233" },
        { "2051611322", "1c648cb56e8a64bb" },
        { "2036529205", "f2e874332b6f50b1" },
        { "1768688657", "80774329818c3312" },
        { "1746144265", "c3d46da5f6f3c75b" },
        { "1611926546", "f61c86479a8a6b20" },
        { "1355047683", "7fe913d78ffc5ed1" },
        { "1373072054", "aebeae5c425684cd" },
        { "1373899792", "a26970a4ffb62d49" },
        { "1395185025", "a763280d9f7396ec" },
        { "1205532638", "0f29abe2243b5a5e" },
        { "1378359327", "0cb381199969833e" },
        { "1880388286", "021df1cd9695387d" },
        { "2025088185", "018261c3cbe60945" },
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        char *result = acerInsydeKeygen(cases[i].serial);

        TEST_ASSERT_NOT_NULL(result);
        TEST_ASSERT_EQUAL_STRING(cases[i].expected, result);

        free(result);
    }
}

void test_insydeKeygen(void)
{
    static const struct {
        const char *serial;
        const char *expected;
    } cases[] = {
        { "03133610", "12891236, 24094120, 99534862" },
        { "87654321", "38732907, 23812041" },
        { "12345678", "03023278, 16503512" },
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        char *result = insydeKeygen(cases[i].serial);

        TEST_ASSERT_NOT_NULL(result);
        TEST_ASSERT_EQUAL_STRING(cases[i].expected, result);

        free(result);
    }
}

void test_hpInsydeKeygen(void)
{
    static const struct {
        const char *serial;
        const char *expected;
    } cases[] = {
        { "i 70412809", "47283646, 65570229" },
        { "i 76205377", "41898738, 69163979" },
        { "i 52669168", "65436527, 43741168" },
        { "i 58828448", "65477807, 47780488" },
        // user can type more spaces or use wrong case for `I`
        { "I 62996480", "55507825, 73694406" },
        { "i  51120876", "66775639, 44888278" },
        { "I  69779941", "54526704, 76651387" },
        { "i   75582785", "42313120, 60480301" },
        { "I   52214872", "65889633, 43172274" },
        { "i	77319488", "40986827, 68071408" },
        { "i 68852353", "55443712, 77730995" },
        { "i 59170869", "64725626, 46858269" },
        { "i 63121056", "54774419, 72889098" },
        { "i 68105474", "55798831, 77863470" },
        { "i 87267970", "10836735, 38145376" },
        { "i 93641394", "04454731, 22729910" }, //had to stray from the orig source here,
        // uppercase I codes                   stripped the space as it wouldnt pass the regex anyways so it would've been impossible
        { "i 51974384", "66529721, 44652900" },
        { "I 51085312", "66618753, 44983934" },
        { "I 86013615", "11682050, 39971231" },
        { "I 59170869", "64725626, 46858269" },
    };

    for (size_t i = 0; i < sizeof(cases) / sizeof(cases[0]); i++) {
        char *result = hpInsydeKeygen(cases[i].serial);
        /*
        if (result == NULL) {
            printf("%s\n", cases[i].serial);
            printf("%s\n", cases[i].expected);
        }
        */

        TEST_ASSERT_NOT_NULL(result);
        TEST_ASSERT_EQUAL_STRING(cases[i].expected, result);

        free(result);
    }
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_acerInsydeKeygen);
    RUN_TEST(test_insydeKeygen);
    RUN_TEST(test_hpInsydeKeygen);
    return UNITY_END();
}