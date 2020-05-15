#include "server.h"

// static void send_to_all(t_list *list, t_chat *chat, t_client *cur_client, char *buf) {
    
//     mx_pthread_mutex_lock(&chat->mutex);
//     t_dtp *dtp = mx_request_creation(MX_MESSAGE, buf);
//     for (t_node *cur = list->head; cur; cur = cur->next) {
//         t_client *client = (t_client*)cur->data;
//         if (cur_client->socket_fd != client->socket_fd) {
//             mx_send(client->ssl, dtp);
//         }
//     }
//     mx_free_request_struct(&dtp);
//     mx_pthread_mutex_unlock(&chat->mutex);
// }

static void str_echo(t_client *client) {
    t_pdl *pdl = NULL;
    // system("leaks -q uchat_server");

    while ((pdl = mx_recv(client->ssl))) {
        if (!mx_authorization(client, pdl)) {
            mx_free_decode_struct(&pdl);
            break;
        }
        mx_free_decode_struct(&pdl);
    }
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

    pthread_detach(pthread_self());
    str_echo(client);
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
