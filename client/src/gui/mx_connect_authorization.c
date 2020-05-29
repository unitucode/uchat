#include "client.h"

void mx_errmsg_wrong_authdata(GtkBuilder *builder) {
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder,
                                                       "label_autherror"));

    gtk_label_set_text(label, "The email or password inccorect");
}

static bool is_valid_auth_data(char *login, char *pass, GtkBuilder *builder) {
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder,
                                                       "label_autherror"));

    if (*login == '\0' || *pass == '\0') {
        gtk_label_set_text(label, "Please, enter login and password");
        return false;
    }
    else if (!mx_match_search(login, MX_LOGIN_REGEX)) {
        gtk_label_set_text(label, "Login can contain a-z, 0-9 and \'-\'");
        return false;
    }
    return true;
}

void mx_req_signup(GtkButton *btn, t_chat *chat) {
    char *login = mx_get_buffer_text("buffer_login", chat->builder);
    char *password = mx_get_buffer_text("buffer_password", chat->builder);
    t_dtp *dtp = NULL;
    char pass[33];

    if (is_valid_auth_data(login, password, chat->builder)) {
        pass[32] = '\0';
        mx_md5(pass, (const unsigned char*)password, strlen(password));
        dtp = mx_sign_up_request(login, pass);
        mx_send(chat->ssl, dtp);
        mx_free_request(&dtp);
    }
    (void)btn;
}

void mx_req_login(GtkButton *btn, t_chat *chat) {
    char *login = mx_get_buffer_text("buffer_login", chat->builder);
    char *password = mx_get_buffer_text("buffer_password", chat->builder);
    t_dtp *dtp = NULL;
    char pass[33];

    if (is_valid_auth_data(login, password, chat->builder)) {
        pass[32] = '\0';
        mx_md5(pass, (const unsigned char*)password, strlen(password));
        dtp = mx_log_in_request(login, pass);
        mx_send(chat->ssl, dtp);
        mx_free_request(&dtp);
    }
    (void)btn;
}

void mx_connect_authorization(t_chat *chat) {
    GtkButton *btn_signup = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_signup"));
    GtkButton *btn_login = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_login"));

    g_signal_connect(btn_signup, "clicked", G_CALLBACK(mx_req_signup), chat);
    g_signal_connect(btn_login, "clicked", G_CALLBACK(mx_req_login), chat);
}
