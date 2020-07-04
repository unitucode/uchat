#include "api.h"

/*
 * Function: mx_upd_room_name_request
 * -------------------------------
 * Creates request "update room name"
 * 
 * room_id: room id that need to update name
 * room_name: new name
 * 
 * returns: new request
 */
t_dtp *mx_upd_room_name_request(guint64 room_id, char *room_name) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_ROOM_NAME))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "room_name", room_name))
        return NULL;
    return mx_get_transport_data(json_result);
}

static gboolean is_valid(gchar *room_name) {
    gsize len = strlen(room_name);

    if (len <= 0 || len > MX_MAX_ROOM_NAME)
        return FALSE;
    return TRUE;
}

/*
 * Function: mx_upd_room_name_handler
 * -------------------------------
 * Handles request from client
 * 
 * room: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_upd_room_name_handler(t_dtp *room, t_client *client) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(room->json, "room_id");
    cJSON *room_name = cJSON_GetObjectItemCaseSensitive(room->json,
                                                        "room_name");
    t_dtp *resend = NULL;

    if (!cJSON_IsNumber(room_id) || !cJSON_IsString(room_name))
        return FALSE;
    if (!is_valid(room_name->valuestring))
        return FALSE;
    if (mx_get_type_member(client->info->database, client->user->user_id,
                           room_id->valueint) != DB_CUSTOMER) {
        return FALSE;
    }
    mx_edit_room_name_by_id(client->info->database, room_id->valueint,
                            room_name->valuestring);
    resend = mx_upd_room_name_request(room_id->valueint,
                                      room_name->valuestring);
    mx_send_to_all(resend, client, room_id->valueint);
    mx_free_request(&resend);
    return TRUE;
}
