#include "server.h"

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

// static void func(gpointer data, gpointer user_data) {
//     GOutputStream *out = G_OUTPUT_STREAM(data);

//     g_print("sent %s\n", user_data);
//     g_output_stream_write(out, user_data, 2048, NULL, NULL);
// }

static gboolean incoming_callback(GSocketService *service, GSocketConnection *connection, GObject *source_object, gpointer user_data) {
    GInputStream *in = g_io_stream_get_input_stream(G_IO_STREAM(connection));
    GOutputStream *out = g_io_stream_get_output_stream(G_IO_STREAM(connection));
    t_info *info = (t_info*)user_data;

    info->users = g_list_append(info->users, out);
    while (g_socket_connection_is_connected(connection) && !g_output_stream_is_closed(out)) {
        t_dtp *dtp = mx_recv(in);
        if (dtp)
            g_print("data = %s\n", dtp->str);
        // g_list_foreach(info->users, func, );
    }
    info->users = g_list_remove(info->users, out);
    (void)info;
    (void)service;
    (void)source_object;
    return FALSE;
}

int main(int argc, char **argv) {
    // sqlite3 *database =  mx_server_data_open(MX_DB_USER);
    // mx_insert_room_into_db(database, "name_room", "admin");
    // char *string = cJSON_Print(mx_create_json_object(database, "vlad"));
    // char *string = cJSON_Print(mx_get_last_message(database, "chat_of_vlad", 1591449397, 100));
    // printf("%s\n", string);
    // mx_json();
    // t_dl_list *list = mx_parse_json(string);
    // t_room *room = (t_room*)list->front->data;
    // printf("room_customer -> %s\n", room->customer);
    // printf("Ok\n");
    // exit(1);
    // t_chat *chat = mx_init_chat(argc, argv);
    // t_client *client = NULL;
    // t_ssl_con *ssl = NULL;

    // mx_change_working_dir();
    // chat->database = mx_server_data_open(MX_DB_USER);
    // client = NULL;
    // ssl = mx_init_ssl(SERVER);
    // mx_create_table_users(chat->database);
    // mx_logger(MX_LOG_FILE, LOGMSG,"started server pid[%d]: %s %s\n", getpid(), argv[0], argv[1]);
    // while (1) {
    //     client = mx_new_client(chat->len);
    //     client->socket_fd = mx_accept(chat->listen_fd,
    //                                   client->cliaddr, &client->len);
    //     ssl->ssl = SSL_new(ssl->ctx);
    //     SSL_set_fd(ssl->ssl, client->socket_fd);
    //     if (SSL_accept(ssl->ssl) == -1)
    //         mx_elogger(MX_LOG_FILE, LOGERR, "ssl_accept\n");
    //     client->chat = chat;
    //     client->ssl = ssl->ssl;
    //     mx_connect_client(client);
    // }
    // mx_deinit_chat(&chat);
    GError *error = NULL;
    GSocketService *service = g_threaded_socket_service_new(-1);
    GMainLoop *loop = NULL;
    t_info *info = mx_malloc(sizeof(t_info));

    info->users = NULL;
    if (argc != 2) {
        g_printerr("Usage ./uchat_server <port>\n");
        return -1;
    }
    if (!g_socket_listener_add_inet_port((GSocketListener*)service, g_ascii_strtoll(argv[1], NULL, 10), NULL, &error)) {
        g_printerr("Invalid port\n");
        return -1;
    }
    g_signal_connect(service, "run", G_CALLBACK(incoming_callback), info);
    g_socket_service_start (service);
    loop = g_main_loop_new(NULL, FALSE);
    g_main_loop_run(loop);
    return 0;
}
