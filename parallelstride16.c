/*
 * 参考: https://github.com/google/crc32c/blob/1.1.0/src/crc32c_portable.cc
 *
 * 正式な名称が不明なため、仮の名として「parallel stride 16」としている。
 */

#include "defs.h"
#include <stdint.h>

static const uint16_t bytetable[256];

// 今のところは2バイト単位での計算となるので、stridetable は過剰な要素を含んでいる
static const uint16_t stridetable[4][256];

static inline uint16_t
loadu16be(const void *ptr)
{
    const uint8_t *p = (const uint8_t *)ptr;
    return (p[0] << 8) | (p[1] << 0);
}

uint16_t
crc16_parallelstride16(const uint8_t *ptr, size_t num, uint16_t crc)
{
    if (num >= 18) {
        // 入力の前に0を詰める CRC 仕様なので、入力を伴わない16ビット分を計算する
        crc = bytetable[(crc >>  8) & 0xff] ^ (crc << 8);
        crc = bytetable[(crc >>  8) & 0xff] ^ (crc << 8);

        uint16_t s[8] = { crc, 0, 0, 0, 0, 0, 0, 0 };

        // 入力の前に0を詰める CRC 仕様なので、最後の2バイトを除き64バイト単位で処理を行う
        for (; num >= 66; num -= 64, ptr += 64) {
            s[0] = loadu16be(ptr +  0) ^ stridetable[3][(uint8_t)(s[0] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[0] >> 0) & 0xff];
            s[1] = loadu16be(ptr +  2) ^ stridetable[3][(uint8_t)(s[1] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[1] >> 0) & 0xff];
            s[2] = loadu16be(ptr +  4) ^ stridetable[3][(uint8_t)(s[2] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[2] >> 0) & 0xff];
            s[3] = loadu16be(ptr +  6) ^ stridetable[3][(uint8_t)(s[3] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[3] >> 0) & 0xff];
            s[4] = loadu16be(ptr +  8) ^ stridetable[3][(uint8_t)(s[4] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[4] >> 0) & 0xff];
            s[5] = loadu16be(ptr + 10) ^ stridetable[3][(uint8_t)(s[5] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[5] >> 0) & 0xff];
            s[6] = loadu16be(ptr + 12) ^ stridetable[3][(uint8_t)(s[6] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[6] >> 0) & 0xff];
            s[7] = loadu16be(ptr + 14) ^ stridetable[3][(uint8_t)(s[7] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[7] >> 0) & 0xff];

            s[0] = loadu16be(ptr + 16) ^ stridetable[3][(uint8_t)(s[0] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[0] >> 0) & 0xff];
            s[1] = loadu16be(ptr + 18) ^ stridetable[3][(uint8_t)(s[1] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[1] >> 0) & 0xff];
            s[2] = loadu16be(ptr + 20) ^ stridetable[3][(uint8_t)(s[2] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[2] >> 0) & 0xff];
            s[3] = loadu16be(ptr + 22) ^ stridetable[3][(uint8_t)(s[3] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[3] >> 0) & 0xff];
            s[4] = loadu16be(ptr + 24) ^ stridetable[3][(uint8_t)(s[4] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[4] >> 0) & 0xff];
            s[5] = loadu16be(ptr + 26) ^ stridetable[3][(uint8_t)(s[5] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[5] >> 0) & 0xff];
            s[6] = loadu16be(ptr + 28) ^ stridetable[3][(uint8_t)(s[6] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[6] >> 0) & 0xff];
            s[7] = loadu16be(ptr + 30) ^ stridetable[3][(uint8_t)(s[7] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[7] >> 0) & 0xff];

            s[0] = loadu16be(ptr + 32) ^ stridetable[3][(uint8_t)(s[0] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[0] >> 0) & 0xff];
            s[1] = loadu16be(ptr + 34) ^ stridetable[3][(uint8_t)(s[1] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[1] >> 0) & 0xff];
            s[2] = loadu16be(ptr + 36) ^ stridetable[3][(uint8_t)(s[2] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[2] >> 0) & 0xff];
            s[3] = loadu16be(ptr + 38) ^ stridetable[3][(uint8_t)(s[3] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[3] >> 0) & 0xff];
            s[4] = loadu16be(ptr + 40) ^ stridetable[3][(uint8_t)(s[4] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[4] >> 0) & 0xff];
            s[5] = loadu16be(ptr + 42) ^ stridetable[3][(uint8_t)(s[5] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[5] >> 0) & 0xff];
            s[6] = loadu16be(ptr + 44) ^ stridetable[3][(uint8_t)(s[6] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[6] >> 0) & 0xff];
            s[7] = loadu16be(ptr + 46) ^ stridetable[3][(uint8_t)(s[7] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[7] >> 0) & 0xff];

            s[0] = loadu16be(ptr + 48) ^ stridetable[3][(uint8_t)(s[0] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[0] >> 0) & 0xff];
            s[1] = loadu16be(ptr + 50) ^ stridetable[3][(uint8_t)(s[1] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[1] >> 0) & 0xff];
            s[2] = loadu16be(ptr + 52) ^ stridetable[3][(uint8_t)(s[2] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[2] >> 0) & 0xff];
            s[3] = loadu16be(ptr + 54) ^ stridetable[3][(uint8_t)(s[3] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[3] >> 0) & 0xff];
            s[4] = loadu16be(ptr + 56) ^ stridetable[3][(uint8_t)(s[4] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[4] >> 0) & 0xff];
            s[5] = loadu16be(ptr + 58) ^ stridetable[3][(uint8_t)(s[5] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[5] >> 0) & 0xff];
            s[6] = loadu16be(ptr + 60) ^ stridetable[3][(uint8_t)(s[6] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[6] >> 0) & 0xff];
            s[7] = loadu16be(ptr + 62) ^ stridetable[3][(uint8_t)(s[7] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[7] >> 0) & 0xff];
        }

        // 入力の前に0を詰める CRC 仕様なので、最後の2バイトを除き16バイト単位で処理を行う
        for (; num >= 18; num -= 16, ptr += 16) {
            s[0] = loadu16be(ptr +  0) ^ stridetable[3][(uint8_t)(s[0] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[0] >> 0) & 0xff];
            s[1] = loadu16be(ptr +  2) ^ stridetable[3][(uint8_t)(s[1] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[1] >> 0) & 0xff];
            s[2] = loadu16be(ptr +  4) ^ stridetable[3][(uint8_t)(s[2] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[2] >> 0) & 0xff];
            s[3] = loadu16be(ptr +  6) ^ stridetable[3][(uint8_t)(s[3] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[3] >> 0) & 0xff];
            s[4] = loadu16be(ptr +  8) ^ stridetable[3][(uint8_t)(s[4] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[4] >> 0) & 0xff];
            s[5] = loadu16be(ptr + 10) ^ stridetable[3][(uint8_t)(s[5] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[5] >> 0) & 0xff];
            s[6] = loadu16be(ptr + 12) ^ stridetable[3][(uint8_t)(s[6] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[6] >> 0) & 0xff];
            s[7] = loadu16be(ptr + 14) ^ stridetable[3][(uint8_t)(s[7] >> 8) & 0xff] ^ stridetable[2][(uint8_t)(s[7] >> 0) & 0xff];
        }

        crc = 0;
        for (int i = 0; i < 8; i ++) {
            crc ^= s[i];
            crc = bytetable[(crc >>  8) & 0xff] ^ (crc << 8);
            crc = bytetable[(crc >>  8) & 0xff] ^ (crc << 8);
        }

        // 入力の前に0を詰める CRC 仕様なので、2バイトが入力された状態にする
        crc ^= loadu16be(ptr);
        ptr += 2;
        num -= 2;
    }

    // 入力の前に0を詰める CRC 仕様に従って、1バイト単位で計算する
    for (; num > 0; num --, ptr ++) {
        crc = bytetable[(crc >>  8) & 0xff] ^ (crc << 8) ^ *ptr;
    }

    return crc;
}

