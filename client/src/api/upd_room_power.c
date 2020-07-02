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
    g_message("update power for %d room, power = %f PLEASE CHECK IF ROOM EXIST client/src/api/upd_room_power.c\n", room_id->valueint, power->valuedouble);
    (void)chat; // TODELETE
    return TRUE;
}
