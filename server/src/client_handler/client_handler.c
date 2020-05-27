#include "server.h"

// static void send_to_all(t_list *list, t_chat *chat, t_client *cur_client, char *buf) {

//     mx_pthread_mutex_lock(&chat->mutex);
//     t_dtp *dtp = mx_request_creation(buf);
//     for (t_node *cur = list->head; cur; cur = cur->next) {
//         t_client *client = (t_client*)cur->data;
//         if (cur_client->socket_fd != client->socket_fd) {
//             mx_send(client->ssl, dtp);
//         }
//     }
//     mx_free_request(&dtp);
//     mx_pthread_mutex_unlock(&chat->mutex);
// }

// static void receiver(t_client *client) {
//     t_dtp *dtp = NULL;
//     // system("leaks -q uchat_server");

//     while ((dtp = mx_recv(client->ssl))) {
//         if (!mx_authorization(client, dtp)) {
//             mx_free_request(&dtp);
//             mx_logger(MX_LOG_FILE, LOGERR, "invalid autorization packet\n");
//             break;
//         }
//         printf("recv = %s\n", dtp->str);
//         // send_to_all(client->chat->clients, client->chat, client, dtp->str);
//         mx_free_request(&dtp);
//     }
// }

void mx_disconnect_client(t_client *client) {
    mx_pthread_mutex_lock(&client->chat->mutex);
    mx_logger(MX_LOG_FILE, LOGMSG, "disconnected: IP[%s] port[%s]\n",
              client->ip, client->port);
    mx_delete_node(client->chat->clients, &client->node);
    mx_pthread_mutex_unlock(&client->chat->mutex);
}

void mx_connect_client(t_client *client) {
    mx_get_client_info(client);
    client->node = mx_push_front(client->chat->clients, client);
    mx_logger(MX_LOG_FILE, LOGMSG, "connected: IP[%s] port[%s]\n",
              client->ip, client->port);
    mx_pthread_create(&client->tid, NULL, mx_receiver, client);
}
