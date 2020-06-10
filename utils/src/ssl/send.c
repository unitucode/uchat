#include "utils.h"
#include "protocol.h"

/*
 * Send message by ssl
 */
int mx_send(SSL *ssl, t_dtp *dtp) {
    // bool result = true;

    // if (!SSL_write(ssl, dtp->data, dtp->len)) {
    //     mx_logger(MX_LOG_FILE, LOGWAR, "SSL_write data failed\n");
    //     result = false;
    // }
    // return result;
    bool result = true;
    ssize_t len = dtp->len;
    char *data = dtp->data;
    int sended_bytes = 0;

    while (len > 0) {
        if (!(sended_bytes = SSL_write(ssl, data, MX_RQ_SIZE))) {
            mx_logger(MX_LOG_FILE, LOGWAR, "SSL_write data failed\n");
            result = false;
            break;
        }
        fprintf(stderr, "len = %zu, sended_bytes = %d\n", len, sended_bytes);
        data += sended_bytes;
        len -= sended_bytes;
        fprintf(stderr, "SENDED %d len = %zu\n", sended_bytes, dtp->len);
    }
    return result;
}
