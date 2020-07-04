#include "client.h"

void mx_msgcreate_box_energy(GtkWidget *box_status, t_gmsg *gmsg) {
    GtkWidget *box_energy = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    GtkWidget *img = gtk_image_new_from_icon_name("energy",
                                                  GTK_ICON_SIZE_MENU);
    gchar *wat_str = g_strdup_printf("%.2f Wt", gmsg->power);
    GtkWidget *value = gtk_label_new(wat_str);

    gtk_box_pack_start(GTK_BOX(box_energy), img, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box_energy), value, FALSE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box_status), box_energy, FALSE, TRUE, 0);
    gtk_widget_set_tooltip_text(box_energy, "energy spent on this message");
    gmsg->label_power = GTK_LABEL(value);
    g_free(wat_str);
}
