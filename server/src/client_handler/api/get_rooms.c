#include "api.h"

static void resend(t_client *client, cJSON *rooms_json) {
    t_dtp *rooms = mx_get_transport_data(rooms_json);

    mx_send(client->out, rooms);
    mx_free_request(&rooms);
}

/*
 * Function: mx_get_rooms_handler
 * -------------------------------
 * Handles request from client and send all messages of room to client
 * 
 * data: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_get_rooms_handler(t_dtp *data, t_client *client) {
    cJSON *date = cJSON_GetObjectItemCaseSensitive(data->json, "date");
    cJSON *rooms_json = cJSON_CreateObject();
    cJSON *rooms_array = NULL;

    if (!cJSON_IsNumber(date))
        return FALSE;
    rooms_array = mx_get_rooms(client->info->database, date->valueint,
                               client->user->user_id);
    if (!cJSON_AddItemReferenceToObject(rooms_json, "rooms", rooms_array)) {
        cJSON_Delete(rooms_json);
        return FALSE;
    }
    if (!cJSON_AddNumberToObject(rooms_json, "type", RQ_GET_ROOMS)) {
        cJSON_Delete(rooms_json);
        return FALSE;
    }
    resend(client, rooms_json);
    return TRUE;
}
