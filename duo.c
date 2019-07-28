#include "defs.h"
#include <stdint.h>

static const uint16_t table[32][4];

uint16_t
crc16_by_duo(const uint8_t *ptr, size_t num, uint16_t crc)
{
    for (; num > 0; num --, ptr ++) {
        crc = table[0][(crc >> 14) & 0x03] ^ (crc << 2);
        crc = table[0][(crc >> 14) & 0x03] ^ (crc << 2);
        crc = table[0][(crc >> 14) & 0x03] ^ (crc << 2);
        crc = table[0][(crc >> 14) & 0x03] ^ (crc << 2);
        crc ^= *ptr;
    }

    return crc;
}

uint16_t
crc16_by1_duo(const uint8_t *ptr, size_t num, uint16_t crc)
{
    for (; num > 0; num --, ptr ++) {
        crc = table[3][(crc >> 14) & 0x03] ^
              table[2][(crc >> 12) & 0x03] ^
              table[1][(crc >> 10) & 0x03] ^
              table[0][(crc >>  8) & 0x03] ^
              (crc << 8) ^ *ptr;
    }

    return crc;
}

uint16_t
crc16_by2_duo(const uint8_t *ptr, size_t num, uint16_t crc)
{
    for (; num >= 2; num -= 2, ptr += 2) {
        crc = table[7][(crc >> 14) & 0x03] ^
              table[6][(crc >> 12) & 0x03] ^
              table[5][(crc >> 10) & 0x03] ^
              table[4][(crc >>  8) & 0x03] ^
              table[3][(crc >>  6) & 0x03] ^
              table[2][(crc >>  4) & 0x03] ^
              table[1][(crc >>  2) & 0x03] ^
              table[0][(crc >>  0) & 0x03] ^
              ((ptr[0] << 8) ^ ptr[1]);
    }

    for (; num > 0; num --, ptr ++) {
        crc = table[3][(crc >> 14) & 0x03] ^
              table[2][(crc >> 12) & 0x03] ^
              table[1][(crc >> 10) & 0x03] ^
              table[0][(crc >>  8) & 0x03] ^
              (crc << 8) ^ *ptr;
    }

    return crc;
}

uint16_t
crc16_by4_duo(const uint8_t *ptr, size_t num, uint16_t crc)
{
    for (; num >= 4; num -= 4, ptr += 4) {
        uint8_t a = ptr[0];
        uint8_t b = ptr[1];
        uint16_t cd = (ptr[2] << 8) | ptr[3]; /* load uint16_t as big-endian */

        crc = table[15][(crc >> 14) & 0x03] ^
              table[14][(crc >> 12) & 0x03] ^
              table[13][(crc >> 10) & 0x03] ^
              table[12][(crc >>  8) & 0x03] ^
              table[11][(crc >>  6) & 0x03] ^
              table[10][(crc >>  4) & 0x03] ^
              table[ 9][(crc >>  2) & 0x03] ^
              table[ 8][(crc >>  0) & 0x03] ^
              table[ 7][(a   >>  6) & 0x03] ^
              table[ 6][(a   >>  4) & 0x03] ^
              table[ 5][(a   >>  2) & 0x03] ^
              table[ 4][(a   >>  0) & 0x03] ^
              table[ 3][(b   >>  6) & 0x03] ^
              table[ 2][(b   >>  4) & 0x03] ^
              table[ 1][(b   >>  2) & 0x03] ^
              table[ 0][(b   >>  0) & 0x03] ^
              cd;
    }

    for (; num > 0; num --, ptr ++) {
        crc = table[3][(crc >> 14) & 0x03] ^
              table[2][(crc >> 12) & 0x03] ^
              table[1][(crc >> 10) & 0x03] ^
              table[0][(crc >>  8) & 0x03] ^
              ((crc << 8) | *ptr);
    }

    return crc;
}