#include <stdint.h>

static const uint16_t bytetable[256] =
{ /* round 0 */
  0x0000U, 0x1021U, 0x2042U, 0x3063U, 0x4084U, 0x50a5U, 0x60c6U, 0x70e7U,
  0x8108U, 0x9129U, 0xa14aU, 0xb16bU, 0xc18cU, 0xd1adU, 0xe1ceU, 0xf1efU,
  0x1231U, 0x0210U, 0x3273U, 0x2252U, 0x52b5U, 0x4294U, 0x72f7U, 0x62d6U,
  0x9339U, 0x8318U, 0xb37bU, 0xa35aU, 0xd3bdU, 0xc39cU, 0xf3ffU, 0xe3deU,
  0x2462U, 0x3443U, 0x0420U, 0x1401U, 0x64e6U, 0x74c7U, 0x44a4U, 0x5485U,
  0xa56aU, 0xb54bU, 0x8528U, 0x9509U, 0xe5eeU, 0xf5cfU, 0xc5acU, 0xd58dU,
  0x3653U, 0x2672U, 0x1611U, 0x0630U, 0x76d7U, 0x66f6U, 0x5695U, 0x46b4U,
  0xb75bU, 0xa77aU, 0x9719U, 0x8738U, 0xf7dfU, 0xe7feU, 0xd79dU, 0xc7bcU,
  0x48c4U, 0x58e5U, 0x6886U, 0x78a7U, 0x0840U, 0x1861U, 0x2802U, 0x3823U,
  0xc9ccU, 0xd9edU, 0xe98eU, 0xf9afU, 0x8948U, 0x9969U, 0xa90aU, 0xb92bU,
  0x5af5U, 0x4ad4U, 0x7ab7U, 0x6a96U, 0x1a71U, 0x0a50U, 0x3a33U, 0x2a12U,
  0xdbfdU, 0xcbdcU, 0xfbbfU, 0xeb9eU, 0x9b79U, 0x8b58U, 0xbb3bU, 0xab1aU,
  0x6ca6U, 0x7c87U, 0x4ce4U, 0x5cc5U, 0x2c22U, 0x3c03U, 0x0c60U, 0x1c41U,
  0xedaeU, 0xfd8fU, 0xcdecU, 0xddcdU, 0xad2aU, 0xbd0bU, 0x8d68U, 0x9d49U,
  0x7e97U, 0x6eb6U, 0x5ed5U, 0x4ef4U, 0x3e13U, 0x2e32U, 0x1e51U, 0x0e70U,
  0xff9fU, 0xefbeU, 0xdfddU, 0xcffcU, 0xbf1bU, 0xaf3aU, 0x9f59U, 0x8f78U,
  0x9188U, 0x81a9U, 0xb1caU, 0xa1ebU, 0xd10cU, 0xc12dU, 0xf14eU, 0xe16fU,
  0x1080U, 0x00a1U, 0x30c2U, 0x20e3U, 0x5004U, 0x4025U, 0x7046U, 0x6067U,
  0x83b9U, 0x9398U, 0xa3fbU, 0xb3daU, 0xc33dU, 0xd31cU, 0xe37fU, 0xf35eU,
  0x02b1U, 0x1290U, 0x22f3U, 0x32d2U, 0x4235U, 0x5214U, 0x6277U, 0x7256U,
  0xb5eaU, 0xa5cbU, 0x95a8U, 0x8589U, 0xf56eU, 0xe54fU, 0xd52cU, 0xc50dU,
  0x34e2U, 0x24c3U, 0x14a0U, 0x0481U, 0x7466U, 0x6447U, 0x5424U, 0x4405U,
  0xa7dbU, 0xb7faU, 0x8799U, 0x97b8U, 0xe75fU, 0xf77eU, 0xc71dU, 0xd73cU,
  0x26d3U, 0x36f2U, 0x0691U, 0x16b0U, 0x6657U, 0x7676U, 0x4615U, 0x5634U,
  0xd94cU, 0xc96dU, 0xf90eU, 0xe92fU, 0x99c8U, 0x89e9U, 0xb98aU, 0xa9abU,
  0x5844U, 0x4865U, 0x7806U, 0x6827U, 0x18c0U, 0x08e1U, 0x3882U, 0x28a3U,
  0xcb7dU, 0xdb5cU, 0xeb3fU, 0xfb1eU, 0x8bf9U, 0x9bd8U, 0xabbbU, 0xbb9aU,
  0x4a75U, 0x5a54U, 0x6a37U, 0x7a16U, 0x0af1U, 0x1ad0U, 0x2ab3U, 0x3a92U,
  0xfd2eU, 0xed0fU, 0xdd6cU, 0xcd4dU, 0xbdaaU, 0xad8bU, 0x9de8U, 0x8dc9U,
  0x7c26U, 0x6c07U, 0x5c64U, 0x4c45U, 0x3ca2U, 0x2c83U, 0x1ce0U, 0x0cc1U,
  0xef1fU, 0xff3eU, 0xcf5dU, 0xdf7cU, 0xaf9bU, 0xbfbaU, 0x8fd9U, 0x9ff8U,
  0x6e17U, 0x7e36U, 0x4e55U, 0x5e74U, 0x2e93U, 0x3eb2U, 0x0ed1U, 0x1ef0U,
};

