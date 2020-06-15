#include "utils.h"
#include "protocol.h"

/*
 * Send message by ssl
 */
int mx_send(SSL *ssl, t_dtp *dtp) {
    long int written = 0;
    char *data = dtp->data;
    long int bytes = MX_RQ_SIZE;
    long int len = dtp->len;
    char response[strlen(MX_RES_OK) + 1];

    bzero(response, sizeof(response));
    if (SSL_write(ssl, data + written, sizeof(int)) <= 0) {
        mx_logger(MX_LOG_FILE, LOGWAR, "SSL_write data failed\n");
        return false;
    }
    if (SSL_read(ssl, response, sizeof(response) - 1) <= 0 || strcmp(response, MX_RES_OK)) {
        mx_logger(MX_LOG_FILE, LOGWAR, "Response size data failed\n");
        return false;
    }
    written += sizeof(int);
    while (written < len) {
        if (len - written < MX_RQ_SIZE)
            bytes = len - written;
        if (SSL_write(ssl, data + written, bytes) <= 0) {
            mx_logger(MX_LOG_FILE, LOGWAR, "SSL_write data failed\n");
            return false;
        }
        if (SSL_read(ssl, response, sizeof(response) - 1) <= 0 || strcmp(response, MX_RES_OK)) {
            mx_logger(MX_LOG_FILE, LOGWAR, "Response main data failed\n");
            return false;
        }
        fprintf(stderr, "written = %s\n", data + written);
        written += bytes;
    }
    return true;
}
