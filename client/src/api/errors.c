#include "client.h"

bool mx_error_handle(t_dtp *data, t_chat *chat) {
    cJSON *data_obj = cJSON_GetObjectItemCaseSensitive(data->json, "error_code");
    int error = data_obj->valueint;

    if (error == 10)
        mx_errmsg_wrong_authdata(chat->builder);
    if (error == 11)
        mx_errmsg_user_exist(chat->builder);
    return true;
}
