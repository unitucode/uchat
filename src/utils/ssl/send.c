#include "utils.h"
#include "protocol.h"

/*
 * Send message by ssl
 */
int mx_send(SSL *ssl, t_dtp *dtp) {
    bool result = true;

    if (!SSL_write(ssl, dtp->data, strlen(dtp->data))) {
        mx_logger(MX_LOG_FILE, LOGWAR, "SSL_write data failed\n");
        result = false;
    }
    return result;
}
