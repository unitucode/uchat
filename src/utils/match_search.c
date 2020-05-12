#include "utils.h"

int mx_get_counts_of_digits(int number) {
    int count = (number == 0) ? 1 : 0;
    while (number != 0) {
        count++;
        number /= 10;
    }
    return count;
}

int mx_match_search(char *str, char *regex) {
    regex_t reg;
    int res;

    regcomp(&reg, regex, REG_EXTENDED);
    res = regexec(&reg, str, 0, NULL, 0);
    regfree(&reg);
    return res == 0;
}
