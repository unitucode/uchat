#include "client.h"

static void show_ban_member(GObject *btn, GtkBuilder *builder) {
    GObject *dialog = gtk_builder_get_object(builder, "dialog_ban_member");
    GObject *btn_ban = gtk_builder_get_object(builder, "btn_ban");
    GObject *label_member = gtk_builder_get_object(builder,
                                                   "label_ban_login");

    g_object_set_data(btn_ban, "member_id",
                      g_object_get_data(btn, "member_id"));
    mx_widget_set_visibility(GTK_WIDGET(dialog), TRUE);
    gtk_label_set_text(GTK_LABEL(label_member),
                       g_object_get_data(btn, "member_login"));
}

void mx_add_to_sett_members(gint *key,
                            gchar *value, GtkBuilder *builder) {
    t_groom *groom = mx_get_selected_groom(builder, MX_LOCAL_ROOMS);

    if (g_strcmp0(groom->customer, value)) {
        GObject *listbox = gtk_builder_get_object(builder,
                                                "listbox_sett_members");
        GtkWidget *box_member = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
        GtkWidget *name = gtk_label_new(value);
        GtkWidget *btn = gtk_button_new_with_label("Ban");

        gtk_widget_set_size_request(box_member, -1, 40);
        gtk_box_pack_start(GTK_BOX(box_member), name, FALSE, FALSE, 0);
        gtk_box_pack_end(GTK_BOX(box_member), btn, FALSE, FALSE, 0);
        gtk_list_box_insert(GTK_LIST_BOX(listbox), box_member, -1);
        gtk_widget_show_all(GTK_WIDGET(listbox));
        g_object_set_data(G_OBJECT(btn), "member_id", key);
        g_object_set_data(G_OBJECT(btn), "member_login", value);
        g_signal_connect(btn, "clicked", G_CALLBACK(show_ban_member),
                         builder);
    }
    (void)key;
}

static void show_user_info(GObject *btn, GtkBuilder *builder) {
    GObject *popup = gtk_builder_get_object(builder, "popup_user_info");

    g_object_set_data(popup, "member_id",
                      g_object_get_data(btn, "member_id"));
    mx_widget_set_visibility(GTK_WIDGET(popup), TRUE);
}

void mx_add_to_info_members(gint *key,
                            gchar *value, GtkBuilder *builder) {
    GObject *listbox = gtk_builder_get_object(builder,
                                              "listbox_info_members");
    GtkWidget *box_member = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *name = gtk_label_new(value);
    GtkWidget *btn = gtk_button_new_with_label("Info");

    gtk_widget_set_size_request(box_member, -1, 40);
    gtk_box_pack_start(GTK_BOX(box_member), name, FALSE, FALSE, 0);
    gtk_box_pack_end(GTK_BOX(box_member), btn, FALSE, FALSE, 0);
    gtk_list_box_insert(GTK_LIST_BOX(listbox), box_member, -1);
    gtk_widget_show_all(GTK_WIDGET(listbox));
    g_object_set_data(G_OBJECT(btn), "member_id", key);
    g_signal_connect(btn, "clicked", G_CALLBACK(show_user_info), builder);
    (void)key;
}
