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
    return room;
}

static gboolean get_data(cJSON *msg, cJSON **dtp, char *field) {
    *dtp = cJSON_GetObjectItemCaseSensitive(msg, field);
    if (!*dtp)
        return FALSE;
    return TRUE;
}

static gboolean is_valid(t_groom *groom, gboolean is_valid) {
    if (!is_valid) {
        mx_delete_groom(groom);
        return FALSE;
    }
    return TRUE;
}

t_groom *mx_create_groom(cJSON *room) {
    t_groom *groom = mx_init_groom();
    cJSON *dtp = NULL;
    gboolean valid = TRUE;

    mx_reset_select_count(groom);
    if ((valid = get_data(room, &dtp, "name")) && cJSON_IsString(dtp))
        groom->room_name = strdup(dtp->valuestring);
    if ((valid = get_data(room, &dtp, "customer_id")) && cJSON_IsNumber(dtp))
        groom->customer_id = dtp->valuedouble;
    if ((valid = get_data(room, &dtp, "id")) && cJSON_IsNumber(dtp))
        groom->id = dtp->valuedouble;
    if ((valid = get_data(room, &dtp, "date")) && cJSON_IsNumber(dtp))
        groom->date = dtp->valuedouble;
    if ((valid = get_data(room, &dtp, "desc")) && cJSON_IsString(dtp))
        groom->desc = strdup(dtp->valuestring);
    if ((valid = get_data(room, &dtp, "power")) && cJSON_IsNumber(dtp))
        groom->power = dtp->valuedouble;
    if (!is_valid(groom, valid))
        return NULL;
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
