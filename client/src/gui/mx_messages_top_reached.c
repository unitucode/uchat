#include "client.h"

static void delete_older_message(t_groom *groom) {
    GtkListBoxRow *row = gtk_list_box_get_row_at_index(groom->box_messages, 0);

    gtk_widget_destroy(GTK_WIDGET(row));
}

static void my_gtk_post_top(GtkPositionType pos, t_chat *chat,
                            t_groom *groom, GtkScrolledWindow *scroll) {
    GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(scroll);
    GtkListBoxRow *glb = gtk_list_box_get_row_at_index(groom->box_messages, 0);
    t_gmsg *msg = (t_gmsg*)g_object_get_data(G_OBJECT(glb), "gmsg");
    t_dtp *get_old = mx_old_msgs_request(msg->date, groom->id);

    if (pos == GTK_POS_TOP && !chat->upl_old_msgs) {
        if (!gtk_list_box_get_row_at_index(groom->box_messages, 0))
            return;
        mx_send(chat->out, get_old);
        mx_free_request(&get_old);
        chat->upl_old_msgs = TRUE;
    }
    if (pos == GTK_POS_TOP)
        gtk_adjustment_set_value(adj, gtk_adjustment_get_value(adj) + 1);
}

void mx_box_messages_reached(GtkScrolledWindow *scroll,
                             GtkPositionType pos, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, MX_LOCAL_ROOMS);

    my_gtk_post_top(pos, chat, groom, scroll);
    if (pos == GTK_POS_BOTTOM) {
        chat->upl_old_msgs = TRUE;
        while (groom->uploaded > MX_BUF_MSGS) {
            GtkRequisition req;
            GtkRequisition req2;
            GtkAdjustment *adj = gtk_scrolled_window_get_vadjustment(scroll);

            gtk_widget_get_preferred_size(GTK_WIDGET(gtk_list_box_get_row_at_index(groom->box_messages, 0)), &req, &req2);
            delete_older_message(groom);
            gtk_adjustment_set_upper(adj, gtk_adjustment_get_upper(adj)
                                           - req2.height);
            gtk_adjustment_set_value(adj, gtk_adjustment_get_upper(adj)
                                           - gtk_adjustment_get_page_size(adj));
            groom->uploaded--;
        }
        chat->upl_old_msgs = FALSE;
    }
}
