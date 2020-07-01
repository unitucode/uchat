#include "utils.h"

/*
 * Wrapper of standart function fclose
 */
gint mx_fclose(FILE *stream) {
    gint result = fclose(stream);

    if (result == EOF)
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_WARNING, "fclose");
    return result;
}
