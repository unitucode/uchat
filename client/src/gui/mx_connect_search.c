#include "client.h"

static void req_search_global_rooms(gchar *search_name, t_chat *chat) {
    t_dtp *dtp = mx_search_rooms_request(search_name);

    mx_send(chat->out, dtp);
    mx_free_request(&dtp);
    (void)chat;
}

void mx_start_search_room(GtkSearchEntry *sentry, t_chat *chat) {
    gchar *search_name = (gchar*)gtk_entry_get_text(GTK_ENTRY(sentry));
    t_filter_data *filter_data = mx_create_filter_data(search_name);

    mx_clear_global_search(chat->builder);
    mx_search_delim_set_visibility(chat->builder, TRUE);
    if (!strlen(search_name))
        mx_stop_search_room(NULL, NULL, chat->builder);
    else {
        mx_search_local_rooms(chat->builder, filter_data);
        req_search_global_rooms(search_name, chat);
    }
    mx_free_filter_data(filter_data);
}

void mx_connect_search(t_chat *chat) {
    GObject *sentry = gtk_builder_get_object(chat->builder, "sentry_rooms");

    g_signal_connect(GTK_SEARCH_ENTRY(sentry), "search-changed",
                     G_CALLBACK(mx_start_search_room), chat);
}
