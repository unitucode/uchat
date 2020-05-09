#include "utils.h"

static void create_config(FILE *fp) {
    fp = mx_fopen(MX_CONFIG, "a");
    fprintf(fp, MX_DEFAULT_CONFIG);
    mx_fclose(fp);
    mx_logger(MX_LOG_FILE, LOGMSG, \
              "Created empty \"%s\" file\n", MX_CONFIG);
}

/*
 * Return  struct json_value  parsed from .json file  
 */
json_value *mx_open_config() {
    struct stat filestatus;
    char *file_contents;
    FILE *fp = NULL;
    json_value *value;

    if (stat(MX_CONFIG, &filestatus) == 0) {
        file_contents = (char*)mx_malloc(filestatus.st_size);
        fp = mx_fopen(MX_CONFIG, "rb");
        fread(file_contents, filestatus.st_size, 1, fp);
        mx_fclose(fp);
        value = json_parse((json_char*)file_contents, filestatus.st_size);
        mx_free((void**)&file_contents);
        return value;
    }
    else
        create_config(fp);
    return NULL;
}
