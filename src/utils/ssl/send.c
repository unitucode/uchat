#include "utils.h"

/*
 * Send message by ssl
 */
int mx_send(SSL *ssl, t_dtp *data) {
    bool result = true;
    t_dtp *dtp = mx_request_creation(data->len);

    if (!SSL_write(ssl, dtp->data, strlen(dtp->data))) {
        mx_logger(MX_LOG_FILE, LOGWAR, "SSL_write len failed\n");
        result = false;
    }
    mx_free_request_struct(&dtp);
    if (!SSL_write(ssl, data->data, strlen(data->data))) {
        mx_logger(MX_LOG_FILE, LOGWAR, "SSL_write data failded\n");
        result = false;
    }
    return result;
}
