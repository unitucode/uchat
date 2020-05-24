#include "utils.h"

/*
 * Wrapper of standart function fclose
 */
int mx_fclose(FILE *stream) {
    int result = fclose(stream);

    if (result == EOF)
        mx_elogger(MX_LOG_FILE, LOGERR, "fclose\n");
    return result;
}
