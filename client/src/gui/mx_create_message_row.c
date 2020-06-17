#include "client.h"

void mx_msgcreate_label_login(GtkWidget *box_main, t_gmsg *gmsg) {
    GtkWidget *label_login = gtk_label_new(gmsg->login);

    gtk_box_pack_start(GTK_BOX(box_main), label_login, FALSE, FALSE, 0);
    gtk_widget_set_halign(label_login, GTK_ALIGN_START);
}

void mx_msgcreate_label_text(GtkWidget *box_info, t_gmsg *gmsg) {
    GtkWidget *label_text = gtk_label_new(NULL);

    gtk_box_pack_start(GTK_BOX(box_info), label_text, FALSE, FALSE, 0);
    gtk_label_set_xalign(GTK_LABEL(label_text), 0.00);
    gtk_widget_set_halign(label_text, GTK_ALIGN_START);
    gtk_label_set_line_wrap(GTK_LABEL(label_text), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(label_text), PANGO_WRAP_WORD_CHAR);
    gtk_label_set_text(GTK_LABEL(label_text), gmsg->msg);
    gmsg->label_text = GTK_LABEL(label_text);
}

void mx_msgcreate_label_time(GtkWidget *box_info, t_gmsg *gmsg) {
    GtkWidget *label_time = gtk_label_new(NULL);

    gtk_box_pack_start(GTK_BOX(box_info), label_time, FALSE, TRUE, 0);
    gtk_widget_set_halign(label_time, GTK_ALIGN_START);
    gtk_label_set_text(GTK_LABEL(label_time), "13:07");
    gtk_widget_set_tooltip_text(label_time, "24.05.2020    13:37");
    (void)gmsg;
}

// MAIN CREATING
static GtkWidget *create_eventbox() {
    GtkWidget *eventbox = gtk_event_box_new();

    gtk_widget_set_can_focus(eventbox, FALSE);
    return eventbox;
}

static GtkWidget *create_box_main(GtkWidget *eventbox) {
    GtkWidget *box_main = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

    gtk_container_add(GTK_CONTAINER(eventbox), GTK_WIDGET(box_main));
    return box_main;
}

static void create_box_info(GtkWidget *box_main, t_gmsg *gmsg) {
    GtkWidget *box_info = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    gtk_widget_set_size_request(box_main, 100, -1);
    gtk_box_pack_end(GTK_BOX(box_main), box_info, FALSE, TRUE, 0);
    mx_msgcreate_label_login(box_main, gmsg);
    mx_msgcreate_label_text(box_info, gmsg);
    mx_msgcreate_label_time(box_info, gmsg);
}

GtkWidget *mx_create_message_row(t_gmsg *msg) {
    GtkWidget  *eventbox = create_eventbox();
    GtkWidget *box_main = create_box_main(eventbox);
    create_box_info(box_main, msg);

    return eventbox;
}
