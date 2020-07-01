#include "client.h"

/*
 * Function: mx_sticker_request
 * -------------------------------
 * Creates message request with type DB_STICKER
 * 
 * sticker: name of sticker
 * room_id: room id
 * 
 * returns: sticker request
 */
t_dtp *mx_sticker_request(char *sticker, guint64 room_id) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_MSG))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "message", MX_J_STR(sticker)))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "msg_type", DB_STICKER))
        return NULL;
    return mx_get_transport_data(json_result);
}
