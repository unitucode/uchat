#include "client.h"

t_groom *mx_init_groom(void) {
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
    room->is_updated = TRUE;
    room->desc = NULL;
    room->is_watched = FALSE;
    room->customer_id = 0;
    room->members = g_hash_table_new(g_direct_hash, g_direct_equal);
    room->uploaded = 0;
    room->select_all = 0;
    room->select_own = 0;
    room->select_another = 0;
    room->select_notedit = 0;
    return room;
}

gboolean get_data(cJSON *msg, cJSON **data, char *field) {
    *data = cJSON_GetObjectItemCaseSensitive(msg, field);
    if (!*data)
        return FALSE;
    return TRUE;
}

t_groom *mx_create_groom(cJSON *room) {
    t_groom *groom = mx_init_groom();
    cJSON *data = NULL;
    gboolean valid = TRUE;

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
