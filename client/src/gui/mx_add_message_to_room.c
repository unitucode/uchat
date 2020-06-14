#include "client.h"

// SIGNAL-HANDLERS
void mx_select_msg(GtkWidget *widget, GdkEventButton *event,
                   t_signal_data *data) {
    t_groom *groom = mx_get_selected_groom(data->builder);

    if (gtk_list_box_row_is_selected(GTK_LIST_BOX_ROW(data->row_msg))) {
        mx_switch_room_header(data->builder, MX_ROOM_CTRL);
        gtk_list_box_unselect_row(GTK_LIST_BOX(groom->box_messages),
                                  GTK_LIST_BOX_ROW(data->row_msg));
    }
    else {
        mx_switch_room_header(data->builder, MX_MSG_CTRL);
        gtk_list_box_select_row(GTK_LIST_BOX(groom->box_messages),
                                GTK_LIST_BOX_ROW(data->row_msg));
    }
    (void)widget;
    (void)event;
}
//==============================

static void add_message_row(t_gmsg *msg, GtkBuilder *builder) {
    GtkWidget *row = gtk_list_box_row_new();
    GtkWidget *event = mx_create_message_row(msg);
    t_groom *room = mx_get_groom_by_id(msg->room_id, builder);
    GtkListBox *box = room->box_messages;
    t_signal_data *data = NULL;

    data = mx_create_sigdata(builder, NULL, GTK_LIST_BOX_ROW(row));

    msg->row_msg = GTK_LIST_BOX_ROW(row);
    gtk_container_add(GTK_CONTAINER(row), event);
    g_signal_connect(event, "button_press_event",
                     G_CALLBACK(mx_select_msg), data);
    room->is_updated = true;
    gtk_list_box_insert(box, row, -1);
    gtk_list_box_row_changed(room->row_room);
    room->is_updated = false;
    gtk_widget_show_all(GTK_WIDGET(box));
    g_object_set_data_full(G_OBJECT(row), "gmsg", msg,
                           (GDestroyNotify)mx_delete_gmsg);
    g_object_set_data_full(G_OBJECT(event), "sigdata", data,
                           (GDestroyNotify)mx_free_sigdata);
}

void mx_add_message_to_room(t_gmsg *msg, GtkBuilder *builder) {
    add_message_row(msg, builder);
}
