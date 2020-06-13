#include "client.h"

GtkWidget *mx_create_message_row(t_gmsg *msg) {
    GtkWidget  *event = gtk_event_box_new();

    GtkWidget *label_txt = gtk_label_new(msg->msg);
    gtk_label_set_xalign(GTK_LABEL(label_txt), 0.03);
    GtkWidget *main_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_end(GTK_BOX(main_box), label_txt, true, true, 0);

    PangoAttrList *attr_list = pango_attr_list_new();
    PangoAttribute *attr = pango_attr_weight_new(PANGO_WEIGHT_HEAVY);
    pango_attr_list_insert(attr_list, attr);
    GtkWidget *label_name = gtk_label_new(msg->login);
    gtk_label_set_xalign(GTK_LABEL(label_name), 0.03);
    GtkWidget *label_time = gtk_label_new("13:07");
    gtk_label_set_xalign(GTK_LABEL(label_time), 0.97);
    gtk_label_set_attributes(GTK_LABEL(label_name), attr_list);
    pango_attr_list_unref(attr_list);
    gtk_widget_set_tooltip_text(label_time, "24.05.2020    13:37");
    GtkWidget *info_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(info_box), label_name, true, true, 0);
    gtk_box_pack_end(GTK_BOX(info_box), label_time, true, true, 0);
    gtk_box_pack_start(GTK_BOX(main_box), info_box, true, true, 0);

    gtk_container_add(GTK_CONTAINER(event), GTK_WIDGET(main_box));
    return event;
}
