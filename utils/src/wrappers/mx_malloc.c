#include "utils.h"

/*
 * Wrapper of standart function malloc
 */
void *mx_malloc(size_t size) {
    void *data = malloc(size);

    if (!data)
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_WARNING, "malloc");
    return data;
}
