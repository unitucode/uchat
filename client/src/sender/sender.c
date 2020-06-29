#include "client.h"

gssize mx_send(GDataOutputStream *out, t_dtp *dtp) {
    GError *error = NULL;
    gsize size = 0;

    if (!g_data_output_stream_put_string(out, dtp->str, NULL, &error)) {
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_WARNING, "Write string error");
    }
    if (error) {
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_WARNING, "Error send");
        g_clear_error(&error);
    }
    return size;
}
