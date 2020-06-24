#include "client.h"

void mx_hide_msg_editing(GtkButton *btn, GtkBuilder *builder) {
    GObject *box_editing = gtk_builder_get_object(builder, "box_editing_msg");
    GObject *btn_apply = gtk_builder_get_object(builder, "btn_edit_msg_apply");
    GObject *btn_send = gtk_builder_get_object(builder, "btn_send_msg");

    gtk_widget_hide(GTK_WIDGET(box_editing));
    gtk_widget_hide(GTK_WIDGET(btn_apply));
    gtk_widget_show(GTK_WIDGET(btn_send));
    mx_clear_buffer_text("buffer_message", builder);
    (void)btn;
}

/*
 * Unselec all messages in current room
 */
void mx_unselect_curr_room_messages(GtkBuilder *builder) {
    t_groom *groom = mx_get_selected_groom(builder, MX_LOCAL_ROOMS);

    if (groom)
        gtk_list_box_unselect_all(groom->box_messages);
}

void mx_reset_messege_room(t_groom *new_selected, GtkBuilder *builder) {
    t_groom *groom = mx_get_selected_groom(builder, MX_LOCAL_ROOMS);

    if (groom && new_selected->id != groom->id) {
        mx_switch_room_header(builder, MX_ROOM_CTRL);
        mx_unselect_curr_room_messages(builder);
        mx_hide_msg_editing(NULL, builder);
    }
}
