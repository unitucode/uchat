#include "client.h"

void mx_trim_message(gchar **message) {
    gchar *trimed = NULL;

    if (strlen(*message) > MX_MAX_MESSAGE) {
        trimed = g_strndup(*message, MX_MAX_MESSAGE);
        g_free(*message);
        *message = g_strdup(trimed);
        g_free(trimed);
    }
}
