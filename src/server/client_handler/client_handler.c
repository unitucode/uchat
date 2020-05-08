#include "server.h"

static void send_to_all(t_list *list, t_chat *chat, t_client *cur_client, char *buf) {
    mx_pthread_mutex_lock(&chat->mutex);
    for (t_node *cur = list->head; cur; cur = cur->next) {
        t_client *client = (t_client*)cur->data;
        if (cur_client->socket_fd != client->socket_fd) {
            SSL_write(client->ssl, buf, strlen(buf));
        }
    }
    mx_pthread_mutex_unlock(&chat->mutex);
}

static void str_echo(int sockfd, t_list *list, t_client *cur_client, t_chat *chat) {
    ssize_t n;
    char buf[1024];
    sockfd++;

    bzero(buf, sizeof(buf));
again:
    while ((n = SSL_read(cur_client->ssl, buf, sizeof(buf))) > 0) {
        send_to_all(list, chat, cur_client, buf);
        bzero(buf, sizeof(buf));
    }
    
    if (n < 0 && errno == EINTR)
        goto again;
    else if (n < 0)
        exit(1);

}

static void mx_disconnect_client(t_client *client) {
    mx_pthread_mutex_lock(&client->chat->mutex);
    mx_logger(MX_LOG_FILE, LOGMSG, "disconnected: IP[%s] port[%s]\n",
              client->ip, client->port);
    mx_delete_client_list(client->chat->clients, client);
    mx_pthread_mutex_unlock(&client->chat->mutex);
}

static void *client_handler(void *arg) {
    t_client *client = (t_client*)arg;
    t_chat *chat = (t_chat*)client->chat;
    t_list *list = (t_list*)chat->clients;

    pthread_detach(pthread_self());
    str_echo(client->socket_fd, list, client, chat);
    mx_disconnect_client(client);
    return NULL;
}

void mx_connect_client(t_client *client) {
    mx_get_client_info(client);
    mx_push_node(client->chat->clients, client, MX_LIST_BACK);
    mx_logger(MX_LOG_FILE, LOGMSG, "connected: IP[%s] port[%s]\n",
              client->ip, client->port);
    mx_pthread_create(&client->tid, NULL, &client_handler, client);
}
