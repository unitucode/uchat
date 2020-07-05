#include "client.h"

t_gmsg *mx_get_gmsg_by_id(guint64 msg_id, guint64 room_id,
                          GtkBuilder *builder) {
    t_groom *room = mx_get_groom_by_id(room_id, builder);
    GtkListBox *box = NULL;
    GtkListBoxRow *row = NULL;
    t_gmsg *gmsg = NULL;
    gboolean flag = TRUE;

    if (!room)
        return NULL;
    box = room->box_messages;
    for (guint64 i = 0; flag; i++) {
        row = gtk_list_box_get_row_at_index(box, i);
        if (row == NULL)
            flag = FALSE;
        else {
            gmsg = (t_gmsg*)g_object_get_data(G_OBJECT(row), "gmsg");
            if (msg_id == gmsg->message_id)
                return gmsg;
        }
    }
    return NULL;
}

void mx_delete_row_msg(GtkListBoxRow *row, GtkBuilder *builder) {
    if (gtk_list_box_row_is_selected(row))
        mx_switch_room_header(builder, MX_ROOM_CTRL);
    gtk_widget_destroy(GTK_WIDGET(row));
}

void mx_gdel_msg(guint64 msg_id, guint64 room_id, GtkBuilder *builder) {
    t_gmsg *msg = mx_get_gmsg_by_id(msg_id, room_id, builder);
    t_groom *room = mx_get_groom_by_id(room_id, builder);

    if (msg && room) {
        room->uploaded--;
        mx_delete_row_msg(msg->row_msg, builder);
        mx_unselect_curr_room_messages(builder);
    }
}

void mx_gupd_msg_text(guint64 msg_id, guint64 room_id,
                      char *text, GtkBuilder *builder) {
    t_gmsg *gmsg = mx_get_gmsg_by_id(msg_id, room_id, builder);

    if (gmsg) {
        mx_free((void **)&(gmsg->msg));
        gmsg->msg = mx_strdup(text);
        gtk_label_set_markup(GTK_LABEL(gmsg->label_text),
                             mx_format_text(gmsg->msg));
        gtk_widget_show_all(GTK_WIDGET(gmsg->row_msg));
        mx_unselect_curr_room_messages(builder);
    }
}

void mx_gupd_msg_power(guint64 msg_id, guint64 room_id,
                       gdouble power, GtkBuilder *builder) {
    t_gmsg *gmsg = mx_get_gmsg_by_id(msg_id, room_id, builder);
    gchar *value = g_strdup_printf("%.2f Wt", power);

    if (gmsg) {
        gmsg->power = power;
        gtk_label_set_text(gmsg->label_power, value);
        gtk_widget_show_all(GTK_WIDGET(gmsg->row_msg));
        mx_unselect_curr_room_messages(builder);
        g_free(value);
    }
}
