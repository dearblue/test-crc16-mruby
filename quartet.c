#include "defs.h"
#include <stdint.h>

static const uint16_t table[16][16];

uint16_t
crc16_by_quartet(const uint8_t *ptr, size_t num, uint16_t crc)
{
    for (; num > 0; num --, ptr ++) {
        crc = table[0][(crc >> 12) & 0x0f] ^ (crc << 4);
        crc = table[0][(crc >> 12) & 0x0f] ^ (crc << 4);
        crc ^= *ptr;
    }

    return crc;
}

uint16_t
crc16_by1_quartet(const uint8_t *ptr, size_t num, uint16_t crc)
{
    for (; num > 0; num --, ptr ++) {
        crc = table[1][(crc >> 12) & 0x0f] ^
              table[0][(crc >>  8) & 0x0f] ^
              (crc << 8) ^ *ptr;
    }

    return crc;
}

uint16_t
crc16_by2_quartet(const uint8_t *ptr, size_t num, uint16_t crc)
{
    for (; num >= 2; num -= 2, ptr += 2) {
        crc = table[3][(crc >> 12) & 0x0f] ^
              table[2][(crc >>  8) & 0x0f] ^
              table[1][(crc >>  4) & 0x0f] ^
              table[0][(crc >>  0) & 0x0f] ^
              ((ptr[0] << 8) | ptr[1]);
    }

    for (; num > 0; num --, ptr ++) {
        crc = table[1][(crc >> 12) & 0x0f] ^
              table[0][(crc >>  8) & 0x0f] ^
              (crc << 8) ^ *ptr;
    }

    return crc;
}

uint16_t
crc16_by4_quartet(const uint8_t *ptr, size_t num, uint16_t crc)
{
    for (; num >= 4; num -= 4, ptr += 4) {
        uint8_t a = ptr[0];
        uint8_t b = ptr[1];
        uint16_t cd = (ptr[2] << 8) | ptr[3]; /* load uint16_t as big-endian */

        crc = table[ 7][(crc >> 12) & 0x0f] ^
              table[ 6][(crc >>  8) & 0x0f] ^
              table[ 5][(crc >>  4) & 0x0f] ^
              table[ 4][(crc >>  0) & 0x0f] ^
              table[ 3][(a   >>  4) & 0x0f] ^
              table[ 2][(a   >>  0) & 0x0f] ^
              table[ 1][(b   >>  4) & 0x0f] ^
              table[ 0][(b   >>  0) & 0x0f] ^
              cd;
    }

    for (; num > 0; num --, ptr ++) {
        crc = table[1][(crc >> 12) & 0x0f] ^
              table[0][(crc >>  8) & 0x0f] ^
              (crc << 8) ^ *ptr;
    }

    return crc;
}

uint16_t
crc16_by8_quartet(const uint8_t *ptr, size_t num, uint16_t crc)
{
    for (; num >= 8; num -= 8, ptr += 8) {
        uint8_t a = ptr[0];
        uint8_t b = ptr[1];
        uint8_t c = ptr[2];
        uint8_t d = ptr[3];
        uint8_t e = ptr[4];
        uint8_t f = ptr[5];
        uint16_t gh = (ptr[6] << 8) | ptr[7]; /* load uint16_t as big-endian */

        crc = table[15][(crc >> 12) & 0x0f] ^
              table[14][(crc >>  8) & 0x0f] ^
              table[13][(crc >>  4) & 0x0f] ^
              table[12][(crc >>  0) & 0x0f] ^
              table[11][(a   >>  4) & 0x0f] ^
              table[10][(a   >>  0) & 0x0f] ^
              table[ 9][(b   >>  4) & 0x0f] ^
              table[ 8][(b   >>  0) & 0x0f] ^
              table[ 7][(c   >>  4) & 0x0f] ^
              table[ 6][(c   >>  0) & 0x0f] ^
              table[ 5][(d   >>  4) & 0x0f] ^
              table[ 4][(d   >>  0) & 0x0f] ^
              table[ 3][(e   >>  4) & 0x0f] ^
              table[ 2][(e   >>  0) & 0x0f] ^
              table[ 1][(f   >>  4) & 0x0f] ^
              table[ 0][(f   >>  0) & 0x0f] ^
              gh;
    }

    for (; num > 0; num --, ptr ++) {
        crc = table[1][(crc >> 12) & 0x0f] ^
              table[0][(crc >>  8) & 0x0f] ^
              (crc << 8) ^ *ptr;
    }

    return crc;
}

