#include "utils.h"
#include "protocol.h"

t_file *mx_upload_file(char *file_path) {
    FILE *file = fopen(file_path, "r");
    t_file *result = mx_malloc(sizeof(t_file));
    int readed = 0;

    if (!file) {
        mx_logger(MX_LOG_FILE, LOGWAR, "Cannot open file %s\n", file_path);
        return NULL;
    }
    stat(file_path, &result->st);
    if (result->st.st_size > MX_MAX_FILE_SIZE)
        return NULL;
    result->bytes = mx_malloc(result->st.st_size + 1);
    result->name = strdup(basename(file_path));
    bzero(result->bytes, result->st.st_size + 1);
    if (!(readed = fread(result->bytes, 1, result->st.st_size, file))) {
        mx_free_file(&result);
        fclose(file);
        return NULL;
    }
    fclose(file);
    return result;
}

void mx_free_file(t_file **file) {
    if (file && *file) {
        mx_free((void**)&((*file)->bytes));
        mx_free((void**)&((*file)->name));
        mx_free((void**)&(*file));
    }
}
