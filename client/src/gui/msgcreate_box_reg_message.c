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

static void mx_msgcreate_box_status(GtkWidget *box_info,
                                    t_gmsg *gmsg, gboolean is_own) {
    GtkWidget *box_status = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    if (is_own)
        gtk_box_pack_end(GTK_BOX(box_info), box_status, FALSE, TRUE, 0);
    else
        gtk_box_pack_start(GTK_BOX(box_info), box_status, FALSE, TRUE, 0);
    gtk_widget_set_valign(box_status, GTK_ALIGN_END);
    mx_msgcreate_box_energy(box_status, gmsg);
    mx_msgcreate_label_time(box_status, gmsg, is_own);
}

void mx_msgcreate_box_info(GtkWidget *box_main, t_gmsg *gmsg,
                           gboolean is_own, t_chat *chat) {
    GtkWidget *box_info = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    if (is_own)
        mx_msgcreate_own_content(box_info, gmsg, chat);
    else
        mx_msgcreate_content(box_main, box_info, gmsg, chat);
    gtk_box_pack_end(GTK_BOX(box_main), box_info, FALSE, TRUE, 0);
    mx_msgcreate_box_status(box_info, gmsg, is_own);
}
