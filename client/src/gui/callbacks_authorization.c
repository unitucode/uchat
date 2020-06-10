#include "client.h"

void mx_set_sensetive_confirm(GtkEntryBuffer *buff, guint pos, gchar *chars,
                              guint n_chars, GtkEntry *entry) {
    char *buffer = (char*)gtk_entry_buffer_get_text(buff);

    if (strlen(buffer))
        gtk_widget_set_sensitive(GTK_WIDGET(entry), 1);
    (void)buff;
    (void)pos;
    (void)chars;
    (void)n_chars;
}

void mx_set_unsensetive_confirm(GtkEntryBuffer *buff, guint pos,
                                guint n_chars, GtkEntry *entry) {
    char *buffer = (char*)gtk_entry_buffer_get_text(buff);

    if (strlen(buffer) == 0)
        gtk_widget_set_sensitive(GTK_WIDGET(entry), 0);
    (void)buff;
    (void)pos;
    (void)n_chars;
}

void mx_reset_auth(GtkNotebook *note, GtkWidget *page,
                   guint page_num, GtkBuilder *builder) {
    mx_clear_buffer_text("buffer_login", builder);
    mx_clear_buffer_text("buffer_password", builder);
    mx_clear_buffer_text("buffer_password_confirm", builder);
    mx_clear_label_by_name("label_autherror_login", builder);
    mx_clear_label_by_name("label_autherror_signup", builder);
    (void)note;
    (void)page;
    (void)page_num;
}

void mx_close_auth(GtkButton *btn, GtkDialog *dialog) {
    gtk_widget_destroy(GTK_WIDGET(dialog));
    (void)btn;
}

void mx_show_password(GtkEntry *entry, GtkEntryIconPosition icon_pos,
                      GdkEvent *event, GtkBuilder *builder) {
    GtkEntry *pixbuf_pass = GTK_ENTRY(gtk_builder_get_object(builder,
                                                             "pixbuf_pass"));

    if (gtk_entry_get_visibility(entry)) {
        GdkPixbuf *vis = gtk_entry_get_icon_pixbuf(pixbuf_pass,
                                                   GTK_ENTRY_ICON_PRIMARY);

        gtk_entry_set_icon_from_pixbuf(entry, icon_pos, vis);
        gtk_entry_set_visibility(entry, false);
    }
    else { 
        GdkPixbuf *unvis = gtk_entry_get_icon_pixbuf(pixbuf_pass,
                                                     GTK_ENTRY_ICON_SECONDARY);
        gtk_entry_set_icon_from_pixbuf(entry, icon_pos, unvis);
        gtk_entry_set_visibility(entry, true);
    }
    (void)event;
}
