#include "utils.h"

gboolean mx_isvalid_login(char *login) {
    return mx_match_search(login, MX_LOGIN_REGEX);
}

gboolean mx_isvalid_hash(char *hash) {
    return mx_match_search(hash, MX_HASH_REGEX);
}

gboolean mx_isvalid_token(char *token) {
    if (mx_match_nsearch(token, MX_HASH_REGEX, MX_SHA256_LENGTH)
        && mx_match_search(token + MX_SHA256_LENGTH, MX_LOGIN_REGEX)) {
        return TRUE;
    }
    return FALSE;
}
