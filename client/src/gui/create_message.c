#include "client.h"

static bool get_data(cJSON *msg, cJSON **data, char *field) {
    *data = cJSON_GetObjectItemCaseSensitive(msg, field);
    if (!*data)
        return false;
    return true;
}

t_gmsg *mx_create_gmsg(cJSON *msg) {
    t_gmsg *gmsg = mx_malloc(sizeof(t_gmsg));
    cJSON *data = NULL;
    bool valid = true;

    if ((valid = get_data(msg, &data, "msg")) && cJSON_IsString(data))
        gmsg->msg = strdup(data->valuestring);
    if ((valid = get_data(msg, &data, "login")) && cJSON_IsString(data))
        gmsg->login = strdup(data->valuestring);
    if ((valid = get_data(msg, &data, "room_name")) && cJSON_IsString(data))
        gmsg->room_name = strdup(data->valuestring);
    if ((valid = get_data(msg, &data, "date")) && cJSON_IsNumber(data))
        gmsg->date = data->valueint;
    if ((valid = get_data(msg, &data, "id_message")) && cJSON_IsNumber(data))
        gmsg->id_message = data->valueint;
    if (!valid) {
        mx_delete_gmsg(&gmsg);
        return NULL;
    }
    return gmsg;
}

void mx_delete_gmsg(t_gmsg **gmsg) {
    if (gmsg && *gmsg) {
        mx_free((void**)&(*gmsg)->msg);
        mx_free((void**)&(*gmsg)->login);
        mx_free((void**)&(*gmsg)->room_name);
        mx_free((void**)gmsg);
        *gmsg = NULL;
    }
}
