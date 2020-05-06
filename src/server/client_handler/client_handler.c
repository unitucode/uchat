#include "server.h"

static void test(t_chat *chat) {
    pthread_mutex_lock(&chat->mutex);
    pthread_mutex_unlock(&chat->mutex);
}

static void str_echo(int sockfd, t_list *list, t_client *cur_client, t_chat *chat) {
    ssize_t n;
    char buf[1024];

    if (cur_client->socket_fd == 5) {
        test(chat);
    }
again:
    while ((n = read(sockfd, buf, 1024)) > 0) {
        for (t_node *cur = list->head; cur; cur = cur->next) {
            t_client *client = (t_client*)cur->data;
            if (cur_client->socket_fd != client->socket_fd)
                dprintf(client->socket_fd, "user:[%s]: %s", cur_client->ip, buf);
        }
    }
    
    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        exit(1);

}

void *client_handler(void *arg) {
    t_chat *chat = (t_chat*)arg;
    t_list *list = (t_list*)chat->clients;
    t_client *client = chat->current_client;
    mx_logger(MX_LOG_FILE, LOGMSG, "connected: IP[%s] port[%s]\n", client->ip, client->port);
    pthread_detach(pthread_self());
    str_echo(client->socket_fd, list, client, chat);
    mx_delete_client_list(chat->clients, client);
    system("leaks -q chat_server");
    return NULL;
}