uint16_t
crc16_by8_duo(const uint8_t *ptr, size_t num, uint16_t crc)
{
    for (; num >= 8; num -= 8, ptr += 8) {
        uint8_t a = ptr[0];
        uint8_t b = ptr[1];
        uint8_t c = ptr[2];
        uint8_t d = ptr[3];
        uint8_t e = ptr[4];
        uint8_t f = ptr[5];
        uint16_t gh = (ptr[6] << 8) | ptr[7]; /* load uint16_t as big-endian */

        crc = table[31][(crc >> 14) & 0x03] ^
              table[30][(crc >> 12) & 0x03] ^
              table[29][(crc >> 10) & 0x03] ^
              table[28][(crc >>  8) & 0x03] ^
              table[27][(crc >>  6) & 0x03] ^
              table[26][(crc >>  4) & 0x03] ^
              table[25][(crc >>  2) & 0x03] ^
              table[24][(crc >>  0) & 0x03] ^
              table[23][(a   >>  6) & 0x03] ^
              table[22][(a   >>  4) & 0x03] ^
              table[21][(a   >>  2) & 0x03] ^
              table[20][(a   >>  0) & 0x03] ^
              table[19][(b   >>  6) & 0x03] ^
              table[18][(b   >>  4) & 0x03] ^
              table[17][(b   >>  2) & 0x03] ^
              table[16][(b   >>  0) & 0x03] ^
              table[15][(c   >>  6) & 0x03] ^
              table[14][(c   >>  4) & 0x03] ^
              table[13][(c   >>  2) & 0x03] ^
              table[12][(c   >>  0) & 0x03] ^
              table[11][(d   >>  6) & 0x03] ^
              table[10][(d   >>  4) & 0x03] ^
              table[ 9][(d   >>  2) & 0x03] ^
              table[ 8][(d   >>  0) & 0x03] ^
              table[ 7][(e   >>  6) & 0x03] ^
              table[ 6][(e   >>  4) & 0x03] ^
              table[ 5][(e   >>  2) & 0x03] ^
              table[ 4][(e   >>  0) & 0x03] ^
              table[ 3][(f   >>  6) & 0x03] ^
              table[ 2][(f   >>  4) & 0x03] ^
              table[ 1][(f   >>  2) & 0x03] ^
              table[ 0][(f   >>  0) & 0x03] ^
              gh;
    }

    for (; num > 0; num --, ptr ++) {
        crc = table[3][(crc >> 14) & 0x03] ^
              table[2][(crc >> 12) & 0x03] ^
              table[1][(crc >> 10) & 0x03] ^
              table[0][(crc >>  8) & 0x03] ^
              ((crc << 8) | *ptr);
    }

    return crc;
}

static const uint16_t table[32][4] =
{
  { /* round 0 */
    0x0000U, 0x1021U, 0x2042U, 0x3063U,
  },
  { /* round 1 */
    0x0000U, 0x4084U, 0x8108U, 0xc18cU,
  },
  { /* round 2 */
    0x0000U, 0x1231U, 0x2462U, 0x3653U,
  },
  { /* round 3 */
    0x0000U, 0x48c4U, 0x9188U, 0xd94cU,
  },
  { /* round 4 */
    0x0000U, 0x3331U, 0x6662U, 0x5553U,
  },
  { /* round 5 */
    0x0000U, 0xccc4U, 0x89a9U, 0x456dU,
  },
  { /* round 6 */
    0x0000U, 0x0373U, 0x06e6U, 0x0595U,
  },
  { /* round 7 */
    0x0000U, 0x0dccU, 0x1b98U, 0x1654U,
  },
  { /* round 8 */
    0x0000U, 0x3730U, 0x6e60U, 0x5950U,
  },
  { /* round 9 */
    0x0000U, 0xdcc0U, 0xa9a1U, 0x7561U,
  },
  { /* round 10 */
    0x0000U, 0x4363U, 0x86c6U, 0xc5a5U,
  },
  { /* round 11 */
    0x0000U, 0x1dadU, 0x3b5aU, 0x26f7U,
  },
  { /* round 12 */
    0x0000U, 0x76b4U, 0xed68U, 0x9bdcU,
  },
  { /* round 13 */
    0x0000U, 0xcaf1U, 0x85c3U, 0x4f32U,
  },
  { /* round 14 */
    0x0000U, 0x1ba7U, 0x374eU, 0x2ce9U,
  },
  { /* round 15 */
    0x0000U, 0x6e9cU, 0xdd38U, 0xb3a4U,
  },
  { /* round 16 */
    0x0000U, 0xaa51U, 0x4483U, 0xeed2U,
  },
  { /* round 17 */
    0x0000U, 0x8906U, 0x022dU, 0x8b2bU,
  },
  { /* round 18 */
    0x0000U, 0x045aU, 0x08b4U, 0x0ceeU,
  },
  { /* round 19 */
    0x0000U, 0x1168U, 0x22d0U, 0x33b8U,
  },
  { /* round 20 */
    0x0000U, 0x45a0U, 0x8b40U, 0xcee0U,
  },
  { /* round 21 */
    0x0000U, 0x06a1U, 0x0d42U, 0x0be3U,
  },
  { /* round 22 */
    0x0000U, 0x1a84U, 0x3508U, 0x2f8cU,
  },
  { /* round 23 */
    0x0000U, 0x6a10U, 0xd420U, 0xbe30U,
  },
  { /* round 24 */
    0x0000U, 0xb861U, 0x60e3U, 0xd882U,
  },
  { /* round 25 */
    0x0000U, 0xc1c6U, 0x93adU, 0x526bU,
  },
  { /* round 26 */
    0x0000U, 0x377bU, 0x6ef6U, 0x598dU,
  },
  { /* round 27 */
    0x0000U, 0xddecU, 0xabf9U, 0x7615U,
  },
  { /* round 28 */
    0x0000U, 0x47d3U, 0x8fa6U, 0xc875U,
  },
  { /* round 29 */
    0x0000U, 0x0f6dU, 0x1edaU, 0x11b7U,
  },
  { /* round 30 */
    0x0000U, 0x3db4U, 0x7b68U, 0x46dcU,
  },
  { /* round 31 */
    0x0000U, 0xf6d0U, 0xfd81U, 0x0b51U,
  },
};
