#include "client.h"

static gchar *set_tag(gchar *text, const gchar *tag, gchar *delim) {
    gchar **parts = g_strsplit(text, delim, -1);
    gchar *result = "";
    gchar *tagged = NULL;
    gchar *save = NULL;

    if (!*parts)
        return g_strdup("");
    for (gint i = 0; parts[i]; i++) {
        result = g_strjoin("", result, parts[i], NULL);
        save = result;
        i++;
        if (!parts[i])
            break;
        tagged = g_strdup_printf(tag, parts[i]);
        result = g_strjoin("", result, tagged, NULL);
        g_free(save);
        g_free(tagged);
    }
    g_strfreev(parts);
    return result;
}

gchar *mx_format_text(gchar *text) {
    gchar *result = NULL;
    gchar *save = NULL;

    result = set_tag(text, MX_OP_UNDER, MX_FT_UNDER);
    save = result;
    result = set_tag(result, MX_OP_BOLD, MX_FT_BOLD);
    g_free(save);
    save = result;
    result = set_tag(result, MX_OP_SCRATCH, MX_FT_SCRATCH);
    g_free(save);
    save = result;
    result = set_tag(result, MX_OP_ITALIC, MX_FT_ITALIC);
    g_free(save);
    save = result;
    result = set_tag(result, MX_OP_IMPORTANT, MX_FT_IMPORTANT);
    g_free(save);
    return result;
}
