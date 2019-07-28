#include "defs.h"

uint16_t
crc16_bitcombine2(const uint8_t *ptr, size_t num, uint16_t crc)
{
    const uint16_t g0 = CRC16_POLYNOMIAL,
                   g1 = (uint16_t)(g0 << 1) ^ (uint16_t)(-(g0 >> 15) & CRC16_POLYNOMIAL);

    for (; num > 0; num --, ptr ++) {
        crc = (crc << 2) ^
              (g1 & -((crc >> 15) & 1)) ^
              (g0 & -((crc >> 14) & 1));
        crc = (crc << 2) ^
              (g1 & -((crc >> 15) & 1)) ^
              (g0 & -((crc >> 14) & 1));
        crc = (crc << 2) ^
              (g1 & -((crc >> 15) & 1)) ^
              (g0 & -((crc >> 14) & 1));
        crc = (crc << 2) ^
              (g1 & -((crc >> 15) & 1)) ^
              (g0 & -((crc >> 14) & 1));
        crc ^= *ptr;
    }

    return crc;
}

uint16_t
crc16_bitcombine4(const uint8_t *ptr, size_t num, uint16_t crc)
{
    const uint16_t g0 = CRC16_POLYNOMIAL,
                   g1 = (uint16_t)(g0 << 1) ^ (uint16_t)(-(g0 >> 15) & CRC16_POLYNOMIAL),
                   g2 = (uint16_t)(g1 << 1) ^ (uint16_t)(-(g1 >> 15) & CRC16_POLYNOMIAL),
                   g3 = (uint16_t)(g2 << 1) ^ (uint16_t)(-(g2 >> 15) & CRC16_POLYNOMIAL);

    for (; num > 0; num --, ptr ++) {
        crc = (crc << 4) ^
              (g3 & -((crc >> 15) & 1)) ^
              (g2 & -((crc >> 14) & 1)) ^
              (g1 & -((crc >> 13) & 1)) ^
              (g0 & -((crc >> 12) & 1));
        crc = (crc << 4) ^
              (g3 & -((crc >> 15) & 1)) ^
              (g2 & -((crc >> 14) & 1)) ^
              (g1 & -((crc >> 13) & 1)) ^
              (g0 & -((crc >> 12) & 1));
        crc ^= *ptr;
    }

    return crc;
}

uint16_t
crc16_bitcombine8(const uint8_t *ptr, size_t num, uint16_t crc)
{
    const uint16_t g0 = CRC16_POLYNOMIAL,
                   g1 = (uint16_t)(g0 << 1) ^ (uint16_t)(-(g0 >> 15) & CRC16_POLYNOMIAL),
                   g2 = (uint16_t)(g1 << 1) ^ (uint16_t)(-(g1 >> 15) & CRC16_POLYNOMIAL),
                   g3 = (uint16_t)(g2 << 1) ^ (uint16_t)(-(g2 >> 15) & CRC16_POLYNOMIAL),
                   g4 = (uint16_t)(g3 << 1) ^ (uint16_t)(-(g3 >> 15) & CRC16_POLYNOMIAL),
                   g5 = (uint16_t)(g4 << 1) ^ (uint16_t)(-(g4 >> 15) & CRC16_POLYNOMIAL),
                   g6 = (uint16_t)(g5 << 1) ^ (uint16_t)(-(g5 >> 15) & CRC16_POLYNOMIAL),
                   g7 = (uint16_t)(g6 << 1) ^ (uint16_t)(-(g6 >> 15) & CRC16_POLYNOMIAL);

    for (; num > 0; num --, ptr ++) {
        crc = (g7 & -((crc >> 15) & 1)) ^
              (g6 & -((crc >> 14) & 1)) ^
              (g5 & -((crc >> 13) & 1)) ^
              (g4 & -((crc >> 12) & 1)) ^
              (g3 & -((crc >> 11) & 1)) ^
              (g2 & -((crc >> 10) & 1)) ^
              (g1 & -((crc >>  9) & 1)) ^
              (g0 & -((crc >>  8) & 1)) ^
              (crc << 8) ^ *ptr;
    }

    return crc;
}

