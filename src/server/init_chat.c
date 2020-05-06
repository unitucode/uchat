#include "server.h"

t_chat *mx_init_chat(int argc, char **argv) {
    t_chat *chat = mx_malloc(sizeof(t_chat));

    if (argc == 2)
        chat->listen_fd = mx_tcp_listen(argv[1], &chat->len);
    else
        mx_elogger(NULL, LOGMSG, "usage: ./chat_server <port>\n");
    chat->clients = mx_new_list();
    mx_pthread_mutex_init(&chat->mutex, NULL);
    return chat;
}

void mx_deinit_chat(t_chat **chat) {
    mx_delete_list(&(*chat)->clients);
    mx_pthread_mutex_destroy(&(*chat)->mutex);
    free(*chat);
    *chat = NULL;
}
