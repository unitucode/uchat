#include "api.h"

/*
 * Function: mx_member_info_request
 * -------------------------------
 * Creates request "information about member"
 * 
 * user: infomation about user in database
 * 
 * returns: new request
 */
t_dtp *mx_member_info_request(t_db_user *user) {
    cJSON *res = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(res, "type", RQ_MEMBER_INFO))
        return NULL;
    if (!cJSON_AddStringToObject(res, "desc", user->desc))
        return NULL;
    if (!cJSON_AddStringToObject(res, "login", user->login))
        return NULL;
    return mx_get_transport_data(res);
}

/*
 * Function: mx_member_info_handler
 * -------------------------------
 * Handles request from client
 * 
 * id: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_member_info_handler(t_dtp *id, t_client *client) {
    cJSON *user_id = cJSON_GetObjectItemCaseSensitive(id->json, "user_id");
    t_db_user *user = NULL;
    t_dtp *answer = NULL;

    if (!cJSON_IsNumber(user_id))
        return FALSE;
    user = mx_get_user_by_id(client->info->database, user_id->valueint);
    if (!user)
        return FALSE;
    answer = mx_member_info_request(user);
    mx_send(client->out, answer);
    mx_free_request(&answer);
    mx_free_user(&user);
    return TRUE;
}
