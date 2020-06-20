#include "client.h"

GtkWidget *mx_create_reg_message_row(t_gmsg *gmsg, gboolean is_own) {
    GtkWidget *eventbox = mx_msgcreate_eventbox();
    GtkWidget *box_main = mx_msgcreate_box_main(eventbox, is_own);

    mx_msgcreate_box_info(box_main, gmsg, is_own);
    return eventbox;
}