static const uint16_t stridetable[4][256] =
{
  { /* round 12 */
    0x0000U, 0x4563U, 0x8ac6U, 0xcfa5U, 0x05adU, 0x40ceU, 0x8f6bU, 0xca08U,
    0x0b5aU, 0x4e39U, 0x819cU, 0xc4ffU, 0x0ef7U, 0x4b94U, 0x8431U, 0xc152U,
    0x16b4U, 0x53d7U, 0x9c72U, 0xd911U, 0x1319U, 0x567aU, 0x99dfU, 0xdcbcU,
    0x1deeU, 0x588dU, 0x9728U, 0xd24bU, 0x1843U, 0x5d20U, 0x9285U, 0xd7e6U,
    0x2d68U, 0x680bU, 0xa7aeU, 0xe2cdU, 0x28c5U, 0x6da6U, 0xa203U, 0xe760U,
    0x2632U, 0x6351U, 0xacf4U, 0xe997U, 0x239fU, 0x66fcU, 0xa959U, 0xec3aU,
    0x3bdcU, 0x7ebfU, 0xb11aU, 0xf479U, 0x3e71U, 0x7b12U, 0xb4b7U, 0xf1d4U,
    0x3086U, 0x75e5U, 0xba40U, 0xff23U, 0x352bU, 0x7048U, 0xbfedU, 0xfa8eU,
    0x5ad0U, 0x1fb3U, 0xd016U, 0x9575U, 0x5f7dU, 0x1a1eU, 0xd5bbU, 0x90d8U,
    0x518aU, 0x14e9U, 0xdb4cU, 0x9e2fU, 0x5427U, 0x1144U, 0xdee1U, 0x9b82U,
    0x4c64U, 0x0907U, 0xc6a2U, 0x83c1U, 0x49c9U, 0x0caaU, 0xc30fU, 0x866cU,
    0x473eU, 0x025dU, 0xcdf8U, 0x889bU, 0x4293U, 0x07f0U, 0xc855U, 0x8d36U,
    0x77b8U, 0x32dbU, 0xfd7eU, 0xb81dU, 0x7215U, 0x3776U, 0xf8d3U, 0xbdb0U,
    0x7ce2U, 0x3981U, 0xf624U, 0xb347U, 0x794fU, 0x3c2cU, 0xf389U, 0xb6eaU,
    0x610cU, 0x246fU, 0xebcaU, 0xaea9U, 0x64a1U, 0x21c2U, 0xee67U, 0xab04U,
    0x6a56U, 0x2f35U, 0xe090U, 0xa5f3U, 0x6ffbU, 0x2a98U, 0xe53dU, 0xa05eU,
    0xb5a0U, 0xf0c3U, 0x3f66U, 0x7a05U, 0xb00dU, 0xf56eU, 0x3acbU, 0x7fa8U,
    0xbefaU, 0xfb99U, 0x343cU, 0x715fU, 0xbb57U, 0xfe34U, 0x3191U, 0x74f2U,
    0xa314U, 0xe677U, 0x29d2U, 0x6cb1U, 0xa6b9U, 0xe3daU, 0x2c7fU, 0x691cU,
    0xa84eU, 0xed2dU, 0x2288U, 0x67ebU, 0xade3U, 0xe880U, 0x2725U, 0x6246U,
    0x98c8U, 0xddabU, 0x120eU, 0x576dU, 0x9d65U, 0xd806U, 0x17a3U, 0x52c0U,
    0x9392U, 0xd6f1U, 0x1954U, 0x5c37U, 0x963fU, 0xd35cU, 0x1cf9U, 0x599aU,
    0x8e7cU, 0xcb1fU, 0x04baU, 0x41d9U, 0x8bd1U, 0xceb2U, 0x0117U, 0x4474U,
    0x8526U, 0xc045U, 0x0fe0U, 0x4a83U, 0x808bU, 0xc5e8U, 0x0a4dU, 0x4f2eU,
    0xef70U, 0xaa13U, 0x65b6U, 0x20d5U, 0xeaddU, 0xafbeU, 0x601bU, 0x2578U,
    0xe42aU, 0xa149U, 0x6eecU, 0x2b8fU, 0xe187U, 0xa4e4U, 0x6b41U, 0x2e22U,
    0xf9c4U, 0xbca7U, 0x7302U, 0x3661U, 0xfc69U, 0xb90aU, 0x76afU, 0x33ccU,
    0xf29eU, 0xb7fdU, 0x7858U, 0x3d3bU, 0xf733U, 0xb250U, 0x7df5U, 0x3896U,
    0xc218U, 0x877bU, 0x48deU, 0x0dbdU, 0xc7b5U, 0x82d6U, 0x4d73U, 0x0810U,
    0xc942U, 0x8c21U, 0x4384U, 0x06e7U, 0xccefU, 0x898cU, 0x4629U, 0x034aU,
    0xd4acU, 0x91cfU, 0x5e6aU, 0x1b09U, 0xd101U, 0x9462U, 0x5bc7U, 0x1ea4U,
    0xdff6U, 0x9a95U, 0x5530U, 0x1053U, 0xda5bU, 0x9f38U, 0x509dU, 0x15feU,
  },
  { /* round 13 */
    0x0000U, 0x7b61U, 0xf6c2U, 0x8da3U, 0xfda5U, 0x86c4U, 0x0b67U, 0x7006U,
    0xeb6bU, 0x900aU, 0x1da9U, 0x66c8U, 0x16ceU, 0x6dafU, 0xe00cU, 0x9b6dU,
    0xc6f7U, 0xbd96U, 0x3035U, 0x4b54U, 0x3b52U, 0x4033U, 0xcd90U, 0xb6f1U,
    0x2d9cU, 0x56fdU, 0xdb5eU, 0xa03fU, 0xd039U, 0xab58U, 0x26fbU, 0x5d9aU,
    0x9dcfU, 0xe6aeU, 0x6b0dU, 0x106cU, 0x606aU, 0x1b0bU, 0x96a8U, 0xedc9U,
    0x76a4U, 0x0dc5U, 0x8066U, 0xfb07U, 0x8b01U, 0xf060U, 0x7dc3U, 0x06a2U,
    0x5b38U, 0x2059U, 0xadfaU, 0xd69bU, 0xa69dU, 0xddfcU, 0x505fU, 0x2b3eU,
    0xb053U, 0xcb32U, 0x4691U, 0x3df0U, 0x4df6U, 0x3697U, 0xbb34U, 0xc055U,
    0x2bbfU, 0x50deU, 0xdd7dU, 0xa61cU, 0xd61aU, 0xad7bU, 0x20d8U, 0x5bb9U,
    0xc0d4U, 0xbbb5U, 0x3616U, 0x4d77U, 0x3d71U, 0x4610U, 0xcbb3U, 0xb0d2U,
    0xed48U, 0x9629U, 0x1b8aU, 0x60ebU, 0x10edU, 0x6b8cU, 0xe62fU, 0x9d4eU,
    0x0623U, 0x7d42U, 0xf0e1U, 0x8b80U, 0xfb86U, 0x80e7U, 0x0d44U, 0x7625U,
    0xb670U, 0xcd11U, 0x40b2U, 0x3bd3U, 0x4bd5U, 0x30b4U, 0xbd17U, 0xc676U,
    0x5d1bU, 0x267aU, 0xabd9U, 0xd0b8U, 0xa0beU, 0xdbdfU, 0x567cU, 0x2d1dU,
    0x7087U, 0x0be6U, 0x8645U, 0xfd24U, 0x8d22U, 0xf643U, 0x7be0U, 0x0081U,
    0x9becU, 0xe08dU, 0x6d2eU, 0x164fU, 0x6649U, 0x1d28U, 0x908bU, 0xebeaU,
    0x577eU, 0x2c1fU, 0xa1bcU, 0xdaddU, 0xaadbU, 0xd1baU, 0x5c19U, 0x2778U,
    0xbc15U, 0xc774U, 0x4ad7U, 0x31b6U, 0x41b0U, 0x3ad1U, 0xb772U, 0xcc13U,
    0x9189U, 0xeae8U, 0x674bU, 0x1c2aU, 0x6c2cU, 0x174dU, 0x9aeeU, 0xe18fU,
    0x7ae2U, 0x0183U, 0x8c20U, 0xf741U, 0x8747U, 0xfc26U, 0x7185U, 0x0ae4U,
    0xcab1U, 0xb1d0U, 0x3c73U, 0x4712U, 0x3714U, 0x4c75U, 0xc1d6U, 0xbab7U,
    0x21daU, 0x5abbU, 0xd718U, 0xac79U, 0xdc7fU, 0xa71eU, 0x2abdU, 0x51dcU,
    0x0c46U, 0x7727U, 0xfa84U, 0x81e5U, 0xf1e3U, 0x8a82U, 0x0721U, 0x7c40U,
    0xe72dU, 0x9c4cU, 0x11efU, 0x6a8eU, 0x1a88U, 0x61e9U, 0xec4aU, 0x972bU,
    0x7cc1U, 0x07a0U, 0x8a03U, 0xf162U, 0x8164U, 0xfa05U, 0x77a6U, 0x0cc7U,
    0x97aaU, 0xeccbU, 0x6168U, 0x1a09U, 0x6a0fU, 0x116eU, 0x9ccdU, 0xe7acU,
    0xba36U, 0xc157U, 0x4cf4U, 0x3795U, 0x4793U, 0x3cf2U, 0xb151U, 0xca30U,
    0x515dU, 0x2a3cU, 0xa79fU, 0xdcfeU, 0xacf8U, 0xd799U, 0x5a3aU, 0x215bU,
    0xe10eU, 0x9a6fU, 0x17ccU, 0x6cadU, 0x1cabU, 0x67caU, 0xea69U, 0x9108U,
    0x0a65U, 0x7104U, 0xfca7U, 0x87c6U, 0xf7c0U, 0x8ca1U, 0x0102U, 0x7a63U,
    0x27f9U, 0x5c98U, 0xd13bU, 0xaa5aU, 0xda5cU, 0xa13dU, 0x2c9eU, 0x57ffU,
    0xcc92U, 0xb7f3U, 0x3a50U, 0x4131U, 0x3137U, 0x4a56U, 0xc7f5U, 0xbc94U,
  },
  { /* round 14 */
    0x0000U, 0xaefcU, 0x4dd9U, 0xe325U, 0x9bb2U, 0x354eU, 0xd66bU, 0x7897U,
    0x2745U, 0x89b9U, 0x6a9cU, 0xc460U, 0xbcf7U, 0x120bU, 0xf12eU, 0x5fd2U,
    0x4e8aU, 0xe076U, 0x0353U, 0xadafU, 0xd538U, 0x7bc4U, 0x98e1U, 0x361dU,
    0x69cfU, 0xc733U, 0x2416U, 0x8aeaU, 0xf27dU, 0x5c81U, 0xbfa4U, 0x1158U,
    0x9d14U, 0x33e8U, 0xd0cdU, 0x7e31U, 0x06a6U, 0xa85aU, 0x4b7fU, 0xe583U,
    0xba51U, 0x14adU, 0xf788U, 0x5974U, 0x21e3U, 0x8f1fU, 0x6c3aU, 0xc2c6U,
    0xd39eU, 0x7d62U, 0x9e47U, 0x30bbU, 0x482cU, 0xe6d0U, 0x05f5U, 0xab09U,
    0xf4dbU, 0x5a27U, 0xb902U, 0x17feU, 0x6f69U, 0xc195U, 0x22b0U, 0x8c4cU,
    0x2a09U, 0x84f5U, 0x67d0U, 0xc92cU, 0xb1bbU, 0x1f47U, 0xfc62U, 0x529eU,
    0x0d4cU, 0xa3b0U, 0x4095U, 0xee69U, 0x96feU, 0x3802U, 0xdb27U, 0x75dbU,
    0x6483U, 0xca7fU, 0x295aU, 0x87a6U, 0xff31U, 0x51cdU, 0xb2e8U, 0x1c14U,
    0x43c6U, 0xed3aU, 0x0e1fU, 0xa0e3U, 0xd874U, 0x7688U, 0x95adU, 0x3b51U,
    0xb71dU, 0x19e1U, 0xfac4U, 0x5438U, 0x2cafU, 0x8253U, 0x6176U, 0xcf8aU,
    0x9058U, 0x3ea4U, 0xdd81U, 0x737dU, 0x0beaU, 0xa516U, 0x4633U, 0xe8cfU,
    0xf997U, 0x576bU, 0xb44eU, 0x1ab2U, 0x6225U, 0xccd9U, 0x2ffcU, 0x8100U,
    0xded2U, 0x702eU, 0x930bU, 0x3df7U, 0x4560U, 0xeb9cU, 0x08b9U, 0xa645U,
    0x5412U, 0xfaeeU, 0x19cbU, 0xb737U, 0xcfa0U, 0x615cU, 0x8279U, 0x2c85U,
    0x7357U, 0xddabU, 0x3e8eU, 0x9072U, 0xe8e5U, 0x4619U, 0xa53cU, 0x0bc0U,
    0x1a98U, 0xb464U, 0x5741U, 0xf9bdU, 0x812aU, 0x2fd6U, 0xccf3U, 0x620fU,
    0x3dddU, 0x9321U, 0x7004U, 0xdef8U, 0xa66fU, 0x0893U, 0xebb6U, 0x454aU,
    0xc906U, 0x67faU, 0x84dfU, 0x2a23U, 0x52b4U, 0xfc48U, 0x1f6dU, 0xb191U,
    0xee43U, 0x40bfU, 0xa39aU, 0x0d66U, 0x75f1U, 0xdb0dU, 0x3828U, 0x96d4U,
    0x878cU, 0x2970U, 0xca55U, 0x64a9U, 0x1c3eU, 0xb2c2U, 0x51e7U, 0xff1bU,
    0xa0c9U, 0x0e35U, 0xed10U, 0x43ecU, 0x3b7bU, 0x9587U, 0x76a2U, 0xd85eU,
    0x7e1bU, 0xd0e7U, 0x33c2U, 0x9d3eU, 0xe5a9U, 0x4b55U, 0xa870U, 0x068cU,
    0x595eU, 0xf7a2U, 0x1487U, 0xba7bU, 0xc2ecU, 0x6c10U, 0x8f35U, 0x21c9U,
    0x3091U, 0x9e6dU, 0x7d48U, 0xd3b4U, 0xab23U, 0x05dfU, 0xe6faU, 0x4806U,
    0x17d4U, 0xb928U, 0x5a0dU, 0xf4f1U, 0x8c66U, 0x229aU, 0xc1bfU, 0x6f43U,
    0xe30fU, 0x4df3U, 0xaed6U, 0x002aU, 0x78bdU, 0xd641U, 0x3564U, 0x9b98U,
    0xc44aU, 0x6ab6U, 0x8993U, 0x276fU, 0x5ff8U, 0xf104U, 0x1221U, 0xbcddU,
    0xad85U, 0x0379U, 0xe05cU, 0x4ea0U, 0x3637U, 0x98cbU, 0x7beeU, 0xd512U,
    0x8ac0U, 0x243cU, 0xc719U, 0x69e5U, 0x1172U, 0xbf8eU, 0x5cabU, 0xf257U,
  },
  { /* round 15 */
    0x0000U, 0xa824U, 0x4069U, 0xe84dU, 0x80d2U, 0x28f6U, 0xc0bbU, 0x689fU,
    0x1185U, 0xb9a1U, 0x51ecU, 0xf9c8U, 0x9157U, 0x3973U, 0xd13eU, 0x791aU,
    0x230aU, 0x8b2eU, 0x6363U, 0xcb47U, 0xa3d8U, 0x0bfcU, 0xe3b1U, 0x4b95U,
    0x328fU, 0x9aabU, 0x72e6U, 0xdac2U, 0xb25dU, 0x1a79U, 0xf234U, 0x5a10U,
    0x4614U, 0xee30U, 0x067dU, 0xae59U, 0xc6c6U, 0x6ee2U, 0x86afU, 0x2e8bU,
    0x5791U, 0xffb5U, 0x17f8U, 0xbfdcU, 0xd743U, 0x7f67U, 0x972aU, 0x3f0eU,
    0x651eU, 0xcd3aU, 0x2577U, 0x8d53U, 0xe5ccU, 0x4de8U, 0xa5a5U, 0x0d81U,
    0x749bU, 0xdcbfU, 0x34f2U, 0x9cd6U, 0xf449U, 0x5c6dU, 0xb420U, 0x1c04U,
    0x8c28U, 0x240cU, 0xcc41U, 0x6465U, 0x0cfaU, 0xa4deU, 0x4c93U, 0xe4b7U,
    0x9dadU, 0x3589U, 0xddc4U, 0x75e0U, 0x1d7fU, 0xb55bU, 0x5d16U, 0xf532U,
    0xaf22U, 0x0706U, 0xef4bU, 0x476fU, 0x2ff0U, 0x87d4U, 0x6f99U, 0xc7bdU,
    0xbea7U, 0x1683U, 0xfeceU, 0x56eaU, 0x3e75U, 0x9651U, 0x7e1cU, 0xd638U,
    0xca3cU, 0x6218U, 0x8a55U, 0x2271U, 0x4aeeU, 0xe2caU, 0x0a87U, 0xa2a3U,
    0xdbb9U, 0x739dU, 0x9bd0U, 0x33f4U, 0x5b6bU, 0xf34fU, 0x1b02U, 0xb326U,
    0xe936U, 0x4112U, 0xa95fU, 0x017bU, 0x69e4U, 0xc1c0U, 0x298dU, 0x81a9U,
    0xf8b3U, 0x5097U, 0xb8daU, 0x10feU, 0x7861U, 0xd045U, 0x3808U, 0x902cU,
    0x0871U, 0xa055U, 0x4818U, 0xe03cU, 0x88a3U, 0x2087U, 0xc8caU, 0x60eeU,
    0x19f4U, 0xb1d0U, 0x599dU, 0xf1b9U, 0x9926U, 0x3102U, 0xd94fU, 0x716bU,
    0x2b7bU, 0x835fU, 0x6b12U, 0xc336U, 0xaba9U, 0x038dU, 0xebc0U, 0x43e4U,
    0x3afeU, 0x92daU, 0x7a97U, 0xd2b3U, 0xba2cU, 0x1208U, 0xfa45U, 0x5261U,
    0x4e65U, 0xe641U, 0x0e0cU, 0xa628U, 0xceb7U, 0x6693U, 0x8edeU, 0x26faU,
    0x5fe0U, 0xf7c4U, 0x1f89U, 0xb7adU, 0xdf32U, 0x7716U, 0x9f5bU, 0x377fU,
    0x6d6fU, 0xc54bU, 0x2d06U, 0x8522U, 0xedbdU, 0x4599U, 0xadd4U, 0x05f0U,
    0x7ceaU, 0xd4ceU, 0x3c83U, 0x94a7U, 0xfc38U, 0x541cU, 0xbc51U, 0x1475U,
    0x8459U, 0x2c7dU, 0xc430U, 0x6c14U, 0x048bU, 0xacafU, 0x44e2U, 0xecc6U,
    0x95dcU, 0x3df8U, 0xd5b5U, 0x7d91U, 0x150eU, 0xbd2aU, 0x5567U, 0xfd43U,
    0xa753U, 0x0f77U, 0xe73aU, 0x4f1eU, 0x2781U, 0x8fa5U, 0x67e8U, 0xcfccU,
    0xb6d6U, 0x1ef2U, 0xf6bfU, 0x5e9bU, 0x3604U, 0x9e20U, 0x766dU, 0xde49U,
    0xc24dU, 0x6a69U, 0x8224U, 0x2a00U, 0x429fU, 0xeabbU, 0x02f6U, 0xaad2U,
    0xd3c8U, 0x7becU, 0x93a1U, 0x3b85U, 0x531aU, 0xfb3eU, 0x1373U, 0xbb57U,
    0xe147U, 0x4963U, 0xa12eU, 0x090aU, 0x6195U, 0xc9b1U, 0x21fcU, 0x89d8U,
    0xf0c2U, 0x58e6U, 0xb0abU, 0x188fU, 0x7010U, 0xd834U, 0x3079U, 0x985dU,
  },
};