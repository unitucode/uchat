#include "client.h"

void mx_hide_msg_editing(GtkButton *btn, GtkBuilder *builder) {
    GObject *box_editing = gtk_builder_get_object(builder, "box_editing_msg");
    GObject *btn_apply = gtk_builder_get_object(builder, "btn_edit_msg_apply");
    GObject *btn_send = gtk_builder_get_object(builder, "btn_send_msg");
    GObject *btn_stick = gtk_builder_get_object(builder, "btn_choose_sticker");

    gtk_widget_hide(GTK_WIDGET(box_editing));
    gtk_widget_hide(GTK_WIDGET(btn_apply));
    gtk_widget_show(GTK_WIDGET(btn_send));
    gtk_widget_show(GTK_WIDGET(btn_stick));
    mx_clear_buffer_text("buffer_message", builder);
    (void)btn;
}

/*
 * Unselect all messages in current room
 */
void mx_unselect_curr_room_messages(GtkBuilder *builder) {
    t_groom *groom = mx_get_selected_groom(builder, MX_LOCAL_ROOMS);

    if (groom) {
        gtk_list_box_unselect_all(groom->box_messages);
        mx_reset_select_count(groom);
        mx_hide_msg_editing(NULL, builder);
    }
}

void mx_reset_room_for_search(GtkBuilder *builder) {
    mx_switch_room_header(builder, MX_ROOM_CTRL);
    mx_unselect_curr_room_messages(builder);
    mx_hide_msg_editing(NULL, builder);
}

void mx_reset_messege_room(t_groom *new_selected, GtkBuilder *builder) {
    t_groom *groom = mx_get_selected_groom(builder, MX_LOCAL_ROOMS);

    if (groom && (!new_selected || new_selected->id != groom->id)) {
        mx_reset_room_for_search(builder);
        mx_stop_search_message(NULL, NULL, builder);
    }
}
