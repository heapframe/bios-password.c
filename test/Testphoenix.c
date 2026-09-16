#include "unity.h"
#include "phoenix.h"
#include <stdlib.h>

void setUp(void) {}
void tearDown(void) {}

void test_phoenixCalculateHash(void)
{
    PhoenixInfo defaultInfo = {};
    int result = calculateHash("abstoou", &defaultInfo);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(12345, result);

    PhoenixInfo HPCompaqInfo = {
        .salt = 17232
    };
    result = calculateHash("vnflm", &HPCompaqInfo);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(12345, result);

    PhoenixInfo FsiInfo = {
        .salt = 65,
        .dictionary = digitsOnly
    };
    result = calculateHash("411113", &FsiInfo);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(12345, result);

    PhoenixInfo FSIModelLInfo = {
        .shift = 1,
        .salt = 'L',
        .dictionary = digitsOnly
    };
    result = calculateHash("362153", &FSIModelLInfo);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(12345, result);

    PhoenixInfo FSIModelPInfo = {
        .shift = 1,
        .salt = 'P',
        .dictionary = digitsOnly
    };
    result = calculateHash("4465237", &FSIModelPInfo);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(12345, result);

    PhoenixInfo FSIModelSInfo = {
        .shift = 1,
        .salt = 'S',
        .dictionary = digitsOnly
    };
    result = calculateHash("71669", &FSIModelSInfo);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(12345, result);

    PhoenixInfo FSIModelXInfo = {
        .shift = 1,
        .salt = 'X',
        .dictionary = digitsOnly
    };
    result = calculateHash("739979", &FSIModelXInfo);
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_INT(12345, result);

    //free(result);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_phoenixCalculateHash);
    return UNITY_END();
}