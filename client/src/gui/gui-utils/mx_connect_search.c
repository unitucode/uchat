#include "client.h"

void mx_connect_search(t_chat *chat) {
    GObject *sentry_rooms = gtk_builder_get_object(chat->builder,
                                                   "sentry_rooms");
    GObject *sentry_messages = gtk_builder_get_object(chat->builder,
                                                      "sentry_messages");
    GObject *sentry_members = gtk_builder_get_object(chat->builder,
                                                     "sentry_members");

    g_signal_connect(GTK_SEARCH_ENTRY(sentry_rooms), "search-changed",
                     G_CALLBACK(mx_start_search_room), chat);
    g_signal_connect(GTK_SEARCH_ENTRY(sentry_messages), "search-changed",
                     G_CALLBACK(mx_start_search_msgs), chat);
    g_signal_connect(GTK_SEARCH_ENTRY(sentry_members), "search-changed",
                     G_CALLBACK(mx_start_search_members), chat);
}
