#include "client.h"

void mx_errmsg_wrong_authdata(GtkBuilder *builder) {
    GObject *label = gtk_builder_get_object(builder,
                                            "label_autherror_login");

    gtk_label_set_text(GTK_LABEL(label), MX_ERRMSG_INCCRDATA);
}

void mx_errmsg_user_exist(GtkBuilder *builder) {
    GObject *label = gtk_builder_get_object(builder,
                                            "label_autherror_signup");

    gtk_label_set_text(GTK_LABEL(label), MX_ERRMSG_USEREXIST);
}
