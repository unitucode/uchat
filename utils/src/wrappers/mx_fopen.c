#include "utils.h"

/*
 * Wrapper of standart function fopen
 */
FILE *mx_fopen(const char * restrict path, const char * restrict mode) {
    FILE *result = fopen(path, mode);

    if (result == NULL)
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_WARNING, "fopen");
    return result;
}
