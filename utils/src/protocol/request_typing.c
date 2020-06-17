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

void mx_free_request(t_dtp **request) {
    if (request && *request) {
        cJSON_Delete((*request)->json);
        mx_free((void **)(&(*request)->data));
        mx_free((void**)request);
    }
}

static t_dtp *get_filled_dtp(char *str, size_t buf_size) {
    t_dtp *req = mx_malloc(sizeof(t_dtp));
    int type;

    req->data = (char*)mx_memdup(str, buf_size);
    req->str = req->data + 4;
    req->len = buf_size - 1;
    req->json = cJSON_Parse(req->str);
    if ((type = mx_get_type_dtp(req)) < 0 || type >= RQ_COUNT_REQUEST) {
        mx_logger(MX_LOG_FILE, LOGWAR, "Invalid message type\n");
        mx_free_request(&req);
        return NULL;
    }
    req->type = type;
    if (!req->json || req->type == -1) {
        mx_logger(MX_LOG_FILE, LOGWAR, "Invalid json\n");
        mx_free_request(&req);
        return NULL;
    }
    return req;
}

t_dtp *mx_request_creation(char *req_body) {
    size_t req_len = strlen(req_body);
    size_t buf_size = sizeof(int) + req_len + 2;
    char str[buf_size];

    bzero(str, buf_size);
    strcpy(str + 4, req_body);
    strcat(str + 4, "\n");
    memcpy(str, &req_len, sizeof(int));
    return get_filled_dtp(str, buf_size);
}
