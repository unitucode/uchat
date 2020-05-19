#include "server.h"

bool mx_log_in(t_dtp *login, t_client *client) {
    char md5_pass[MX_MD5_BUF_SIZE + 1];
    char *login_str;
    char *pass_str;

    if (!mx_valid_authorization_data(login, &login_str, &pass_str))
        return false;
    return true;
}
