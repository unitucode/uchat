#include "utils.h"

/*
 * Wrapper of standart function fopen
 */
FILE *mx_fopen(const char * restrict path, const char * restrict mode) {
    FILE *result = fopen(path, mode);

    if (result == NULL)
        mx_elogger(MX_LOG_FILE, LOGERR, "fopen\n");
    return result;
}
