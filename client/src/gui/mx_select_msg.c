#include "client.h"

gint select_all;
gint select_own;
gint select_another;
gint select_notedit;

void mx_reset_select_count() {
    select_own = 0;
    select_another = 0;
    select_notedit = 0;
    select_all = 0;
}

static void select_row(t_groom *groom, t_gmsg *gmsg,
                       GtkListBoxRow *row, gboolean is_own) {
    gtk_list_box_select_row(GTK_LIST_BOX(groom->box_messages),
                            GTK_LIST_BOX_ROW(row));

    if (gmsg->type == DB_STICKER)
        select_notedit++;
    if (is_own)
        select_own++;
    else
        select_another++;
    (void)groom;
}

static void unselect_row(t_groom *groom, t_gmsg *gmsg,
                         GtkListBoxRow *row, gboolean is_own) {
    gtk_list_box_unselect_row(GTK_LIST_BOX(groom->box_messages),
                            GTK_LIST_BOX_ROW(row));

    if (gmsg->type == DB_STICKER)
        select_notedit--;
    if (is_own)
        select_own--;
    else
        select_another--;
    (void)groom;
}

void mx_select_msg(gpointer *eventbox, gpointer *event, t_signal_data *data) {
    t_groom *groom = mx_get_selected_groom(data->chat->builder,
                                           MX_LOCAL_ROOMS);
    t_gmsg *gmsg = (t_gmsg*)g_object_get_data(G_OBJECT(data->row_msg), "gmsg");
    gboolean is_own = !g_strcmp0(data->chat->login, gmsg->login);

    if (!mx_widget_is_visible("box_editing_msg", data->chat->builder)) {
        if (gtk_list_box_row_is_selected(GTK_LIST_BOX_ROW(data->row_msg)))
            unselect_row(groom, gmsg, data->row_msg, is_own);
        else
            select_row(groom, gmsg, data->row_msg, is_own);
    }
    select_all = select_own + select_another;
    if (select_all > 0) {
        mx_switch_room_header(data->chat->builder, MX_MSG_CTRL);
        if (select_notedit > 0 || select_another > 0 || select_all > 1) {
            mx_widget_set_visibility_by_name(data->chat->builder,
                                             "btn_edit_msg", FALSE);
        }
        else {
            mx_widget_set_visibility_by_name(data->chat->builder,
                                             "btn_edit_msg", TRUE);
        }
    }
    else
        mx_switch_room_header(data->chat->builder, MX_ROOM_CTRL);
    (void)eventbox;
    (void)event;
}


// void mx_select_msg(gpointer *eventbox, gpointer *event, t_signal_data *data) {
//     t_groom *groom = mx_get_selected_groom(data->chat->builder,
//                                            MX_LOCAL_ROOMS);
//     GList *rows = NULL;

//     if (!mx_widget_is_visible("box_editing_msg", data->chat->builder)) {
//         if (gtk_list_box_row_is_selected(GTK_LIST_BOX_ROW(data->row_msg))) {
//             gtk_list_box_unselect_row(GTK_LIST_BOX(groom->box_messages),
//                                     GTK_LIST_BOX_ROW(data->row_msg));
//             rows = gtk_list_box_get_selected_rows(groom->box_messages);
//             if (!rows)
//                 mx_switch_room_header(data->chat->builder, MX_ROOM_CTRL);
//         }
//         else {
//             gtk_list_box_select_row(GTK_LIST_BOX(groom->box_messages),
//                                     GTK_LIST_BOX_ROW(data->row_msg));
//             mx_switch_room_header(data->chat->builder, MX_MSG_CTRL);
//             rows = gtk_list_box_get_selected_rows(groom->box_messages);
//         }
//     }
//     if (g_list_length(rows) <= 1) {
//         mx_widget_set_visibility_by_name(data->chat->builder,
//                                          "btn_edit_msg", TRUE);
//     }
//     else {
//         mx_widget_set_visibility_by_name(data->chat->builder,
//                                          "btn_edit_msg", FALSE);
//     }
//     g_list_free(rows);
//     (void)eventbox;
//     (void)event;
// }
