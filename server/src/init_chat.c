#include "server.h"

/*
 * Initializates chat variables
 */
t_chat *mx_init_chat(int argc, char **argv) {
    t_chat *chat = mx_malloc(sizeof(t_chat));

    if (argc == 2)
        chat->listen_fd = mx_tcp_listen(argv[1], &chat->len);
    else
        mx_elogger(NULL, LOGMSG, "usage: ./chat_server <port>\n");
    chat->clients = mx_new_dl_list(mx_delete_client);
    chat->online_users = 0;
    mx_init_receiver(chat);
    mx_pthread_mutex_init(&chat->mutex, NULL);
    srand(time(NULL));
    return chat;
}

/*
 * Deinitializates chat variables
 */
void mx_deinit_chat(t_chat **chat) {
    // mx_delete_list(&(*chat)->clients);
    mx_pthread_mutex_destroy(&(*chat)->mutex);
    mx_close_database((*chat)->database);
    free(*chat);
    *chat = NULL;
}
