#include "client.h"

/*
 * Function: mx_send
 * -------------------------------
 * Sends request to server
 * 
 * out: output stream to server
 * dtp: reqeust that need to send
 * 
 * returns: count of sent bytes
 */
gssize mx_send(GDataOutputStream *out, t_dtp *dtp) {
    GError *error = NULL;
    gsize size = 0;

    if (dtp) {
        if ((size = g_data_output_stream_put_string(out, dtp->str,
                                                    NULL, &error)) <= 0) {
            mx_logger(MX_LOG_FILE, G_LOG_LEVEL_WARNING, "Write string error");
        }
        if (error) {
            mx_logger(MX_LOG_FILE, G_LOG_LEVEL_WARNING, "Error send");
            g_clear_error(&error);
        }
    }
    return size;
}
