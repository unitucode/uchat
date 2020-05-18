#include "protocol.h"

t_dtp *mx_log_in_request(char *login, char *pass) {
    t_dtp *dtp = mx_request_json("{\"type\": %d, \"login\": \"%s\", \"pass\": \
    \"%s\"}", MX_LOG_IN, login, pass);

    return dtp;
}

t_dtp *mx_sign_up_request(char *login, char *pass) {
    t_dtp *dtp = mx_request_json("{\"type\": %d, \"login\": \"%s\", \"pass\": \
    \"%s\"}", MX_SIGN_UP, login, pass);

    return dtp;
}

t_dtp *mx_log_in_token_request(char *token) {
    t_dtp *dtp = mx_request_json("{\"type\": %d, \"token\": \"%s\"}",
                                 MX_TOKEN, token);

    return dtp;
}
