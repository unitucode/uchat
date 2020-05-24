#include "server.h"

/*
 * Gets IPv4 from sockaddr_in to client->ip
 * and port from sin->sin_port to client->port
 */
static void get_ipv4_info(t_client *client) {
    struct sockaddr_in *sin = (struct sockaddr_in*)client->cliaddr;

    if (!inet_ntop(AF_INET, &sin->sin_addr, client->ip, sizeof(client->ip))) {
        mx_logger(MX_LOG_FILE, LOGWAR, "IPv4 inet_ntop\n");
    }
    if (ntohs(sin->sin_port)) {
        snprintf(client->port, sizeof(client->port),
                 "%d", ntohs(sin->sin_port));
    }
    else {
        mx_logger(MX_LOG_FILE, LOGWAR, "port ntohs\n");
    }
}


/*
 * Gets IPv6 from sockaddr_in6->sin6_addr to client->ip
 * and port from sin6->sin6_port to client->port
 */
static void get_ipv6_info(t_client *client) {
    struct sockaddr_in6 *sin6 = (struct sockaddr_in6*)client->cliaddr;

    if (!inet_ntop(AF_INET6, &sin6->sin6_addr,
        client->ip, sizeof(client->ip))) {
        mx_logger(MX_LOG_FILE, LOGWAR, "IPv6 inet_ntop\n");
    }
    if (ntohs(sin6->sin6_port)) {
        snprintf(client->port, sizeof(client->port),
                 "%d", ntohs(sin6->sin6_port));
    }
    else {
        mx_logger(MX_LOG_FILE, LOGWAR, "port ntohs\n");
    }
}

/*
 * Gets clients ip and port
 */
void mx_get_client_info(t_client *client) {
    if (client->cliaddr->sa_family == AF_INET) {
        get_ipv4_info(client);    
    }
    else if (client->cliaddr->sa_family == AF_INET6) {
        get_ipv6_info(client);
    }
}
