#include "client.h"

void mx_entry_set_icon_by_path(GtkEntry *entry, gchar *path,
                               GtkEntryIconPosition icon_pos) {
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file(path, NULL);

    gtk_entry_set_icon_from_pixbuf(entry, icon_pos, pixbuf);
    g_object_unref(pixbuf);
}
