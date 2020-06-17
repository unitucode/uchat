#include "server.h"

bool mx_upload_file_handler(t_dtp *data, t_client *client) { // TODO leaks
    // cJSON *name = cJSON_GetObjectItemCaseSensitive(data->json, "name");
    // cJSON *size = cJSON_GetObjectItemCaseSensitive(data->json, "size");
    // char *bytes = NULL;
    // FILE *fd = NULL;

    // if (!name || !cJSON_IsString(name))
    //     return false;
    // if (!size || !cJSON_IsNumber(size))
    //     return false;
    // bytes = mx_recv_file(client->ssl, size->valueint);
    // fd = fopen(name->valuestring, "w");
    // fwrite(bytes, 1, size->valueint, fd);
    // fclose(fd);
    data++;
    client++;
    return true;
}
