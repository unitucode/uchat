/* 
* Login,
* password,
* cockie,
* message
*/

#include "utils.h"

void mx_free_msg_stract(t_msg_config *msg) {
    mx_strdel((void **)(&msg->message));
    mx_strdel((void **)(&msg->len));
    msg = NULL;
}

t_msg_config *mx_message_typing(int msg_type, char *message) {
    t_msg_config *msg = malloc(sizeof(t_msg_config));
    char str[1024];

    sprintf(str, "%c%s", msg_type, message);
    msg->message = strdup(str);
    sprintf(str, "%lu", strlen(message));
    msg->len = strdup(str);
    return msg;
}
