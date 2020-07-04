#include "api.h"

/*
 * Function: mx_error_msg_request
 * -------------------------------
 * Creates request "error message"
 * 
 * msg: message of error
 * error_code: code of errors in utils/inc/protocol.h
 * 
 * returns: new request
 */
t_dtp *mx_error_msg_request(guint64 error_code, char *msg) {
    cJSON *json_result = cJSON_CreateObject();

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_ERROR_MSG))
        return NULL;
    if (!cJSON_AddNumberToObject(json_result, "error_code", error_code))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "msg", MX_J_STR(msg)))
        return NULL;
    return mx_get_transport_data(json_result);
}
