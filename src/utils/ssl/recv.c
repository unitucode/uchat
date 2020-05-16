#include "utils.h"
#include "protocol.h"

/*
 * Receive first packet with size of next packet
 */
static int message_size(SSL *ssl) {
    char buf[4];
    size_t bytes = 0;
    int size = -1;

    bytes = SSL_read(ssl, buf, sizeof(buf));
    if (bytes != 4) {
        mx_logger(MX_LOG_FILE, LOGWAR, "Invalid packet\n");
        return -1;
    }
    memcpy(&size, buf, 4);
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
        char buf[size];

        buf[size] = '\0';
        if ((bytes = SSL_read(ssl, buf, sizeof(buf))) == size)
            dtp = mx_request_creation(buf);
        else
            mx_logger(MX_LOG_FILE, LOGWAR, "mx_recv\n");
    }
    return dtp;
}
