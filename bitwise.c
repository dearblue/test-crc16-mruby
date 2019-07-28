#include "defs.h"

uint16_t
crc16_bitwise_condxor(const uint8_t *ptr, size_t num, uint16_t crc)
{
    for (; num > 0; num --, ptr ++) {
        for (int i = 0; i < 8; i ++) {
            char carry = crc >> 15;
            crc <<= 1;
            if (carry) { crc ^= CRC16_POLYNOMIAL; }
        }

        crc ^= *ptr;
    }

    return crc;
}

uint16_t
crc16_bitwise_branchassign(const uint8_t *ptr, size_t num, uint16_t crc)
{
    for (; num > 0; num --, ptr ++) {
        for (int i = 0; i < 8; i ++) {
            if ((crc >> 15) == 0) {
                crc <<= 1;
            } else {
                crc = (crc << 1) ^ CRC16_POLYNOMIAL;
            }
        }

        crc ^= *ptr;
    }

    return crc;
}

uint16_t
crc16_bitwise_branchmix(const uint8_t *ptr, size_t num, uint16_t crc)
{
    for (; num > 0; num --, ptr ++) {
        for (int i = 0; i < 8; i ++) {
            crc = (crc << 1) ^ ((crc >> 15) == 0 ? 0 : CRC16_POLYNOMIAL);
        }

        crc ^= *ptr;
    }

    return crc;
}

uint16_t
crc16_bitwise_branchless(const uint8_t *ptr, size_t num, uint16_t crc)
{
    for (; num > 0; num --, ptr ++) {
        for (int i = 0; i < 8; i ++) {
            crc = (crc << 1) ^ (-(crc >> 15) & CRC16_POLYNOMIAL);
        }

        crc ^= *ptr;
    }

    return crc;
}
