#include "utils.h"

void *mx_memdup(const void *mem, size_t size) {
    void *res = mx_malloc(size);

    memcpy(res, mem, size);
    return res;
}
