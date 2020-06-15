#include "client.h"

static gboolean reconnect_on(t_chat *chat) {
    puts("reconnect on");
    chat++;
    return G_SOURCE_REMOVE;
}

static gboolean cannot_reconnect(t_chat *chat) {
    puts("cannot reconnect");
    chat++;
    return G_SOURCE_REMOVE;
}

bool mx_reconnect_hanlder(t_dtp *token, t_chat *chat) {
    cJSON *auth_token = NULL;
    cJSON *login = NULL;

    if (chat->auth_token) {
        return false;
    }
    auth_token = cJSON_GetObjectItemCaseSensitive(token->json, "token");
    if (!auth_token || !cJSON_IsString(auth_token)
        || !mx_isvalid_token(auth_token->valuestring)) {
        return false;
    }
    login = cJSON_GetObjectItemCaseSensitive(token->json, "login");
    if (!login || !cJSON_IsString(login)
        || !mx_match_search(login->valuestring, MX_LOGIN_REGEX)) {
        return false;
    }
    chat->login = strdup(login->valuestring);
    chat->auth_token = strdup(auth_token->valuestring);
    //TODO WITH WINDOW GUI
    mx_logger(MX_LOG_FILE, LOGMSG, "Reconnected\n");
    return true;
}

bool mx_reconnect(t_chat *chat) {
    g_idle_add(G_SOURCE_FUNC(reconnect_on), chat);
    for (int i = 0; i < MX_RECONN_ATTEMPTS; i++) {
        mx_logger(MX_LOG_FILE, LOGMSG, "Attemp to reconnect[%d]\n", i);
        sleep(MX_RECONN_DELAY_S);
        if (mx_connect(chat)) {
            fprintf(stderr, "reconnected token = %s\n", chat->auth_token);
            if (chat->auth_token) {
                t_dtp *reconnect = mx_token_request(chat->auth_token);

                mx_send_request(chat, reconnect);
                mx_free_request(&reconnect);
                mx_free((void**)&(chat->auth_token));
                mx_free((void**)&(chat->login));
            }
            return true;
        }
    }
    mx_logger(MX_LOG_FILE, LOGMSG, "Cannot reconnect\n");
    g_idle_add(G_SOURCE_FUNC(cannot_reconnect), chat);
    return false;
}
