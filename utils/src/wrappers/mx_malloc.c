#include "utils.h"

/*
 * Wrapper of standart function malloc
 */
void *mx_malloc(size_t size) {
    void *data = malloc(size);

    if (!data)
        mx_elogger(MX_LOG_FILE, LOGERR, "malloc\n");
    return data;
}
