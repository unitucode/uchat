#include "utils.h"

bool mx_isvalid_login(char *login) {
    return mx_match_search(login, MX_LOGIN_REGEX);
}

bool mx_isvalid_hash(char *hash) {
    return mx_match_search(hash, MX_HASH_REGEX);
}

bool mx_isvalid_token(char *token) {
    if (mx_match_nsearch(token, MX_HASH_REGEX, MX_MD5_BUF_SIZE)
        && mx_match_search(token + MX_MD5_BUF_SIZE, MX_LOGIN_REGEX)) {
        return true;
    }
    return false;
}
