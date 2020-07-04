#include "client.h"

gchar *mx_get_filename(gchar *full_name) {
    gchar *filename = g_strstr_len(full_name,
                                   strlen(full_name),
                                   MX_FILE_DELIM);

    if (filename && strlen(filename) > strlen(MX_FILE_DELIM))
        filename += strlen(MX_FILE_DELIM);
    return filename;
}
