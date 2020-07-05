#include "client.h"

static gboolean get_data(cJSON *msg, cJSON **data, char *field, 
                         cJSON_bool(check_valid)(const cJSON *const)) {
    *data = cJSON_GetObjectItemCaseSensitive(msg, field);
    if (!*data || !check_valid(*data))
        return FALSE;
    return TRUE;
}

static t_groom *help_create_message(gboolean *valid, cJSON *msg, t_gmsg *gmsg,
                                    t_chat *chat) {
    cJSON *data = NULL;
    t_groom *groom = NULL;

    if (*valid && (*valid = get_data(msg, &data, "message", cJSON_IsString)))
        gmsg->msg = strdup(data->valuestring);
    if (*valid && (*valid = get_data(msg, &data, "room_id", cJSON_IsNumber)))
        gmsg->room_id = data->valuedouble;
    if (!(*valid))
        return NULL;
    groom = mx_get_groom_by_id(data->valuedouble, chat->builder);
    if (*valid && (*valid = get_data(msg, &data, "user_id", cJSON_IsNumber))) {
        gpointer hash = g_hash_table_lookup(groom->members,
                                            GINT_TO_POINTER(data->valueint));
        gmsg->login = g_strdup(MX_J_STR(hash));
    }
    if (*valid && (*valid = get_data(msg, &data, "date", cJSON_IsNumber)))
        gmsg->date = data->valuedouble;
    return groom;
}

t_gmsg *mx_create_gmsg(cJSON *msg, t_chat *chat) {
    t_gmsg *gmsg = mx_malloc(sizeof(t_gmsg));
    cJSON *data = NULL;
    gboolean valid = TRUE;
    t_groom *groom = NULL;

    groom = help_create_message(&valid, msg, gmsg, chat);
    if (valid && (valid = get_data(msg, &data, "message_id", cJSON_IsNumber)))
        gmsg->message_id = data->valuedouble;
    if (valid && (valid = get_data(msg, &data, "msg_type", cJSON_IsNumber)))
        gmsg->type = data->valuedouble;
    if (valid && (valid = get_data(msg, &data, "power", cJSON_IsNumber)))
        gmsg->power = mx_get_used_power(data->valuedouble);
    if (!valid && mx_delete_gmsg(gmsg))
        return NULL;
    gmsg->row_msg = NULL;
    return gmsg;
}

gboolean mx_delete_gmsg(t_gmsg *gmsg) {
    if (gmsg) {
        mx_free((void**)&(gmsg->msg));
        mx_free((void**)&(gmsg->login));
        mx_free((void**)&gmsg);
        gmsg = NULL;
    }
    return TRUE;
}
