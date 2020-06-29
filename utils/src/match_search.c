#include "utils.h"

gboolean mx_match_nsearch(gchar *str, gchar *regex, gssize size) {
    gchar buf[size + 1];
    GRegex *g_reg = NULL;
    GMatchInfo *match_info;
    gboolean g_res;

    buf[size] = 0;
    g_strlcpy(buf, str, size + 1);
    g_reg = g_regex_new(regex, 0, 0, NULL);
    g_res = g_regex_match(g_reg, buf, 0, &match_info);
    g_match_info_free(match_info);
    return g_res;
}

gboolean mx_match_search(gchar *str, gchar *regex) {
    GRegex *g_reg = NULL;
    GMatchInfo *match_info;
    gboolean g_res;

    g_reg = g_regex_new(regex, 0, 0, NULL);
    g_res = g_regex_match(g_reg, str, 0, &match_info);
    g_match_info_free(match_info);
    g_regex_unref(g_reg);
    return g_res;
}

