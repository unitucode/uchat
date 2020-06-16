#include "server.h"

gssize mx_send(GOutputStream *out, t_dtp *dtp) {
    GError *error = NULL;
    GBytes *bytes = g_bytes_new(&dtp->len, sizeof(int));
    gssize written = 0;
    gsize size = sizeof(int);
    gsize count = dtp->len - size;


    written = g_output_stream_write_bytes(out, bytes, NULL, &error);
    if (error)
        mx_logger(MX_LOG_FILE, LOGERR, "Write size error = %s\n", error->message);
    if (written < 0)
        mx_logger(MX_LOG_FILE, LOGERR, "Write error size bytes = -1\n");
    written = g_output_stream_write(out, dtp->data + written, count, NULL, &error);
    if (error)
        mx_logger(MX_LOG_FILE, LOGERR, "Write error = %s\n", error->message);
    if (written < 0)
        mx_logger(MX_LOG_FILE, LOGERR, "Write error bytes = -1\n");
    return written;
}
