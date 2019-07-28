#include "defs.h"
#include <stdlib.h>
#include <stdbool.h>

const void *
make_sample_data(size_t *size)
{
    if (*size > (100 << 20)) {
        *size = 100 << 20;
    }

    char *p = (char *)malloc(*size);

    if (p == NULL) {
        *size = 0;
        return NULL;
    }

    char *px = p;
    for (size_t i = *size; i > 0; i --, px ++) {
        *px = random();
    }

    return p;
}
