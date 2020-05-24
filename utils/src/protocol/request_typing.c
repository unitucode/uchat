#include "protocol.h"

int mx_get_type_dtp(t_dtp *dtp) {
    cJSON *type = cJSON_GetObjectItemCaseSensitive(dtp->json, "type");
    int result = -1;

    if (type && !cJSON_IsNumber(type)) {
        cJSON_Delete(type);
        return result;
    }
    if (!type)
        return result;
    result = type->valueint;
    return result;
}

void mx_free_request_struct(t_dtp **request) {
    if (request && *request) {
        cJSON_Delete((*request)->json);
        mx_free((void **)(&(*request)->data));
        mx_free((void**)request);
    }
}

t_dtp *mx_request_creation(char *req_body) {
    t_dtp *req = mx_malloc(sizeof(t_dtp));
    size_t req_len = strlen(req_body);
    size_t buf_size = sizeof(int) + req_len + 1;
    char str[buf_size];

    bzero(str, buf_size);
    strcpy(str + 4, req_body);
    memcpy(str, &req_len, sizeof(int));
    req->data = (char*)mx_memdup(str, buf_size);
    req->str = req->data + 4;
    req->len = buf_size - 1;
    req->json = cJSON_Parse(req->str);
    req->type = mx_get_type_dtp(req);
    if (!req->json || req->type == -1) {
        mx_logger(MX_LOG_FILE, LOGWAR, "Invalid json\n");
        return NULL;
    }
    return req;
}
