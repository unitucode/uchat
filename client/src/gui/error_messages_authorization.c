#include "client.h"

void mx_err_auth_data_handler(GtkBuilder *builder) {
    GObject *label = gtk_builder_get_object(builder,
                                            "label_autherror_login");

    gtk_label_set_text(GTK_LABEL(label), MX_ERRMSG_INCCRDATA);
}

void mx_err_user_exist_handler(GtkBuilder *builder) {
    GObject *label = gtk_builder_get_object(builder,
                                            "label_autherror_signup");

    gtk_label_set_text(GTK_LABEL(label), MX_ERRMSG_USEREXIST);
}

void mx_err_cli_exist_handler(GtkBuilder *builder) {
    GObject *label = gtk_builder_get_object(builder,
                                            "label_autherror_login");

    gtk_label_set_text(GTK_LABEL(label), MX_ERRMSG_CLIEXIST);
}
