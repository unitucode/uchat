#include "api.h"
#include <glib/gstdio.h>

/*
 * Function: mx_change_working_dir
 * -------------------------------
 * Changes working directory to MX_SERVER
 */
void mx_change_working_dir(void) {
    #ifdef MX_SERVER
    if (g_chdir(MX_SERVER)) {
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_ERROR,
                  "No working directory mx_server");
    }
    if (g_mkdir_with_parents(MX_FILES_DIR, 0755)) {
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_ERROR,
                  "No files directory mx_files_dir");
    }
    #else
    mx_logger(MX_LOG_FILE, G_LOG_LEVEL_ERROR, "No working directory");
    #endif
    mx_daemon();
}

/*
 * Function: message_ready
 * -------------------------------
 * Callback for ready message from client
 * 
 * source_object: the object the asynchronous operation was started with
 * res: GAsyncResult
 * user_data: client that sent message
 */
static void message_ready(GObject *source_object, GAsyncResult *res,
                          gpointer user_data) {
    GDataInputStream *in = G_DATA_INPUT_STREAM(source_object);
    gsize count = 0;
    t_client *cli = (t_client*)user_data;

    if (!g_socket_connection_is_connected(cli->conn)
        || g_output_stream_is_closed(G_OUTPUT_STREAM(cli->out))
        || g_input_stream_is_closed(G_INPUT_STREAM(in))) {
        mx_deinit_client(&cli);
        return;
    }
    cli->msg = g_data_input_stream_read_line_finish(in, res, &count, NULL);
    if (!mx_handle_message(cli))
        return;
    g_data_input_stream_read_line_async(in, G_PRIORITY_DEFAULT, NULL,
                                        message_ready, cli);
}

/*
 * Function: incoming
 * -------------------------------
 * Callback for incoming connection
 * 
 * service: socket_service
 * conn: connection between server and client
 * souce_object: the source_object passed to g_socket_listener_add_address()
 * user_data: information about another users, database, handlers
 * 
 * returns: stop other handlers from being called
 */
static gboolean incoming(GSocketService *service, GSocketConnection *conn,
                         GObject *source_object, gpointer user_data) {
    GOutputStream *out_s = g_io_stream_get_output_stream(G_IO_STREAM(conn));
    GInputStream *in_s = g_io_stream_get_input_stream(G_IO_STREAM(conn));
    GDataOutputStream *out = g_data_output_stream_new(out_s);
    GDataInputStream *in = g_data_input_stream_new(in_s);
    t_client *gclient = mx_malloc(sizeof(t_client));

    gclient->out = out;
    gclient->info = (t_info*)user_data;
    gclient->conn = g_object_ref(conn);
    gclient->user = NULL;
    gclient->in = in;
    gclient->in_s = in_s;
    gclient->upload_file = FALSE;
    gclient->is_file = FALSE;
    g_data_input_stream_read_line_async(in, G_PRIORITY_DEFAULT, NULL,
                                        message_ready, gclient);
    (void)source_object;
    (void)service;
    return FALSE;
}

static gboolean is_valid_args(gint argc) {
    if (argc != 2) {
        g_printerr("Usage ./uchat_server <port>\n");
        return FALSE;
    }
    return TRUE;
}

gint main(gint argc, char **argv) {
    GSocketService *service = g_socket_service_new();
    GMainLoop *loop = NULL;
    t_info *info = NULL;
    gint64 port = -1;

    mx_change_working_dir();
    info = mx_init_info();
    if (!is_valid_args(argc))
        return -1;
    port = g_ascii_strtoll(argv[1], NULL, 10);
    if (!g_socket_listener_add_inet_port((GSocketListener*)service, port, 
                                         NULL, NULL)) {
        g_printerr("Invalid port\n");
        return -1;
    }
    g_signal_connect(service, "incoming", G_CALLBACK(incoming), info);
    g_socket_service_start (service);
    loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);
    return 0;
}

