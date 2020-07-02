#include "client.h"

void mx_msgcreate_box_energy(GtkWidget *box_status, t_gmsg *gmsg) {
    GtkWidget *box_energy = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);

    gtk_box_pack_end(GTK_BOX(box_status), box_energy, FALSE, TRUE, 0);
}
