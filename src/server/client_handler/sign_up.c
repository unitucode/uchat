#include "server.h"
#include "protocol.h"

bool mx_sign_up(t_dtp *login, t_client *client) {
    cJSON *login_struct = NULL;

    if (login->type != MX_SIGN_UP)
        return false;
    login_struct = cJSON_GetObjectItemCaseSensitive(login->json, "login");
    if (!mx_match_search(login_struct->valuestring, MX_LOGIN_REGEX))
        return false;
    login_struct = cJSON_GetObjectItemCaseSensitive(login->json, "pass");
    if (!mx_match_search(login_struct->valuestring, MX_HASH_REGEX))
        return false;
    printf("OKE, VALID SIGNUP\n");
    client++;
    return true;
}
