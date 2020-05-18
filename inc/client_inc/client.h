#pragma once

#include "utils.h"
#include <sqlite3.h>

int mx_tcp_connect(const char *host, const char *serv);
void mx_signup(SSL *ssl);
void mx_login(SSL *ssl);
