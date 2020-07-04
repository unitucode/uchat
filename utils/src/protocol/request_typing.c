#include "protocol.h"

gint64 mx_get_type_dtp(t_dtp *dtp) {
    cJSON *type = cJSON_GetObjectItemCaseSensitive(dtp->json, "type");
    gint64 result = -1;

    if (!cJSON_IsNumber(type)) {
        cJSON_Delete(type);
        return result;
    }
    result = (gint64)type->valuedouble;
    return result;
}

void mx_free_request(t_dtp **request) {
    if (request && *request) {
        cJSON_Delete((*request)->json);
        mx_free((void**)request);
    }
}

static t_dtp *get_filled_dtp(char *str, size_t buf_size) {
    t_dtp *req = mx_malloc(sizeof(t_dtp));
    gint type;

    req->str = strdup(str);
    req->len = buf_size - 1;
    req->json = cJSON_Parse(req->str);
    if ((type = mx_get_type_dtp(req)) < 0 || type >= RQ_COUNT_REQUEST) {
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_WARNING, "Invalid message type");
        mx_free_request(&req);
        return NULL;
    }
    req->type = type;
    if (!req->json || req->type == -1) {
        mx_logger(MX_LOG_FILE, G_LOG_LEVEL_WARNING, "Invalid json");
        mx_free_request(&req);
        return NULL;
    }
    return req;
}

t_dtp *mx_request_creation(char *req_body) {
    size_t req_len = strlen(req_body);
    size_t buf_size = req_len + 2;
    char str[buf_size];

    bzero(str, buf_size);
    strcpy(str, req_body);
    str[buf_size - 2] = '\n';
    return get_filled_dtp(str, buf_size);
}
