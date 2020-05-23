#include "protocol.h"

/*
 * Receive first packet with size of next packet
 */
static int message_size(SSL *ssl) {
    char buf[sizeof(int)];
    int bytes = 0;
    int size = -1;

    bytes = SSL_read(ssl, buf, sizeof(buf));
    if (bytes != sizeof(int)) {
        mx_logger(MX_LOG_FILE, LOGWAR, "Invalid packet\n");
        return -1;
    }
    memcpy(&size, buf, sizeof(int));
    return size;
}

/*
 * Receive message from ssl socket
 */
t_dtp *mx_recv(SSL *ssl) {
    t_dtp *dtp = NULL;
    int size = 0;
    int bytes = 0;

    if ((size = message_size(ssl)) > 0) {
        char buf[size + 1];

        if ((bytes = SSL_read(ssl, buf, size)) == size) {
            buf[bytes] = '\0';
            dtp = mx_request_creation(buf);
        }
        else
            mx_logger(MX_LOG_FILE, LOGWAR, "mx_recv\n");
    }
    return dtp;
}
