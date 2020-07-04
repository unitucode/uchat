#include "client.h"

static GtkWidget *create_image_btn(gchar *filename) {
    GtkWidget *btn = NULL;

    if (g_file_test(filename, G_FILE_TEST_EXISTS)) {
        if (mx_is_file_image(filename) || mx_is_file_animation(filename))
            btn = gtk_button_new_from_icon_name("image", GTK_ICON_SIZE_DND);
        else
            btn = gtk_button_new_from_icon_name("document", GTK_ICON_SIZE_DND);
    }
    else
        btn = gtk_button_new_from_icon_name("download", GTK_ICON_SIZE_DND);
    return btn;
}

void mx_msgcreate_file(GtkWidget *box_info, t_gmsg *gmsg,
                       gboolean is_own, t_chat *chat) {
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gchar *file = mx_get_filename(gmsg->msg);
    GtkWidget *filename = gtk_label_new(file);
    GtkWidget *btn = create_image_btn(gmsg->msg);

    mx_widget_set_class(box, "file-button");
    gtk_widget_set_can_focus(btn, FALSE);
    g_object_set_data(G_OBJECT(btn), "gmsg", gmsg);
    g_signal_connect(btn, "clicked", G_CALLBACK(mx_open_files_dir), chat);
    gtk_label_set_line_wrap(GTK_LABEL(filename), TRUE);
    gtk_label_set_line_wrap_mode(GTK_LABEL(filename), PANGO_WRAP_WORD_CHAR);
    gtk_box_pack_start(GTK_BOX(box), btn, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), filename, FALSE, TRUE, 0);
    if (is_own)
        gtk_box_pack_end(GTK_BOX(box_info), box, FALSE, TRUE, 0);
    else
        gtk_box_pack_start(GTK_BOX(box_info), box, FALSE, TRUE, 0);
}
