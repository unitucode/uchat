#include "client.h"

t_groom *mx_init_groom() {
    t_groom *room = mx_malloc(sizeof(t_groom));

    room->room_name = NULL;
    room->customer = NULL;
    room->box_rooms = NULL;
    room->box_messages = NULL;
    room->page = NULL;
    room->row_room = NULL;
    room->stack_msg = NULL;
    room->id = -1;
    room->date = -1;
    room->is_updated = true;
    room->desc = NULL;
    room->is_watched = false;
    room->customer_id = 0;
    room->members = g_hash_table_new(g_direct_hash, g_direct_equal);
    room->uploaded = 0;
    return room;
}

bool get_data(cJSON *msg, cJSON **data, char *field) { // TO FIX IN GMSG GET_DATA
    *data = cJSON_GetObjectItemCaseSensitive(msg, field);
    if (!*data)
        return false;
    return true;
}

t_groom *mx_create_groom(cJSON *room) {
    t_groom *groom = mx_init_groom();
    cJSON *data = NULL;
    bool valid = true;

    if ((valid = get_data(room, &data, "name")) && cJSON_IsString(data))
        groom->room_name = strdup(data->valuestring);
    if ((valid = get_data(room, &data, "customer_id")) && cJSON_IsNumber(data))
        groom->customer_id = data->valuedouble;
    if ((valid = get_data(room, &data, "id")) && cJSON_IsNumber(data))
        groom->id = data->valuedouble;
    if ((valid = get_data(room, &data, "date")) && cJSON_IsNumber(data))
        groom->date = data->valuedouble;
    if ((valid = get_data(room, &data, "desc")) && cJSON_IsString(data))
        groom->desc = strdup(data->valuestring);
    if ((valid = get_data(room, &data, "power")) && cJSON_IsNumber(data))
        groom->power = data->valuedouble;
    if (!valid) {
        mx_delete_groom(groom);
        return NULL;
    }
    return groom;
}

void mx_delete_groom(t_groom *room) {
    if (room) {
        mx_free((void**)&(room->room_name));
        mx_free((void**)&(room->customer));
        mx_free((void**)&(room->desc));
        mx_free((void**)&room);
        room = NULL;
    }
}
