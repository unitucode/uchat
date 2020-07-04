#include "client.h"

void mx_send_auth_request(char *login, char *password,
                          t_chat *chat, t_request_type request_type) {
    char *pass;
    t_dtp *dtp = NULL;

    pass = g_compute_checksum_for_string(G_CHECKSUM_SHA256, password,
                                         strlen(password));
    if (request_type == RQ_LOG_IN)
        dtp = mx_log_in_request(login, pass);
    else
        dtp = mx_sign_up_request(login, pass);
    g_free(pass);
    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
}
