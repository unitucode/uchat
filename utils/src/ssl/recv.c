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
    long int readed_bytes = 0;

    if ((size = message_size(ssl)) > 0) {
        char data[size + 1];
        char buf[MX_RQ_SIZE + 1];

        bzero(data, sizeof(data));
        bzero(buf, sizeof(buf));
        while (SSL_read(ssl, buf, MX_RQ_SIZE) > 0) {
            readed_bytes += strlen(buf);
            if (readed_bytes <= size)
                strcat(data, buf);
            if (readed_bytes == size)
                break;
        }
        if (strlen(data) == (unsigned int)size)
            dtp = mx_request_creation(data);
    }
    return dtp;
}
