#include "api.h"

static gboolean is_valid(t_client *client, guint64 room_id) {
    if (!mx_is_member(client->info->database, client->user->user_id,
                      room_id)) {
        return FALSE;
    }
    if (mx_get_type_member(client->info->database, client->user->user_id,
                           room_id) == DB_BANNED) {
        return FALSE;
    }
    return TRUE;
}

static gboolean resend(t_client *client, cJSON *msgs_json) {
    t_dtp *msgs = NULL;

    if (!cJSON_AddNumberToObject(msgs_json, "type", RQ_GET_NEW_MSGS)) {
        cJSON_Delete(msgs_json);
        return FALSE;
    }
    msgs = mx_get_transport_data(msgs_json);
    mx_send(client->out, msgs);
    mx_free_request(&msgs);
    return TRUE;
}

/*
 * Function: mx_get_msgs_handler
 * -------------------------------
 * Handles request from client and send all messages of room to client
 * 
 * data: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_get_msgs_handler(t_dtp *data, t_client *client) {
    cJSON *date = cJSON_GetObjectItemCaseSensitive(data->json, "date");
    cJSON *count = cJSON_GetObjectItemCaseSensitive(data->json, "count");
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *msgs_json = NULL;

    if (!cJSON_IsNumber(date) || !cJSON_IsNumber(count)
        || !cJSON_IsNumber(room_id)
        || !is_valid(client, room_id->valuedouble)) {
        return FALSE;
    }
    msgs_json = mx_get_new_messages_by_id(
        client->info->database, room_id->valueint, date->valuedouble,
        count->valueint);
    if (!resend(client, msgs_json)) {
        cJSON_Delete(msgs_json);
        return FALSE;
    }
    mx_update_room_power(client, room_id->valuedouble);
    return TRUE;
}
