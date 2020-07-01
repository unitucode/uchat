#include "client.h"

GtkWidget *mx_msgcreate_eventbox() {
    GtkWidget *eventbox = gtk_event_box_new();

    gtk_widget_set_can_focus(eventbox, FALSE);
    return eventbox;
}

GtkWidget *mx_msgcreate_box_main(GtkWidget *eventbox, gboolean is_own) {
    GtkWidget *box_main = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    if (is_own)
        mx_widget_set_class(box_main, "main_own_msg_box");
    else
        mx_widget_set_class(box_main, "main_msg_box");
    gtk_container_add(GTK_CONTAINER(eventbox), GTK_WIDGET(box_main));
    return box_main;
}

void mx_msgcreate_box_info(GtkWidget *box_main, t_gmsg *gmsg,
                           gboolean is_own, t_chat *chat) {
    GtkWidget *box_info = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    if (is_own)
        mx_msgcreate_own_content(box_info, gmsg, chat);
    else
        mx_msgcreate_content(box_main, box_info, gmsg, chat);
    gtk_box_pack_end(GTK_BOX(box_main), box_info, FALSE, TRUE, 0);
    mx_msgcreate_label_time(box_info, gmsg, is_own);
}
