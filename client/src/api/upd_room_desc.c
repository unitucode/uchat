#include "client.h"

t_dtp *mx_upd_room_desc_request(int room_id, char *desc) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_UPD_ROOM_DESC))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "room_id", room_id))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "desc", MX_J_STR(desc)))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_msg_handler(t_dtp *data, t_chat *chat) {
    cJSON *room_id = cJSON_GetObjectItemCaseSensitive(data->json, "room_id");
    cJSON *room_name = cJSON_GetObjectItemCaseSensitive(data->json, "room_name");

    if (!room_id || !cJSON_IsNumber(room_id))
        return false;
    if (!room_name || !cJSON_IsString(room_name))
        return false;
    //WORKING WITH GUI
    printf("room_id = %d new room_name = %s\n", room_id->valueint, room_name->valuestring);
    //WORKING WITH GUI
    return true;
}
