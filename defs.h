#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/*
 * このソースコードに出てくる crc16 の定義は次の通りです:
 * - 16 ビット長
 * - 生成多項式は `0x11021`
 * - 入力に16ビットの `0` を前置する
 * - 順入力、順出力
 * - 初期 CRC 値は `0`
 * - 出力時の XOR パターンは `0`
 */

#define CRC16_POLYNOMIAL ((uint16_t)0x1021U)

/* from mruby-2.0.1 */
uint16_t calc_crc_16_ccitt(const uint8_t *src, size_t nbytes, uint16_t crc);

uint16_t crc16_bitwise_condxor(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_bitwise_branchassign(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_bitwise_branchmix(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_bitwise_branchless(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_bitcombine2(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_bitcombine4(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_bitcombine8(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_bitcombine16(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_bitcombine32(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_by_duo(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_by1_duo(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_by2_duo(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_by4_duo(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_by8_duo(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_by_quartet(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_by1_quartet(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_by2_quartet(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_by4_quartet(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_by8_quartet(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_by1_octet(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_by2_octet(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_by4_octet(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_by8_octet(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_by16_octet(const uint8_t *ptr, size_t num, uint16_t crc);
uint16_t crc16_parallelstride16(const uint8_t *ptr, size_t num, uint16_t crc);

const void *make_sample_data(size_t *size);
