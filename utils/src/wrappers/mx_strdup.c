#include "utils.h"

char *mx_strdup(char *str) {
    if (!str)
        return strdup("");
    else
        return strdup(str);
}