static const uint16_t table[16][16] =
{
  { /* round 0 */
    0x0000U, 0x1021U, 0x2042U, 0x3063U, 0x4084U, 0x50a5U, 0x60c6U, 0x70e7U,
    0x8108U, 0x9129U, 0xa14aU, 0xb16bU, 0xc18cU, 0xd1adU, 0xe1ceU, 0xf1efU,
  },
  { /* round 1 */
    0x0000U, 0x1231U, 0x2462U, 0x3653U, 0x48c4U, 0x5af5U, 0x6ca6U, 0x7e97U,
    0x9188U, 0x83b9U, 0xb5eaU, 0xa7dbU, 0xd94cU, 0xcb7dU, 0xfd2eU, 0xef1fU,
  },
  { /* round 2 */
    0x0000U, 0x3331U, 0x6662U, 0x5553U, 0xccc4U, 0xfff5U, 0xaaa6U, 0x9997U,
    0x89a9U, 0xba98U, 0xefcbU, 0xdcfaU, 0x456dU, 0x765cU, 0x230fU, 0x103eU,
  },
  { /* round 3 */
    0x0000U, 0x0373U, 0x06e6U, 0x0595U, 0x0dccU, 0x0ebfU, 0x0b2aU, 0x0859U,
    0x1b98U, 0x18ebU, 0x1d7eU, 0x1e0dU, 0x1654U, 0x1527U, 0x10b2U, 0x13c1U,
  },
  { /* round 4 */
    0x0000U, 0x3730U, 0x6e60U, 0x5950U, 0xdcc0U, 0xebf0U, 0xb2a0U, 0x8590U,
    0xa9a1U, 0x9e91U, 0xc7c1U, 0xf0f1U, 0x7561U, 0x4251U, 0x1b01U, 0x2c31U,
  },
  { /* round 5 */
    0x0000U, 0x4363U, 0x86c6U, 0xc5a5U, 0x1dadU, 0x5eceU, 0x9b6bU, 0xd808U,
    0x3b5aU, 0x7839U, 0xbd9cU, 0xfeffU, 0x26f7U, 0x6594U, 0xa031U, 0xe352U,
  },
  { /* round 6 */
    0x0000U, 0x76b4U, 0xed68U, 0x9bdcU, 0xcaf1U, 0xbc45U, 0x2799U, 0x512dU,
    0x85c3U, 0xf377U, 0x68abU, 0x1e1fU, 0x4f32U, 0x3986U, 0xa25aU, 0xd4eeU,
  },
  { /* round 7 */
    0x0000U, 0x1ba7U, 0x374eU, 0x2ce9U, 0x6e9cU, 0x753bU, 0x59d2U, 0x4275U,
    0xdd38U, 0xc69fU, 0xea76U, 0xf1d1U, 0xb3a4U, 0xa803U, 0x84eaU, 0x9f4dU,
  },
  { /* round 8 */
    0x0000U, 0xaa51U, 0x4483U, 0xeed2U, 0x8906U, 0x2357U, 0xcd85U, 0x67d4U,
    0x022dU, 0xa87cU, 0x46aeU, 0xecffU, 0x8b2bU, 0x217aU, 0xcfa8U, 0x65f9U,
  },
  { /* round 9 */
    0x0000U, 0x045aU, 0x08b4U, 0x0ceeU, 0x1168U, 0x1532U, 0x19dcU, 0x1d86U,
    0x22d0U, 0x268aU, 0x2a64U, 0x2e3eU, 0x33b8U, 0x37e2U, 0x3b0cU, 0x3f56U,
  },
  { /* round 10 */
    0x0000U, 0x45a0U, 0x8b40U, 0xcee0U, 0x06a1U, 0x4301U, 0x8de1U, 0xc841U,
    0x0d42U, 0x48e2U, 0x8602U, 0xc3a2U, 0x0be3U, 0x4e43U, 0x80a3U, 0xc503U,
  },
  { /* round 11 */
    0x0000U, 0x1a84U, 0x3508U, 0x2f8cU, 0x6a10U, 0x7094U, 0x5f18U, 0x459cU,
    0xd420U, 0xcea4U, 0xe128U, 0xfbacU, 0xbe30U, 0xa4b4U, 0x8b38U, 0x91bcU,
  },
  { /* round 12 */
    0x0000U, 0xb861U, 0x60e3U, 0xd882U, 0xc1c6U, 0x79a7U, 0xa125U, 0x1944U,
    0x93adU, 0x2bccU, 0xf34eU, 0x4b2fU, 0x526bU, 0xea0aU, 0x3288U, 0x8ae9U,
  },
  { /* round 13 */
    0x0000U, 0x377bU, 0x6ef6U, 0x598dU, 0xddecU, 0xea97U, 0xb31aU, 0x8461U,
    0xabf9U, 0x9c82U, 0xc50fU, 0xf274U, 0x7615U, 0x416eU, 0x18e3U, 0x2f98U,
  },
  { /* round 14 */
    0x0000U, 0x47d3U, 0x8fa6U, 0xc875U, 0x0f6dU, 0x48beU, 0x80cbU, 0xc718U,
    0x1edaU, 0x5909U, 0x917cU, 0xd6afU, 0x11b7U, 0x5664U, 0x9e11U, 0xd9c2U,
  },
  { /* round 15 */
    0x0000U, 0x3db4U, 0x7b68U, 0x46dcU, 0xf6d0U, 0xcb64U, 0x8db8U, 0xb00cU,
    0xfd81U, 0xc035U, 0x86e9U, 0xbb5dU, 0x0b51U, 0x36e5U, 0x7039U, 0x4d8dU,
  },
};
