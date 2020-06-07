#include "utils.h"

/*
 * Wrapper of standart function setsockopt
 */
int mx_setsockopt(t_sockopt *sockopt) {
    if (setsockopt(sockopt->socket, sockopt->level, sockopt->option_name,
        sockopt->option_value, sockopt->option_len)) {
        mx_elogger(MX_LOG_FILE, LOGERR, "setsockopt\n");
    }
    return 0;
}
