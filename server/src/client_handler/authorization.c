#include "server.h"

void mx_create_token(char **token, char *login) {
    char *seed = g_compute_checksum_for_string(G_CHECKSUM_MD5, login, strlen(login));
    char *hash = NULL;
    mx_randomize_str(seed, strlen(login) / 2);
    hash = g_compute_checksum_for_string(G_CHECKSUM_SHA256, seed, strlen(seed));
    *token = g_strjoin("", hash, login, NULL);
    g_free(hash);
    g_free(seed);
}
