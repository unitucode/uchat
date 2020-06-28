#include "client.h"

gboolean mx_error_handler(t_dtp *data, t_chat *chat) {
    cJSON *error = cJSON_GetObjectItemCaseSensitive(data->json, "error_code");

    if (!cJSON_IsNumber(error) || error->valueint >= ER_COUNT_ERRS
        || error->valueint < 0) {
        return FALSE;
    }
    if (chat->error_handler[error->valueint])
        chat->error_handler[error->valueint](chat->builder);
    return TRUE;
}
