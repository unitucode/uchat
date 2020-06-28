#include "client.h"

t_chat *mx_init_chat(GSocketConnection *connection, int argc, char **argv) {
    t_chat *chat = mx_malloc(sizeof(t_chat));
    GOutputStream *out_s = g_io_stream_get_output_stream(G_IO_STREAM(connection));
    GDataOutputStream *out = g_data_output_stream_new(out_s);
    GInputStream *in_s = g_io_stream_get_input_stream(G_IO_STREAM(connection));
    GDataInputStream *in = g_data_input_stream_new(in_s);

    chat->builder = NULL;
    chat->conn = connection;
    chat->curr_room = NULL;
    chat->auth_token = NULL;
    chat->valid = true;
    chat->login = NULL;
    chat->out = out;
    chat->in = in;
    chat->builder = mx_init_window(argc, argv);
    chat->argc = argc;
    chat->argv = argv;
    chat->upl_old_msgs = false;
    chat->msg_placeholder = true;
    mx_init_handlers(chat);
    mx_init_errors(chat);
    g_data_input_stream_read_line_async(in, G_PRIORITY_DEFAULT, NULL, mx_receiver, chat);
    return chat;
}
