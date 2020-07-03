#include "api.h"

/*
 * Function: mx_search_rooms_request
 * -------------------------------
 * Creates request "found rooms"
 * 
 * array: cJSON object that contains array of found rooms
 * 
 * returns: new request
 */
t_dtp *mx_search_rooms_request(cJSON *array) {
    cJSON *res = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(res, "type", RQ_SEARCH_CH))
        return NULL;
    if (!cJSON_AddItemReferenceToObject(res, "rooms", array))
        return NULL;
    return mx_get_transport_data(res);
}

static gboolean is_valid(gchar *name) {
    gsize len = strlen(name);

    if (len <= 0 || len > MX_MAX_ROOM_NAME)
        return FALSE;
    return TRUE;
}

/*
 * Function: mx_search_rooms_handler
 * -------------------------------
 * Handles request from client
 * 
 * data: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_search_rooms_handler(t_dtp *data, t_client *client) {
    cJSON *name = cJSON_GetObjectItemCaseSensitive(data->json, "name");
    t_dtp *answer = NULL;

    if (!cJSON_IsString(name) || !is_valid(name->valuestring))
        return FALSE;
    answer = mx_search_rooms_request(mx_search_room(client->info->database,
                                                    name->valuestring,
                                                    client->user->user_id));
    mx_send(client->out, answer);
    mx_free_request(&answer);
    return TRUE;
}
