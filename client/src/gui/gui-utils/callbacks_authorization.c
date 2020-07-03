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
    GObject *login = gtk_builder_get_object(builder, "entry_login_password");
    GObject *signup = gtk_builder_get_object(builder, "entry_signup_password");
    GObject *confirm = gtk_builder_get_object(builder, "entry_signup_confirm");

    mx_entry_set_icon_by_path(GTK_ENTRY(login), MX_IMG_EYE,
                              GTK_ENTRY_ICON_SECONDARY);
    mx_entry_set_icon_by_path(GTK_ENTRY(signup), MX_IMG_EYE,
                              GTK_ENTRY_ICON_SECONDARY);
    gtk_entry_set_visibility(GTK_ENTRY(login), FALSE);
    gtk_entry_set_visibility(GTK_ENTRY(signup), FALSE);
    gtk_entry_set_visibility(GTK_ENTRY(confirm), FALSE);
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
                      GdkEvent *event, gpointer *entry_second) {
    if (gtk_entry_get_visibility(entry)) {
        mx_entry_set_icon_by_path(entry, MX_IMG_EYE, icon_pos);
        gtk_entry_set_visibility(entry, FALSE);
        if (GTK_IS_ENTRY(entry_second))
            gtk_entry_set_visibility(GTK_ENTRY(entry_second), FALSE);
    }
    else { 
        mx_entry_set_icon_by_path(entry, MX_IMG_CLOSEDEYE, icon_pos);
        gtk_entry_set_visibility(entry, TRUE);
        if (GTK_IS_ENTRY(entry_second))
            gtk_entry_set_visibility(GTK_ENTRY(entry_second), TRUE);
    }
    (void)event;
}
