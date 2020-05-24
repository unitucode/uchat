#include "server.h"
#include <sqlite3.h>

int callback(void *message, int argc, char** argv, char **data_parametr) {
    for (int i = 0; i < argc; i++) {
        printf("%s -> %s\n", data_parametr[i], argv[i]);
        if (strcmp("MESSAGE", data_parametr[i]) == 0 && argv[i] != NULL) {
            message = strdup(argv[i]);
        }
    }
    printf("Ok\n");
    return 0;
}

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

int main(int argc, char **argv) {
    // mx_test_room();
    // mx_test_users();
    // mx_test_message();
    // mx_test_member();
    // exit(1);
    t_chat *chat = mx_init_chat(argc, argv);
    t_client *client = NULL;
    t_ssl_con *ssl = NULL;

    mx_change_working_dir();
    chat->database = mx_server_data_open(MX_DB_USER);
    client = NULL;
    ssl = mx_init_ssl(SERVER);
    mx_create_table(chat->database, MX_USERS_TABLE);
    mx_logger(MX_LOG_FILE, LOGMSG,"started server pid[%d]: %s %s\n", getpid(), argv[0], argv[1]);
    while (1) {
        client = mx_new_client(chat->len);
        client->socket_fd = mx_accept(chat->listen_fd,
                                      client->cliaddr, &client->len);
        ssl->ssl = SSL_new(ssl->ctx);
        SSL_set_fd(ssl->ssl, client->socket_fd);
        if (SSL_accept(ssl->ssl) == -1)
            mx_elogger(MX_LOG_FILE, LOGERR, "ssl_accept\n");
        client->chat = chat;
        client->ssl = ssl->ssl;
        mx_connect_client(client);
    }
    mx_deinit_chat(&chat);
}