uint16_t
crc16_bitcombine16(const uint8_t *ptr, size_t num, uint16_t crc)
{
    const uint16_t g0 = CRC16_POLYNOMIAL,
                   g1 = (uint16_t)(g0 << 1) ^ (uint16_t)(-(g0 >> 15) & CRC16_POLYNOMIAL),
                   g2 = (uint16_t)(g1 << 1) ^ (uint16_t)(-(g1 >> 15) & CRC16_POLYNOMIAL),
                   g3 = (uint16_t)(g2 << 1) ^ (uint16_t)(-(g2 >> 15) & CRC16_POLYNOMIAL),
                   g4 = (uint16_t)(g3 << 1) ^ (uint16_t)(-(g3 >> 15) & CRC16_POLYNOMIAL),
                   g5 = (uint16_t)(g4 << 1) ^ (uint16_t)(-(g4 >> 15) & CRC16_POLYNOMIAL),
                   g6 = (uint16_t)(g5 << 1) ^ (uint16_t)(-(g5 >> 15) & CRC16_POLYNOMIAL),
                   g7 = (uint16_t)(g6 << 1) ^ (uint16_t)(-(g6 >> 15) & CRC16_POLYNOMIAL),
                   g8 = (uint16_t)(g7 << 1) ^ (uint16_t)(-(g7 >> 15) & CRC16_POLYNOMIAL),
                   g9 = (uint16_t)(g8 << 1) ^ (uint16_t)(-(g8 >> 15) & CRC16_POLYNOMIAL),
                   gA = (uint16_t)(g9 << 1) ^ (uint16_t)(-(g9 >> 15) & CRC16_POLYNOMIAL),
                   gB = (uint16_t)(gA << 1) ^ (uint16_t)(-(gA >> 15) & CRC16_POLYNOMIAL),
                   gC = (uint16_t)(gB << 1) ^ (uint16_t)(-(gB >> 15) & CRC16_POLYNOMIAL),
                   gD = (uint16_t)(gC << 1) ^ (uint16_t)(-(gC >> 15) & CRC16_POLYNOMIAL),
                   gE = (uint16_t)(gD << 1) ^ (uint16_t)(-(gD >> 15) & CRC16_POLYNOMIAL),
                   gF = (uint16_t)(gE << 1) ^ (uint16_t)(-(gE >> 15) & CRC16_POLYNOMIAL);

    for (; num >= 2; num -= 2, ptr += 2) {
        crc = (gF & -((crc >> 15) & 1)) ^
              (gE & -((crc >> 14) & 1)) ^
              (gD & -((crc >> 13) & 1)) ^
              (gC & -((crc >> 12) & 1)) ^
              (gB & -((crc >> 11) & 1)) ^
              (gA & -((crc >> 10) & 1)) ^
              (g9 & -((crc >>  9) & 1)) ^
              (g8 & -((crc >>  8) & 1)) ^
              (g7 & -((crc >>  7) & 1)) ^
              (g6 & -((crc >>  6) & 1)) ^
              (g5 & -((crc >>  5) & 1)) ^
              (g4 & -((crc >>  4) & 1)) ^
              (g3 & -((crc >>  3) & 1)) ^
              (g2 & -((crc >>  2) & 1)) ^
              (g1 & -((crc >>  1) & 1)) ^
              (g0 & -((crc >>  0) & 1)) ^
              (ptr[0] << 8) ^ (ptr[1] << 0);
    }

    for (; num > 0; num --, ptr ++) {
        crc = (g7 & -((crc >> 15) & 1)) ^
              (g6 & -((crc >> 14) & 1)) ^
              (g5 & -((crc >> 13) & 1)) ^
              (g4 & -((crc >> 12) & 1)) ^
              (g3 & -((crc >> 11) & 1)) ^
              (g2 & -((crc >> 10) & 1)) ^
              (g1 & -((crc >>  9) & 1)) ^
              (g0 & -((crc >>  8) & 1)) ^
              (crc << 8) ^ *ptr;
    }

    return crc;
}

