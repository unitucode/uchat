#include "client.h"

static bool get_data(cJSON *msg, cJSON **data, char *field) {
    *data = cJSON_GetObjectItemCaseSensitive(msg, field);
    if (!*data)
        return false;
    return true;
}

t_gmsg *mx_create_gmsg(cJSON *msg, t_chat *chat) {
    t_gmsg *gmsg = mx_malloc(sizeof(t_gmsg));
    cJSON *data = NULL;
    bool valid = true;
    t_groom *groom = NULL;

    if ((valid = get_data(msg, &data, "message")) && cJSON_IsString(data))
        gmsg->msg = strdup(data->valuestring);
    if ((valid = get_data(msg, &data, "room_id")) && cJSON_IsNumber(data))
        gmsg->room_id = data->valuedouble;
    groom = mx_get_groom_by_id(data->valuedouble, chat->builder);
    if ((valid = get_data(msg, &data, "user_id")) && cJSON_IsNumber(data))
        gmsg->login = g_strdup(MX_J_STR(g_hash_table_lookup(groom->members, GINT_TO_POINTER(data->valueint))));
    if ((valid = get_data(msg, &data, "date")) && cJSON_IsNumber(data))
        gmsg->date = data->valuedouble;
    if ((valid = get_data(msg, &data, "message_id")) && cJSON_IsNumber(data))
        gmsg->message_id = data->valuedouble;
    if ((valid = get_data(msg, &data, "msg_type")) && cJSON_IsNumber(data))
        gmsg->type = data->valuedouble;
    if ((valid = get_data(msg, &data, "power")) && cJSON_IsNumber(data))
        gmsg->power = mx_get_used_power(data->valuedouble);
    if (!valid) {
        mx_delete_gmsg(gmsg);
        return NULL;
    }
    gmsg->row_msg = NULL;
    return gmsg;
}

void mx_delete_gmsg(t_gmsg *gmsg) {
    if (gmsg) {
        mx_free((void**)&(gmsg->msg));
        mx_free((void**)&(gmsg->login));
        mx_free((void**)&gmsg);
        gmsg = NULL;
    }
}
