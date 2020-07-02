#include "server.h"

void mx_update_room_power(t_client *client, guint64 room_id) {
    cJSON *power_json = cJSON_CreateObject();
    gdouble power = mx_get_power_of_room(client->info->database, room_id);
    t_dtp *request = NULL;

    if (!cJSON_AddNumberToObject(power_json, "type", RQ_UPD_ROOM_POWR))
        return;
    if (!cJSON_AddNumberToObject(power_json, "power", power))
        return;
    if (!cJSON_AddNumberToObject(power_json, "room_id", room_id))
        return;
    request = mx_get_transport_data(power_json);
    mx_send_to_all(request, client, room_id);
    mx_free_request(&request);
}
