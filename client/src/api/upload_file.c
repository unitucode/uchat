#include "client.h"

static char *upload_file(char *file_path) {
    FILE *file = fopen(file_path, "r");
    struct stat st;
    char *bytes = NULL;

    if (!file) {
        mx_logger(MX_LOG_FILE, LOGWAR, "Cannot open file %s\n", file_path);
        return NULL;
    }
    stat(file_path, &st);
    if (st.st_size > MX_MAX_FILE_SIZE)
        return NULL;
    bytes = mx_malloc(st.st_size + 1);
    if (!fgets(bytes, st.st_size, file)) {
        if (bytes)
            mx_free((void**)&bytes);
        return NULL;
    }
    return bytes;
}

t_dtp *mx_upload_file_request(char *file_path) {
    cJSON *json_result = cJSON_CreateObject();
    char *file = upload_file(file_path);

    if (!cJSON_AddNumberToObject(json_result, "type", RQ_FILE))
        return NULL;
    if (!cJSON_AddStringToObject(json_result, "file", file))
        return NULL;
    return mx_get_transport_data(json_result);
}

bool mx_upload_file_handler(t_dtp *data, t_chat *chat) {
    data++;
    chat++;
    return true;
}
