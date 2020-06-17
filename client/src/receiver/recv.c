#include "client.h"

t_dtp *mx_recv(GInputStream *in) {
    GError *error = NULL;
    GBytes *bytes = NULL;
    gsize read = 0;
    gsize size = 0;

    bytes = g_input_stream_read_bytes(in, sizeof(int), NULL, &error);
    if (error)
        mx_logger(MX_LOG_FILE, LOGERR, "Read size error = %s\n", error->message);
    if (read < 0 || g_bytes_get_size(bytes) != sizeof(int))
        mx_logger(MX_LOG_FILE, LOGERR, "Read error size bytes = %ld\n", read);
    memcpy(&size, g_bytes_get_data(bytes, 0), sizeof(int));
    gchar buf[size + 1];

    read = g_input_stream_read(in, buf, size, NULL, &error);
    buf[read] = '\0';
    if (error)
        mx_logger(MX_LOG_FILE, LOGERR, "Read error = %s\n", error->message);
    if (read < 0 || read != size)
        mx_logger(MX_LOG_FILE, LOGERR, "Read error bytes = %ld\n", read);
    return mx_request_creation(buf);
}
