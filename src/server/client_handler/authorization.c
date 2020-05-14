#include "server.h"

bool mx_authorization(t_client *client, t_pdl *data) {
    return client->user
           || mx_log_in(data, client)
           || mx_sign_up(data, client)
           || mx_log_in_token(data, client);
}
