#include "client.h"

/*
 * Function: mx_error_handler
 * -------------------------------
 * Handles errors from server
 * 
 * data: request from server
 * chat: information about chat
 * 
 * returns: success of handling
 */
gboolean mx_error_handler(t_dtp *data, t_chat *chat) {
    cJSON *error = cJSON_GetObjectItemCaseSensitive(data->json, "error_code");

    if (!cJSON_IsNumber(error) || error->valuedouble >= ER_COUNT_ERRS
        || error->valuedouble < 0) {
        return FALSE;
    }
    if (chat->error_handler[(guint64)error->valuedouble])
        chat->error_handler[(guint64)error->valuedouble](chat->builder);
    else
        return FALSE;
    return TRUE;
}
