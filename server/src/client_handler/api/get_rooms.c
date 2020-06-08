#include "server.h"

bool mx_get_rooms(t_dtp *data, t_client *client) {
    cJSON *date = cJSON_GetObjectItemCaseSensitive(data->json, "date");

    if (!date || !cJSON_IsNumber(date))
        return false;
    
    return true;
}
