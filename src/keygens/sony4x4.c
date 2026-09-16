#include <stdint.h>
#include <stdio.h>
#include <string.h>

static const char otpChars[] = "9DPK7V2F3RT6HX8J";
static const char pwdChars[] = "47592836";

void decodeHash(const char *hash, uint8_t out[8])
{
    for (int i = 0; i < 16; i += 2) {
        const char *a = strchr(otpChars, hash[i]);
        const char *b = strchr(otpChars, hash[i + 1]);

        out[7 - i / 2] = (a - otpChars) * 16 + (b - otpChars);
    }
}

static uint64_t arrayToNumber(const uint8_t bytes[8])
{
    uint64_t n = 0;

    for (int i = 0; i < 8; i++)
        n |= (uint64_t)bytes[i] << (i * 8);

    return n;
}

static uint64_t modpow(uint64_t base, uint64_t exponent, uint64_t modulus)
{
    uint64_t result = 1;

    while (exponent) {
        if (exponent & 1)
            result = (__uint128_t)result * base % modulus;

        exponent >>= 1;
        base = (__uint128_t)base * base % modulus;
    }

    return result;
}

uint64_t rsaDecrypt(uint64_t code) {
    static const uint64_t N = 9909111257037312469ULL;
    static const uint64_t D = 2900227683130855721ULL;
    return modpow(code, D, N);
}

void encodePassword(uint32_t pwd, char out[9])
{
    for (int i = 0; i < 8; i++)
        out[i] = pwdChars[(pwd >> (21 - i * 3)) & 7];

    out[8] = '\0';
}

void _keygen(const char *hash, char out[9])
{
    uint8_t numHash[8];

    decodeHash(hash, numHash);

    uint64_t code = arrayToNumber(numHash);
    uint64_t decrypted = rsaDecrypt(code);

    encodePassword((uint32_t)decrypted, out);
}

char *sony4x4Keygen(const char *hash)
{
    char out[9];

    _keygen(hash, out);

    return strdup(out);
}