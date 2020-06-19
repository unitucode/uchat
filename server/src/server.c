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
    if (!mx_handle_request(cli->msg, cli)) {
        g_free(cli->msg);
        return;
    }
    g_free(cli->msg);
    g_data_input_stream_read_line_async(in, G_PRIORITY_DEFAULT, NULL, message_ready, cli);
}

static gboolean incoming_callback (GSocketService *service, GSocketConnection *connection, GObject *source_object, gpointer user_data) {
    g_print("connected!");
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
    gclient->in = g_object_ref(in);
    gclient->in_s = g_object_ref(in_stream);
    g_data_input_stream_read_line_async(in, G_PRIORITY_DEFAULT, NULL, message_ready, gclient);
    (void)source_object;
    (void)service;
    return FALSE;
}

int main(int argc, char **argv) {
    GError *error = NULL;
    GSocketService *service = g_socket_service_new();
    GMainLoop *loop = NULL;
    t_info *info = NULL;

    mx_change_working_dir();
    info = mx_init_info();
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

void test() {
    sqlite3 *db = mx_open_db(MX_DB);
    
    // t_db_room *room = malloc(sizeof(t_db_room));
    // room->customer = "customer";
    // room->desc = NULL;
    // room->room_name = "name";
    // room->type = GLOBAL_CHAT;
    // for (int i = 0; i < 100; i++)
    //     mx_insert_room_into_db(db, room);
    // mx_free_room(&room);
    
    // t_db_user *user = malloc(sizeof(t_db_user));
    // user->desc = "desc";
    // user->login = "login5";
    // user->name = "name5";
    // user->pass = "pass";
    // user->token = "token";
    // mx_insert_user_into_db(db, user);

    // for (int i = 2; i < 20; i++)
        // mx_insert_member_into_db(db, 1, 1, SIMPLE);

    // t_db_message *message = malloc(sizeof(t_db_message));
    // message->user_id = 1;
    // message->room_id = 1;
    // message->message = "hello";
    // message->name_file = NULL;
    // message->size = 0;
    // message->type = TEXT_MSG;
    // for (int i = 0; i < 1000; i++) {
    //     mx_insert_message(db, message);
    // }

    mx_get_user_by_login(db, "login1");

    // cJSON *json = mx_get_rooms(db, 0, 1);
    // gchar *string = cJSON_Print(json); 
    // printf("%s\n", string);

    // cJSON *json1 = mx_get_users(db, 0);
    // gchar *string1 = cJSON_Print(json1);
    // printf("%s\n", string1);

    mx_close_database(db);
    printf("Ok\n");
    system("leaks -q uchat_server");
    exit(1);
}

