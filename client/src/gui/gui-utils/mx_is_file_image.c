#include "client.h"

gboolean mx_is_file_image(gchar *filename) {
    if (g_str_has_suffix(filename, ".png")
        || g_str_has_suffix(filename, ".jpg")
        || g_str_has_suffix(filename, ".jpeg")) {
        return TRUE;
    }
    else
        return FALSE;
}

gboolean mx_is_file_animation(gchar *filename) {
    if (g_str_has_suffix(filename, ".gif")) {
        return TRUE;
    }
    else
        return FALSE;
}
