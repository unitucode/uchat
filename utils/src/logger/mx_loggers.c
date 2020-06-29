#include "utils.h"

/*
 * Logs string to file
 */
void mx_logger(gchar *file_name, GLogLevelFlags flags, gchar *error) {
    GLogField logfield;

    file_name++;
    if (error == NULL)
        return;
    logfield.key = "MESSAGE";
    logfield.value = (gpointer)error;
    logfield.length = strlen(error);
    g_log_writer_default(flags, &logfield, 1, "hi");
}
