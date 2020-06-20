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
        g_hash_table_remove(cli->info->users, cli->out);
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
    GOutputStream *out_stream = g_io_stream_get_output_stream(G_IO_STREAM(connection));
    GInputStream *in_stream = g_io_stream_get_input_stream(G_IO_STREAM(connection));
    GDataOutputStream *out = g_data_output_stream_new(out_stream);
    GDataInputStream *in = g_data_input_stream_new(in_stream);
    t_client *gclient = mx_malloc(sizeof(t_client));

    gclient->out = g_object_ref(out);
    gclient->info = (t_info*)user_data;
    gclient->conn = g_object_ref(connection);
    gclient->user = NULL;
    gclient->in = g_object_ref(in);
    gclient->in_s = g_object_ref(in_stream);
    g_data_input_stream_read_line_async(in, G_PRIORITY_DEFAULT, NULL, message_ready, gclient);
    (void)source_object;
    (void)service;
    return FALSE;
}

void test();

int main(int argc, char **argv) {
    // test();
    GError *error = NULL;
    GSocketService *service = g_socket_service_new();
    GMainLoop *loop = NULL;
    t_info *info = NULL;

    mx_change_working_dir();
    info = mx_init_info();
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

    // if (mx_check_user_by_login(db, "login5"))
    //     printf("true\n");
    // else
    //     printf("false\n");

    // mx_insert_contact(db, 1, 2, DB_BLACKLIST);
    // mx_delete_contact(db, 1, 2);

    // for (int i = 0; i < 10; i++)
    //     mx_db_push_queue_by_id(db, 6, "request1");
    // mx_db_pop_queue_by_id(db, 6);
    // printf("%s\n", mx_get_queue(db, 6));

    t_db_room *room = malloc(sizeof(t_db_room));
    room->customer_id = 1;
    room->desc = "";
    room->room_name = "name";
    room->type = DB_GLOBAL_CHAT;
    for (int i = 0; i < 10; i++)
        mx_insert_room_into_db(db, room);
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
    // message->file_name = NULL;
    // message->file_size = 0;
    // message->type = DB_TEXT_MSG;
    // for (int i = 0; i < 1000; i++) {
    //     mx_insert_message(db, message);
    // }

    // cJSON *json_om = mx_get_old_messages_by_id(db, 1, 1592614114621, 5);
    // char *str_om = cJSON_Print(json_om);
    // printf("%s\n", str_om);

    // cJSON *json_nm = mx_get_new_messages_by_id(db, 1, 1592614114541, 5);
    // char *str_nm = cJSON_Print(json_nm);
    // printf("%s\n", str_nm);

    // cJSON *json_cm = mx_get_curr_messages_by_id(db, 1, 5);
    // char *str_cm = cJSON_Print(json_cm);
    // printf("%s\n", str_cm);

    // mx_get_user_by_login(db, "login1");

    // cJSON *json_1 = cJSON_CreateObject();
    // cJSON_AddStringToObject(json_1, "name", "my first and last name");
    // cJSON_AddStringToObject(json_1, "pass", "password");
    // cJSON_AddStringToObject(json_1, "login", "login13");
    // cJSON_AddStringToObject(json_1, "token", "token144");
    // cJSON_AddStringToObject(json_1, "desc", "desc553");
    // t_db_user *user = mx_parse_json_user(json_1);
    // if (user) {
    //     printf("name \t->)-<>-(-> %s\n", user->name);
    //     printf("login\t->)-<>-(-> %s\n", user->login);
    //     printf("desc \t->)-<>-(-> %s\n", user->desc);
    //     printf("pass \t->)-<>-(-> %s\n", user->pass);
    //     printf("token\t->)-<>-(-> %s\n", user->token);
    //     mx_insert_user_into_db(db, user);
    // }

    // cJSON *message_j = cJSON_CreateObject();
    // cJSON_AddNumberToObject(message_j, "room_id", 1);
    // cJSON_AddNumberToObject(message_j, "user_id", 1);
    // cJSON_AddNumberToObject(message_j, "type", DB_FILE_MSG);
    // cJSON_AddNumberToObject(message_j, "file_size", 0);
    // cJSON_AddStringToObject(message_j, "message", "");
    // cJSON_AddStringToObject(message_j, "file_name", "name_file");
    // t_db_message *message = mx_parse_message(message_j);
    // if (message) {
    //     printf("parse Ok !\n");
    //     printf("file_size\t->)-<>-(-> %s\n", message->file_name);
    //     printf("file_size\t->)-<>-(-> %llu\n", message->file_size);
    //     printf("message  \t->)-<>-(-> %s\n", message->message);
    //     printf("room_id  \t->)-<>-(-> %llu\n", message->room_id);
    //     printf("user_id  \t->)-<>-(-> %llu\n", message->user_id);
    //     printf("type     \t->)-<>-(-> %d\n", message->type);
    //     mx_insert_message(db, message);
    // }

    // cJSON *room_j = cJSON_CreateObject();
    // cJSON_AddStringToObject(room_j, "name", "room_name");
    // cJSON_AddStringToObject(room_j, "desc", "");
    // cJSON_AddNumberToObject(room_j, "customer_id", 1);
    // cJSON_AddNumberToObject(room_j, "type", DB_PRIVAT_CHAT);
    // t_db_room *room = mx_parse_json_room(room_j);
    // if (room) {
    //     printf("create !\n");
    //     printf("name        \t->)-<>-(-> %s\n", room->room_name);
    //     printf("desc        \t->)-<>-(-> %s\n", room->desc);
    //     printf("customer_id \t->)-<>-(-> %llu\n", room->customer_id);
    //     printf("type        \t->)-<>-(-> %d\n", room->type);
    //     mx_insert_room_into_db(db, room);
    // }

    // cJSON *json0 = mx_search_room(db, "n");
    // gchar *string0 = cJSON_Print(json0);
    // printf("%s\n", string0);

    // printf("%llu\n", mx_get_time(DB_SECOND));
    // printf("%llu\n", mx_get_time(DB_MILISECOND));
    // printf("%llu\n", mx_get_time(DB_MICROSECOND));

    // cJSON *json = mx_get_rooms(db, 0, 1);
    // gchar *string = cJSON_Print(json); 
    // printf("%s\n", string);

    // cJSON *json1 = mx_get_users(db, 0);
    // gchar *string1 = cJSON_Print(json1);
    // printf("%s\n", string1);

    mx_close_db(db);
    printf("Ok\n");
    // system("leaks -q uchat_server");
    exit(1);
}

