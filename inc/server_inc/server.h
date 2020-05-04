#pragma once

#include "../utils_inc/utils.h"

#define MX_LISTENQ 1024

int mx_tcp_listen(const char *serv, socklen_t *addr_len);
