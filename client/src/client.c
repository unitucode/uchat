#include "client.h"

static void change_working_dir(void) {
    #ifdef MX_CLIENT
    if (chdir(MX_CLIENT)) {
        mx_elogger(NULL, LOGERR,
                   "No working directory %s\n", MX_CLIENT);
    }
    #else
    mx_elogger(NULL, LOGERR, "No working directory");
    #endif
}


int main(int argc, char **argv) {
    GError * error = NULL;
    argv++;
    argc++;
    GSocketConnection * connection = NULL;
    GSocketClient * client = g_socket_client_new();

    change_working_dir();
    connection = g_socket_client_connect_to_host (client,
                                                (gchar*)"localhost",
                                                    8888,
                                                    NULL,
                                                    &error);

    GOutputStream *ostream = g_io_stream_get_output_stream(G_IO_STREAM(connection));
    while (1) {
        t_dtp *dtp = mx_sign_up_request("hello", "bye");
        gchar *str = g_strjoin("", dtp->str, "\n", NULL);
        g_print("str = %s\n", str);
        GDataOutputStream *out = g_data_output_stream_new(ostream);

        g_print("sent = %d\n", g_data_output_stream_put_string(out, str, NULL, NULL));
        g_free(str);
        g_usleep(1000000);
    }
    /* don't forget to check for errors */
    return 0;
}
