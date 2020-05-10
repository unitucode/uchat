#include "utils.h"

int mx_send(SSL *ssl, t_pds *data) {
    bool result = true;
    t_pds *pds = mx_request_creation(/*Room id*/1, MX_SIZE_MSG, data->len);

    if (!SSL_write(ssl, pds->data, strlen(pds->data))) {
        mx_logger(MX_LOG_FILE, LOGWAR, "SSL_write len failed\n");
        result = false;
    }
    mx_free_request_struct(&pds);
    if (!SSL_write(ssl, data->data, strlen(data->data))) {
        mx_logger(MX_LOG_FILE, LOGWAR, "SSL_write data failded\n");
        result = false;
    }
    return result;
}
