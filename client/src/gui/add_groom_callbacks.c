#include "client.h"

void mx_reset_addroom(GtkButton *btn, GtkBuilder *builder) {
    mx_clear_buffer_text("buffer_roomname", builder);
    (void)btn;
}

static void set_main_info_current_room_sett(GtkBuilder *builder,
                                            t_groom *groom) {
    GObject *name = gtk_builder_get_object(builder, "label_prefs_roomname");
    GObject *energy = gtk_builder_get_object(builder, "label_room_energy");
    GObject *go_down = gtk_builder_get_object(builder, "btn_go_down");
    gchar *value = g_strdup_printf("%.4f Wt", groom->power);

    gtk_widget_hide(GTK_WIDGET(go_down));
    gtk_label_set_text(GTK_LABEL(name), groom->room_name);
    gtk_label_set_text(GTK_LABEL(energy), value);
    g_free(value);
}

void mx_set_current_room_sett(GtkBuilder *builder) {
    t_groom *groom = mx_get_selected_groom(builder, MX_LOCAL_ROOMS);
    GObject *customer = gtk_builder_get_object(builder,
                                               "label_prefs_customer");
    GObject *desc = gtk_builder_get_object(builder, "buffer_room_desc");
    GObject *header_name = gtk_builder_get_object(builder,
                                                  "label_header_roomname");
    GObject *message_field = gtk_builder_get_object(builder, "msg_entry");

    if (groom) {
        gtk_widget_grab_focus(GTK_WIDGET(message_field));
        gtk_text_buffer_set_text(GTK_TEXT_BUFFER(desc), groom->desc, -1);
        gtk_label_set_text(GTK_LABEL(customer), groom->customer);
        gtk_label_set_text(GTK_LABEL(header_name), groom->room_name);
        mx_set_room_members(builder, groom);
        set_main_info_current_room_sett(builder, groom);
        mx_reset_select_count(groom);
    }
}

void mx_select_room(GtkWidget *event_box, GdkEventButton *event,
                    gpointer *user_data) {
    t_signal_data *data = g_object_get_data(G_OBJECT(event_box), "sigdata");
    GObject *btn_room_sett = gtk_builder_get_object(data->chat->builder,
                                                    "btn_show_room_sett");
    if (mx_is_same_groom(data->groom, data->chat->builder)) {
        mx_reset_messege_room(data->groom, data->chat->builder);
        gtk_stack_set_visible_child(data->groom->stack_msg,
                                    GTK_WIDGET(data->groom->page));
        gtk_list_box_select_row(data->groom->box_rooms,
                                data->groom->row_room);
        mx_set_current_room_sett(data->chat->builder);
        mx_set_room_widgets_visibility(data->chat->builder, TRUE);
        mx_widget_remove_class(GTK_WIDGET(data->groom->label_name),
                            "has-messages");
        if (!g_strcmp0(data->chat->login, data->groom->customer))
            mx_widget_set_visibility(GTK_WIDGET(btn_room_sett), TRUE);
        else
            mx_widget_set_visibility(GTK_WIDGET(btn_room_sett), FALSE);
    }
    (void)event;
    (void)user_data;
}

void mx_show_join_to_room(GtkWidget *event_box, GdkEventButton *event,
                          gpointer *user_data) {
    t_signal_data *data = g_object_get_data(G_OBJECT(event_box), "sigdata");
    t_groom *lgroom = mx_get_selected_groom(data->chat->builder,
                                            MX_LOCAL_ROOMS);
    GObject *label_name = gtk_builder_get_object(data->chat->builder,
                                                 "label_join_roomname");

    gtk_list_box_select_row(data->groom->box_rooms, data->groom->row_room);
    mx_reset_messege_room(lgroom, data->chat->builder);
    mx_widget_switch_visibility_by_name(data->chat->builder,
                                        "dialog_join_to_room");
    gtk_label_set_text(GTK_LABEL(label_name), data->groom->room_name);
    (void)event;
    (void)user_data;
}
