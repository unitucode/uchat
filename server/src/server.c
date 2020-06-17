#include "server.h"
#include "sqlite3.h"

void mx_change_working_dir(void) {
    #ifdef MX_SERVER
    if (chdir(MX_SERVER)) {
        mx_elogger(NULL, LOGERR,
                   "No working directory %s\n", MX_SERVER);
    }
    #else
    mx_elogger(NULL, LOGERR, "No working directory");
    #endif
}

static void message_ready(GObject *source_object, GAsyncResult *res, gpointer user_data) {
    GDataInputStream *in = G_DATA_INPUT_STREAM(source_object);
    GError *error = NULL;
    gsize count = 0;
    t_client *cli = (t_client*)user_data;

    if (!g_socket_connection_is_connected(cli->conn)
        || g_output_stream_is_closed(G_OUTPUT_STREAM(cli->out))
        || g_input_stream_is_closed(G_INPUT_STREAM(in))) {
        cli->info->users = g_list_remove(cli->info->users, cli->out);
        return;
    }
    cli->msg = g_data_input_stream_read_line_finish(in, res, &count, &error);
    if (!cli->msg)
        return;
    if (error) {
        g_error ("%s\n", error->message);
        g_clear_error (&error);
    }
    g_message("received = %s\n", cli->msg);
    g_message("sent = %d\n", g_data_output_stream_put_string(cli->out, "hello\n", NULL, NULL));
    g_free(cli->msg);
    g_data_input_stream_read_line_async(in, G_PRIORITY_DEFAULT, NULL, message_ready, cli);
}

static gboolean incoming_callback (GSocketService *service, GSocketConnection *connection, GObject *source_object, gpointer user_data) {
    GOutputStream *out_stream = g_io_stream_get_output_stream(G_IO_STREAM(connection));
    GInputStream *in_stream = g_io_stream_get_input_stream(G_IO_STREAM(connection));
    GDataOutputStream *out = g_data_output_stream_new(out_stream);
    GDataInputStream *in = g_data_input_stream_new(in_stream);
    t_client *gclient = mx_malloc(sizeof(t_client));

    gclient->out = g_object_ref(out);
    gclient->info = (t_info*)user_data;
    gclient->info->users = g_list_append(gclient->info->users, out);
    gclient->conn = g_object_ref(connection);
    gclient->user = NULL;
    g_data_input_stream_read_line_async(in, G_PRIORITY_DEFAULT, NULL, message_ready, gclient);
    (void)source_object;
    (void)service;
    return FALSE;
}

int main(int argc, char **argv) {
    GError *error = NULL;
    GSocketService *service = g_socket_service_new();
    GMainLoop *loop = NULL;
    t_info *info = mx_init_info();

    mx_change_working_dir();
    info->users = NULL;
    if (argc != 2) {
        g_printerr("Usage ./uchat_server <port>\n");
        return -1;
    }
    if (!g_socket_listener_add_inet_port((GSocketListener*)service, g_ascii_strtoll(argv[1], NULL, 10), NULL, &error)) {
        g_printerr("Invalid port\n");
        return -1;
    }
    g_signal_connect(service, "incoming", G_CALLBACK(incoming_callback), info);
    g_socket_service_start (service);
    loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);
    return 0;
}
