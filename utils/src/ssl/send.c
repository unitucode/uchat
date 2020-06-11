#include "utils.h"
#include "protocol.h"

/*
 * Send message by ssl
 */
int mx_send(SSL *ssl, t_dtp *dtp) {
    long int len = dtp->len;
    char *data = dtp->data;

    while (len > 0) {
        if (!SSL_write(ssl, data, MX_RQ_SIZE)) {
            mx_logger(MX_LOG_FILE, LOGWAR, "SSL_write data failed\n");
            return false;
        }
        data += MX_RQ_SIZE;
        len -= MX_RQ_SIZE;
    }
    return true;
}
