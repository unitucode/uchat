#include "client.h"

static void init_fields(t_chat *chat) {
    chat->curr_room = NULL;
    chat->auth_token = NULL;
    chat->valid = TRUE;
    chat->login = NULL;
    chat->builder = NULL;
    chat->upl_old_msgs = FALSE;
    chat->msg_placeholder = TRUE;
    chat->shift_hold = FALSE;
    chat->css_prov = NULL;
}

static void fill_chat(t_chat *chat, gint argc,
                      char **argv, GDataInputStream *in) {
    chat->argc = argc;
    chat->argv = argv;
    mx_init_handlers(chat);
    mx_init_errors(chat);
    g_data_input_stream_read_line_async(in, G_PRIORITY_DEFAULT, NULL,
                                        mx_receiver, chat);
    mx_css_connect_from_file(chat);
}

/*
 * Function: mx_init_chat
 * -------------------------------
 * Initializate chat information
 * 
 * connection: connection between server and client
 * argc: arguments count
 * argv: arguments array
 * 
 * returns: new chat information
 */
t_chat *mx_init_chat(GSocketConnection *connection, gint argc, char **argv) {
    t_chat *chat = mx_malloc(sizeof(t_chat));
    GOutputStream *out_s = g_io_stream_get_output_stream(
        G_IO_STREAM(connection));
    GDataOutputStream *out = g_data_output_stream_new(out_s);
    GInputStream *in_s = g_io_stream_get_input_stream(
        G_IO_STREAM(connection));
    GDataInputStream *in = g_data_input_stream_new(in_s);

    chat->conn = connection;
    chat->out = out;
    chat->in = in;
    init_fields(chat);
    #ifdef MX_UNIT_TEST
    chat->builder = NULL;
    #else
    chat->builder = mx_init_window(argc, argv);
    #endif
    fill_chat(chat, argc, argv, in);
    return chat;
}
