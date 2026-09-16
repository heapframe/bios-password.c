// cryptoUtils.h
#ifndef CRC64_H
#define CRC64_H

#include <stdint.h>
#include <stddef.h>

#define POLY 0xC96C5795D7870F42ULL
#define CRC64_TABLE_SIZE 256

typedef struct {
    uint64_t poly;
    uint64_t table[CRC64_TABLE_SIZE];
    uint64_t crc;
} Crc64;

void crc64_init(Crc64 *ctx);
void crc64_reset(Crc64 *ctx);
void crc64_update(Crc64 *ctx, const uint8_t *data, size_t len);
uint64_t crc64_digest(Crc64 *ctx);
void crc64_hexdigest(Crc64 *ctx, char out[17]) ;

#endif