uint16_t
crc16_bitcombine32(const uint8_t *ptr, size_t num, uint16_t crc)
{
    const uint16_t g0 = CRC16_POLYNOMIAL,
                   g1 = (uint16_t)(g0 << 1) ^ (uint16_t)(-(g0 >> 15) & CRC16_POLYNOMIAL),
                   g2 = (uint16_t)(g1 << 1) ^ (uint16_t)(-(g1 >> 15) & CRC16_POLYNOMIAL),
                   g3 = (uint16_t)(g2 << 1) ^ (uint16_t)(-(g2 >> 15) & CRC16_POLYNOMIAL),
                   g4 = (uint16_t)(g3 << 1) ^ (uint16_t)(-(g3 >> 15) & CRC16_POLYNOMIAL),
                   g5 = (uint16_t)(g4 << 1) ^ (uint16_t)(-(g4 >> 15) & CRC16_POLYNOMIAL),
                   g6 = (uint16_t)(g5 << 1) ^ (uint16_t)(-(g5 >> 15) & CRC16_POLYNOMIAL),
                   g7 = (uint16_t)(g6 << 1) ^ (uint16_t)(-(g6 >> 15) & CRC16_POLYNOMIAL),
                   g8 = (uint16_t)(g7 << 1) ^ (uint16_t)(-(g7 >> 15) & CRC16_POLYNOMIAL),
                   g9 = (uint16_t)(g8 << 1) ^ (uint16_t)(-(g8 >> 15) & CRC16_POLYNOMIAL),
                   gA = (uint16_t)(g9 << 1) ^ (uint16_t)(-(g9 >> 15) & CRC16_POLYNOMIAL),
                   gB = (uint16_t)(gA << 1) ^ (uint16_t)(-(gA >> 15) & CRC16_POLYNOMIAL),
                   gC = (uint16_t)(gB << 1) ^ (uint16_t)(-(gB >> 15) & CRC16_POLYNOMIAL),
                   gD = (uint16_t)(gC << 1) ^ (uint16_t)(-(gC >> 15) & CRC16_POLYNOMIAL),
                   gE = (uint16_t)(gD << 1) ^ (uint16_t)(-(gD >> 15) & CRC16_POLYNOMIAL),
                   gF = (uint16_t)(gE << 1) ^ (uint16_t)(-(gE >> 15) & CRC16_POLYNOMIAL),
                   gG = (uint16_t)(gF << 1) ^ (uint16_t)(-(gF >> 15) & CRC16_POLYNOMIAL),
                   gH = (uint16_t)(gG << 1) ^ (uint16_t)(-(gG >> 15) & CRC16_POLYNOMIAL),
                   gI = (uint16_t)(gH << 1) ^ (uint16_t)(-(gH >> 15) & CRC16_POLYNOMIAL),
                   gJ = (uint16_t)(gI << 1) ^ (uint16_t)(-(gI >> 15) & CRC16_POLYNOMIAL),
                   gK = (uint16_t)(gJ << 1) ^ (uint16_t)(-(gJ >> 15) & CRC16_POLYNOMIAL),
                   gL = (uint16_t)(gK << 1) ^ (uint16_t)(-(gK >> 15) & CRC16_POLYNOMIAL),
                   gM = (uint16_t)(gL << 1) ^ (uint16_t)(-(gL >> 15) & CRC16_POLYNOMIAL),
                   gN = (uint16_t)(gM << 1) ^ (uint16_t)(-(gM >> 15) & CRC16_POLYNOMIAL),
                   gO = (uint16_t)(gN << 1) ^ (uint16_t)(-(gN >> 15) & CRC16_POLYNOMIAL),
                   gP = (uint16_t)(gO << 1) ^ (uint16_t)(-(gO >> 15) & CRC16_POLYNOMIAL),
                   gQ = (uint16_t)(gP << 1) ^ (uint16_t)(-(gP >> 15) & CRC16_POLYNOMIAL),
                   gR = (uint16_t)(gQ << 1) ^ (uint16_t)(-(gQ >> 15) & CRC16_POLYNOMIAL),
                   gS = (uint16_t)(gR << 1) ^ (uint16_t)(-(gR >> 15) & CRC16_POLYNOMIAL),
                   gT = (uint16_t)(gS << 1) ^ (uint16_t)(-(gS >> 15) & CRC16_POLYNOMIAL),
                   gU = (uint16_t)(gT << 1) ^ (uint16_t)(-(gT >> 15) & CRC16_POLYNOMIAL),
                   gV = (uint16_t)(gU << 1) ^ (uint16_t)(-(gU >> 15) & CRC16_POLYNOMIAL);

    for (; num >= 4; num -= 4, ptr += 4) {
        uint8_t a = ptr[0];
        uint8_t b = ptr[1];

        crc = (gV & -((crc >> 15) & 1)) ^
              (gU & -((crc >> 14) & 1)) ^
              (gT & -((crc >> 13) & 1)) ^
              (gS & -((crc >> 12) & 1)) ^
              (gR & -((crc >> 11) & 1)) ^
              (gQ & -((crc >> 10) & 1)) ^
              (gP & -((crc >>  9) & 1)) ^
              (gO & -((crc >>  8) & 1)) ^
              (gN & -((crc >>  7) & 1)) ^
              (gM & -((crc >>  6) & 1)) ^
              (gL & -((crc >>  5) & 1)) ^
              (gK & -((crc >>  4) & 1)) ^
              (gJ & -((crc >>  3) & 1)) ^
              (gI & -((crc >>  2) & 1)) ^
              (gH & -((crc >>  1) & 1)) ^
              (gG & -((crc >>  0) & 1)) ^
              (gF & -((a   >>  7) & 1)) ^
              (gE & -((a   >>  6) & 1)) ^
              (gD & -((a   >>  5) & 1)) ^
              (gC & -((a   >>  4) & 1)) ^
              (gB & -((a   >>  3) & 1)) ^
              (gA & -((a   >>  2) & 1)) ^
              (g9 & -((a   >>  1) & 1)) ^
              (g8 & -((a   >>  0) & 1)) ^
              (g7 & -((b   >>  7) & 1)) ^
              (g6 & -((b   >>  6) & 1)) ^
              (g5 & -((b   >>  5) & 1)) ^
              (g4 & -((b   >>  4) & 1)) ^
              (g3 & -((b   >>  3) & 1)) ^
              (g2 & -((b   >>  2) & 1)) ^
              (g1 & -((b   >>  1) & 1)) ^
              (g0 & -((b   >>  0) & 1)) ^
              (ptr[2] << 8) ^ (ptr[3] << 0);
    }

    for (; num > 0; num --, ptr ++) {
        crc = (g7 & -((crc >> 15) & 1)) ^
              (g6 & -((crc >> 14) & 1)) ^
              (g5 & -((crc >> 13) & 1)) ^
              (g4 & -((crc >> 12) & 1)) ^
              (g3 & -((crc >> 11) & 1)) ^
              (g2 & -((crc >> 10) & 1)) ^
              (g1 & -((crc >>  9) & 1)) ^
              (g0 & -((crc >>  8) & 1)) ^
              (crc << 8) ^ *ptr;
    }

    return crc;
}
