#include "utils.h"

void mx_free_request_struct(t_pds **request) {
    if (request && *request) {
        mx_free((void **)(&(*request)->data));
        mx_free((void **)(&(*request)->len));
        mx_free((void**)request);
    }
}

void mx_free_decode_struct(t_pdl **decode_req) {
    if (decode_req && *decode_req) {
        mx_free((void **)(&(*decode_req)->data));
        mx_free((void**)decode_req);
    }
}

int get_counts_of_digits(int number) {
    int count = (number == 0) ? 1 : 0;
    while (number != 0) {
        count++;
        number /= 10;
    }
    return count;
}

t_pds *mx_request_creation(int room, t_request_types req_type, char *req_body) {
    t_pds *req_struct = mx_malloc(sizeof(t_pds));
    int buf_size = strlen(req_body) +
        get_counts_of_digits(room) +
        get_counts_of_digits(req_type);
        printf("Buf size - %d\n", buf_size);
    char str[buf_size];

    sprintf(str, "%d|%d|%s", room, req_type, req_body);
    req_struct->data = strdup(str);
    sprintf(str, "%lu", strlen(req_struct->data));
    req_struct->len = strdup(str);
    return req_struct;
}

static void pars_request(t_pdl *decode, char *request) {
    char *delim = strchr(request, '|');
    char *first_part;
    char *temp;

    delim++;
    delim = strchr(delim, '|');
    first_part = strndup(request, delim - request);
    delim++;
    temp = strtok(first_part, "|");
    decode->room = atoi(temp);
    temp= strtok(NULL, "|");
    decode->type = atoi(temp);
    decode->data = strdup(delim);
    decode->len = strlen(delim);
    mx_free((void**)&first_part);
}

t_pdl *mx_request_decode(char *request) {
    t_pdl *decode_struct = NULL;

    if(!(mx_match_search("1s|s23|sdfsdfs", MX_REQ_REGEX))) {
        mx_logger(MX_LOG_FILE, LOGWAR, "Undefined server request\n");
        return NULL;
    }
    decode_struct = mx_malloc(sizeof(t_pdl));
    pars_request(decode_struct, request);
    return decode_struct;
}
