#include "client.h"

t_gmsg *mx_get_gmsg_by_id(int msg_id, int room_id, GtkBuilder *builder) {
    t_groom *room = mx_get_groom_by_id(room_id, builder);
    GtkListBox *box = room->box_messages;
    GtkListBoxRow *row = NULL;
    t_gmsg *gmsg = NULL;
    bool flag = true;

    for (int i = 0; flag; i++) {
        row = gtk_list_box_get_row_at_index(box, i);
        if (row == NULL)
            flag = false;
        else {
            gmsg = (t_gmsg*)g_object_get_data(G_OBJECT(row), "gmsg");
            if (msg_id == gmsg->message_id)
                return gmsg;
        }
    }
    return NULL;
}

void mx_delete_row_msg(GtkListBoxRow *row, GtkBuilder *builder) {
    GObject *control = gtk_builder_get_object(builder, "btnbox_msg_ctrl");
    
    if (gtk_list_box_row_is_selected(row))
        gtk_widget_hide(GTK_WIDGET(control));
    gtk_widget_destroy(GTK_WIDGET(row));
}

void mx_gdel_msg(int msg_id, int room_id, GtkBuilder *builder) {
    t_gmsg *msg = mx_get_gmsg_by_id(msg_id, room_id, builder);

    mx_delete_row_msg(msg->row_msg, builder);
}

void mx_gupd_msg_text(int msg_id, int room_id,
                      char *text, GtkBuilder *builder) {
    t_gmsg *gmsg = mx_get_gmsg_by_id(msg_id, room_id, builder);

    mx_free((void **)&(gmsg->msg));
    gmsg->msg = mx_strdup(text);
    gtk_label_set_text(gmsg->label_text, gmsg->msg);
    gtk_widget_show_all(GTK_WIDGET(gmsg->label_text));
}
