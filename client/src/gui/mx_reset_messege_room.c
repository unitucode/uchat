#include "client.h"

void mx_hide_msg_editing(GtkButton *btn, GtkBuilder *builder) {
    GObject *box_editing = gtk_builder_get_object(builder, "box_editing_msg");
    GObject *btn_apply = gtk_builder_get_object(builder, "btn_edit_msg_apply");
    GObject *btn_send = gtk_builder_get_object(builder, "btn_send_msg");

    gtk_widget_hide(GTK_WIDGET(box_editing));
    gtk_widget_hide(GTK_WIDGET(btn_apply));
    gtk_widget_show(GTK_WIDGET(btn_send));
    (void)btn;
}

void mx_hide_msg_ctrl(GtkBuilder *builder) {
    GObject *control = gtk_builder_get_object(builder, "btnbox_msg_ctrl");

    gtk_widget_hide(GTK_WIDGET(control));
}

void mx_unselect_curr_room_messages(t_groom *groom) {
    if (groom)
        gtk_list_box_unselect_all(groom->box_messages);
}

void mx_reset_messege_room(t_groom *new_selected, GtkBuilder *builder) {
    t_groom *groom = mx_get_selected_groom(builder);

    if (groom && new_selected->id != groom->id) {
        mx_hide_msg_ctrl(builder);
        mx_unselect_curr_room_messages(groom);
        mx_hide_msg_editing(NULL, builder);
    }
}
