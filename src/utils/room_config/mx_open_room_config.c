#include "utils.h"

static void create_config(FILE *fp) {
    errno = 0;
    fp = fopen(MX_ROOM_CONFIG, "a");
    fprintf(fp, "{\n\n}");
    fclose(fp);
    mx_logger(MX_LOG_FILE, LOGMSG, \
                "Created empty \"%s\" file\n", MX_ROOM_CONFIG);
}

char *mx_open_room_config() {
    struct stat filestatus;
    char *file_contents;
    FILE *fp = NULL;
    int file_size;

    if (stat(MX_ROOM_CONFIG, &filestatus) == 0) {
        file_size = filestatus.st_size;
        file_contents = (char*)malloc(filestatus.st_size);
        fp = fopen(MX_ROOM_CONFIG, "rb");
        fread(file_contents, file_size, 1, fp);
        fclose(fp);
        return file_contents;
    }
    else
        create_config(fp);
    return NULL;
}
