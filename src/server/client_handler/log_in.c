#include "server.h"

static void correct_data(t_pdl *login, t_client *client) {
    char *token = "token"; // replace to get from db;
    t_pds *pds = mx_request_creation(-1, MX_TOKEN_AUTH, token);

    mx_send(client->ssl, pds);
    mx_logger(MX_LOG_FILE, LOGMSG, "Logged in: %s\n", login->data);
    mx_free_request_struct(&pds);
}

static void inccorect_data(t_client *client) {
    t_pds *pds = mx_request_creation(-1, MX_ERR_MSG,
                                     "The email or password inccorect");

    mx_send(client->ssl, pds);
    mx_free_request_struct(&pds);
}

static bool log_in(t_pdl *login, t_pdl *pass, t_client *client) {
    // t_pds *pds = NULL;

    if (strcmp(login->data, "admin\n")) { //replace to check db
        inccorect_data(client);
        mx_logger(MX_LOG_FILE, LOGMSG, "Inccorect login: %s\n", login->data);
        return false;
    }
    if (strcmp(pass->data, "admin\n")) { //repalce to check db
        inccorect_data(client);
        mx_logger(MX_LOG_FILE, LOGMSG, "Inccorect pass: %s\n", login->data);
        return false;
    }
    correct_data(login, client);
    return true;
}

bool mx_log_in(t_pdl *login, t_client *client) {
    t_pdl *pass = NULL;
    bool result = false;

    if (login && login->type != MX_LOGIN)
        return false;
    pass = mx_recv(client->ssl);
    if (pass && pass->type != MX_PASSWORD) {
        mx_free_decode_struct(&pass);
        mx_logger(MX_LOG_FILE, LOGWAR,
                  "First packet was login(%s), but second wasn`t pass\n",
                  login->data);
        return false;
    }
    result = log_in(login, pass, client);
    mx_free_decode_struct(&pass);
    return result;
}
