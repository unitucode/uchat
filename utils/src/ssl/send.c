#include "utils.h"
#include "protocol.h"

/*
 * Send message by ssl
 */
int mx_send(SSL *ssl, t_dtp *dtp) {
    bool result = true;

    if (!SSL_write(ssl, dtp->data, dtp->len)) {
        mx_logger(MX_LOG_FILE, LOGWAR, "SSL_write data failed\n");
        result = false;
    }
    return result;
    // bool result = true;
    // long int len = dtp->len;
    // char *data = dtp->data;

    // printf("size = %zu data = %s\n", dtp->len - 4, dtp->str);
    // while (len > 0) {
    //     if (!(SSL_write(ssl, data, MX_RQ_SIZE))) {
    //         mx_logger(MX_LOG_FILE, LOGWAR, "SSL_write data failed\n");
    //         result = false;
    //         break;
    //     }
    //     data += MX_RQ_SIZE;
    //     len -= MX_RQ_SIZE;
    // }
    // return result;
}
