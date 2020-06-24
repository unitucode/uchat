#include "client.h"

void mx_box_messages_reached(GtkScrolledWindow *scroll,
                             GtkPositionType pos, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, MX_LOCAL_ROOMS);

    if (pos == GTK_POS_TOP && !chat->upl_old_msgs) {
        t_gmsg *msg = (t_gmsg*)g_object_get_data(G_OBJECT(gtk_list_box_get_row_at_index(groom->box_messages, 0)), "gmsg");
        t_dtp *get_old = mx_old_msgs_request(msg->date, groom->id);

        mx_send(chat->out, get_old);
        mx_free_request(&get_old);
        chat->upl_old_msgs = true;
    }
    if (pos == GTK_POS_TOP) {
        GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(scroll);

        gtk_adjustment_set_value(adj, gtk_adjustment_get_value(adj) + 1);
    }
    if (pos == GTK_POS_BOTTOM) {
        chat->upl_old_msgs = true;
        for (guint i = 0; i < groom->uploaded; i++) {
            g_message("delete message here mx_messages_top_reached.c\n");
        }
        chat->upl_old_msgs = false;
    }
    (void)scroll;
}
