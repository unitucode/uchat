#include "client.h"

gssize mx_send(GDataOutputStream *out, t_dtp *dtp) {
    GError *error = NULL;
    gsize size = 0;

    if (!g_data_output_stream_put_string(out, dtp->str, NULL, &error)) {
        mx_logger(MX_LOG_FILE, LOGERR, "Write string error\n");
    }
    if (error) {
        mx_logger(MX_LOG_FILE, LOGERR, "Error = %s\n", error->message);
        g_clear_error(&error);
    }
    return size;
}
