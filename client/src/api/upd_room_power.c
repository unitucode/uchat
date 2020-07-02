#include "client.h"

/*
 * Function: mx_upd_room_power_handler
 * -------------------------------
 * Handles request from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_upd_room_power_handler(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *power = cJSON_GetObjectItemCaseSensitive(data->json, "power");

    if (!cJSON_IsNumber(room_id) || !cJSON_IsNumber(power))
        return FALSE;
    mx_gupd_room_power(room_id->valuedouble, power->valuedouble,
                       chat->builder);
    return TRUE;
}
