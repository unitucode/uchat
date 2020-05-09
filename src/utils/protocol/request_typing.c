#include "utils.h"

void mx_free_request_struct(t_pds **request) {
    mx_free((void **)(&(*request)->data));
    mx_free((void **)(&(*request)->len));
    mx_free((void**)request);
}

void mx_free_decode_struct(t_pdl **decode_req) {
    mx_free((void **)(&(*decode_req)->data));
    mx_free((void**)decode_req);
}

t_pds *mx_request_creation(int req_type, char *req_body) {
    t_pds *req_struct = mx_malloc(sizeof(t_pds));
    char str[MX_BUF_SIZE];

    sprintf(str, "%c%s", req_type, req_body);
    req_struct->data = strdup(str);
    sprintf(str, "%lu", strlen(req_body));
    req_struct->len = strdup(str);
    return req_struct;
}

t_pdl *mx_request_decode(char *request) {
    t_pdl *decode_struct = mx_malloc(sizeof(t_pdl));
    char str[MX_BUF_SIZE];

    sprintf(str, "%d", request[0]);
    decode_struct->type = atoi(str);
    sprintf(str, "%s", ++request);
    decode_struct->data = strdup(str);
    decode_struct->len = strlen(decode_struct->data);
    return decode_struct;
}
