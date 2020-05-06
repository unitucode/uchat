#include "utils.h"

void mx_strdel(void **tds) {
    if (tds && *tds) {
        free(*tds);
        *tds = NULL;
    }
}
