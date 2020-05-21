#include "utils.h"

bool mx_match_nsearch(char *str, char *regex, size_t size) {
    char buf[size + 1];
    regex_t reg;
    int res;

    buf[size] = 0;
    strncpy(buf, str, size);
    regcomp(&reg, regex, REG_EXTENDED);
    res = regexec(&reg, buf, 0, NULL, 0);
    regfree(&reg);
    return !res;
}

bool mx_match_search(char *str, char *regex) {
    regex_t reg;
    int res;

    regcomp(&reg, regex, REG_EXTENDED);
    res = regexec(&reg, str, 0, NULL, 0);
    regfree(&reg);
    return !res;
}
