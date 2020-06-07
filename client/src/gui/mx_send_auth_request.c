#include "client.h"

void mx_send_auth_request(char *login, char *password,
                          SSL *ssl, t_request_type request_type) {
    char pass[33]; 
    t_dtp *dtp = NULL;

    pass[32] = '\0';
    mx_md5(pass, (const unsigned char*)password, strlen(password));
    if (request_type == RQ_LOG_IN)
        dtp = mx_log_in_request(login, pass);
    else
        dtp = mx_sign_up_request(login, pass);
    mx_send(ssl, dtp);
    mx_free_request(&dtp);
}
