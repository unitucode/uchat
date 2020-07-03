#include "api.h"

/*
 * Function: mx_search_msgs_request
 * -------------------------------
 * Creates request "found messages"
 * 
 * array: cJSON object that contains array of found messages
 * 
 * returns: new request
 */
t_dtp *mx_search_msgs_request(cJSON *array) {
    cJSON *res = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(res, "type", RQ_SEARCH_MSG))
        return NULL;
    if (!cJSON_AddItemReferenceToObject(res, "msgs", array))
        return NULL;
    return mx_get_transport_data(res);
}

static gboolean is_valid(cJSON *msg) {
    gsize len = strlen(msg->valuestring);

    if (len <= 0 || len > MX_MAX_MESSAGE)
        return FALSE;
    return TRUE;
}

/*
 * Function: mx_search_msgs_handler
 * -------------------------------
 * Handles request from client
 * 
 * data: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_search_msgs_handler(t_dtp *data, t_client *client) {
    cJSON *msg = cJSON_GetObjectItemCaseSensitive(data->json, "msg");
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    t_dtp *answer = NULL;

    if (!cJSON_IsString(msg) || !cJSON_IsNumber(room_id) || !is_valid(msg))
        return FALSE;
    if (!mx_is_member(client->info->database, client->user->user_id,
                      room_id->valueint)) {
        return FALSE;
    }
    if (mx_get_type_member(client->info->database, client->user->user_id,
                           room_id->valueint) == DB_BANNED) {
        return FALSE;
    }
    answer = mx_search_msgs_request(
        mx_search_message(client->info->database, msg->valuestring,
                          room_id->valueint));
    mx_send(client->out, answer);
    mx_free_request(&answer);
    return TRUE;
}
