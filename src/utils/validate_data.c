#include "utils.h"

bool mx_isvalid_login(char *login) {
    return mx_match_search(login, MX_LOGIN_REGEX);
}

bool mx_isvalid_hash(char *hash) {
    return mx_match_search(hash, MX_HASH_REGEX);
}
