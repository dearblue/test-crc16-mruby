#include "defs.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef __unix__
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>

double
ptime(void)
{
    struct rusage ru;
    getrusage(0, &ru);
    return ru.ru_utime.tv_sec + (double)ru.ru_utime.tv_usec / 1000000.0;
}
#else
# include <time.h>

double
ptime(void)
{
    return (double)clock() / CLOCKS_PER_SEC;
}
#endif

int
main(int argc, char *argv[])
{
    srandomdev();

    size_t size = (random() % 0x100000) + (49 << 20); // 49 MiB + alpha
    const char *sampledata = make_sample_data(&size);
    if (sampledata == NULL) {
        fprintf(stderr, "%s:%d:%s: make_sample_data() が失敗！\n", __FILE__, __LINE__, __func__);
        return 1;
    }

    uint16_t reference_crc;

#define MEASURE(funct)                                                      \
    do {                                                                    \
        double start = ptime();                                             \
        uint16_t crc = funct((const uint8_t *)sampledata, size, 0);         \
        double delta = ptime() - start;                                     \
        if ((funct) == calc_crc_16_ccitt) {                                 \
            reference_crc = crc;                                            \
            printf("%04x  %8.3f sec  (%8.2f MB / s)  %s\n",                 \
                   crc, delta, size / 1000000.0 / delta, #funct);           \
        } else {                                                            \
            printf("%-4s  %8.3f sec  (%8.2f MB / s)  %s\n",                 \
                   (reference_crc == crc ? "OK" : "BAD"),                   \
                   delta, size / 1000000.0 / delta, #funct);                \
        }                                                                   \
    } while (0)                                                             \

    MEASURE(calc_crc_16_ccitt);
    MEASURE(crc16_bitwise_condxor);
    MEASURE(crc16_bitwise_branchassign);
    MEASURE(crc16_bitwise_branchmix);
    MEASURE(crc16_bitwise_branchless);
    MEASURE(crc16_bitcombine2);
    MEASURE(crc16_bitcombine4);
    MEASURE(crc16_bitcombine8);
    MEASURE(crc16_bitcombine16);
    MEASURE(crc16_bitcombine32);
    MEASURE(crc16_by_duo);
    MEASURE(crc16_by1_duo);
    MEASURE(crc16_by2_duo);
    MEASURE(crc16_by4_duo);
    MEASURE(crc16_by8_duo);
    MEASURE(crc16_by_quartet);
    MEASURE(crc16_by1_quartet);
    MEASURE(crc16_by2_quartet);
    MEASURE(crc16_by4_quartet);
    MEASURE(crc16_by8_quartet);
    MEASURE(crc16_by1_octet);
    MEASURE(crc16_by2_octet);
    MEASURE(crc16_by4_octet);
    MEASURE(crc16_by8_octet);
    MEASURE(crc16_by16_octet);
    MEASURE(crc16_parallelstride16);

    return 0;
}
