#include "utils.h"

void mx_free_request_struct(t_pds **request) {
    mx_strdel((void **)(&(*request)->data));
    mx_strdel((void **)(&(*request)->len));
    *request = NULL;
}

void mx_free_decode_struct(t_pdl **decode_req) {
    mx_strdel((void **)(&(*decode_req)->data));
    mx_strdel((void **)(&(*decode_req)->len));
    *decode_req = NULL;
}

t_pds *mx_request_creation(int req_type, char *req_body) {
    t_pds *req_struct = malloc(sizeof(t_pds));
    char str[1024];

    sprintf(str, "%c%s", req_type, req_body);
    req_struct->data = strdup(str);
    sprintf(str, "%lu", strlen(req_body));
    req_struct->len = strdup(str);
    return req_struct;
}
t_pdl *mx_request_decode(char *request) {
    t_pdl *decode_struct = malloc(sizeof(t_pdl));
    char str[1024];

    sprintf(str, "%d", request[0]);
    decode_struct->type = atoi(str);
    sprintf(str, "%s", ++request);
    decode_struct->data = strdup(str);
    sprintf(str, "%lu", strlen(request) - 1);
    decode_struct->len = strdup(str);
    return decode_struct;
}
