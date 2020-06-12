#include "client.h"

typedef struct s_message {
    t_gmsg *msg;
    GtkBuilder *builder;
    GtkWidget *row_msg;
}   t_message;

// SIGNAL-HANDLERS
void mx_select_msg(GtkWidget *widget, GdkEventButton *event, t_message *msg) {
    GObject *control = gtk_builder_get_object(msg->builder, "btnbox_msg_ctrl");
    t_groom *groom = mx_get_selected_groom(msg->builder);

    if (gtk_list_box_row_is_selected(GTK_LIST_BOX_ROW(msg->row_msg))) {
        gtk_widget_set_visible(GTK_WIDGET(control), false);
        gtk_list_box_unselect_row(GTK_LIST_BOX(groom->box_messages),
                                  GTK_LIST_BOX_ROW(msg->row_msg));
    }
    else {
        gtk_widget_set_visible(GTK_WIDGET(control), true);
        gtk_list_box_select_row(GTK_LIST_BOX(groom->box_messages),
                                GTK_LIST_BOX_ROW(msg->row_msg));
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

    t_message *message = (t_message*)malloc(sizeof(t_message));
    message->builder = builder;
    message->msg = msg;
    message->row_msg = row;

    gtk_container_add(GTK_CONTAINER(row), event);
    g_signal_connect(event, "button_press_event",
                     G_CALLBACK(mx_select_msg), message);
    room->is_updated = true;
    gtk_list_box_insert(box, row, -1);
    gtk_list_box_row_changed(room->row_room);
    room->is_updated = false;
    gtk_widget_show_all(GTK_WIDGET(box));
}

void mx_add_message_to_room(t_gmsg *msg, GtkBuilder *builder) {
    add_message_row(msg, builder);
}
