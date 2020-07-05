#include "api.h"

/*
 * Function: mx_upd_room_desc_request
 * -------------------------------
 * Creates request "update room description"
 * 
 * room_id: room id that need to update description
 * desc: new description
 * 
 * returns: new request
 */
t_dtp *mx_upd_room_desc_request(guint64 room_id, char *desc) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_ROOM_DESC))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "desc", desc))
        return NULL;
    return mx_get_transport_data(json_result);
}

static gboolean is_valid(cJSON *desc) {
    gsize len = strlen(desc->valuestring);

    if (len > MX_MAX_MESSAGE)
        return FALSE;
    return TRUE;
}

/*
 * Function: mx_upd_room_desc_handler
 * -------------------------------
 * Handles request from client
 * 
 * room: request from client
 * client: client that sent this request
 * 
 * returns: success of handling
 */
gboolean mx_upd_room_desc_handler(t_dtp *room, t_client *client) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(room->json, "room_id");
    cJSON *desc = cJSON_GetObjectItemCaseSensitive(room->json, "desc");
    t_dtp *resend = NULL;

    if (!cJSON_IsNumber(room_id) || !cJSON_IsString(desc) || !is_valid(desc))
        return FALSE;
    if (mx_get_type_member(client->info->database, client->user->user_id,
                           room_id->valueint) != DB_CUSTOMER) {
        return FALSE;
    }
    mx_edit_desc_room_by_id(client->info->database, room_id->valueint,
                            desc->valuestring);
    resend = mx_upd_room_desc_request(room_id->valueint, desc->valuestring);
    mx_send_to_all(resend, client, room_id->valueint);
    mx_free_request(&resend);
    return TRUE;
}
