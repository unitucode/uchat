#include "client.h"

static bool is_valid_auth_data(char *login, char *pass, GtkLabel *label) {
    if (*login == '\0' || *pass == '\0') {
        gtk_label_set_text(label, MX_ERRMSG_NODATA);
        return false;
    }
    else if (!mx_match_search(login, MX_LOGIN_REGEX)) {
        gtk_label_set_text(label, MX_ERRMSG_INVALID_LOGIN);
        return false;
    }
    return true;
}

static void req_signup(t_chat *chat) {
    GObject *label_error = gtk_builder_get_object(chat->builder,
                                                  "label_autherror_signup");
    char *login = mx_get_buffer_text("buffer_login", chat->builder);
    char *password = mx_get_buffer_text("buffer_password", chat->builder);
    char *confirm = mx_get_buffer_text("buffer_password_confirm",
                                       chat->builder);

    if (is_valid_auth_data(login, password, GTK_LABEL(label_error))) {
        if (!strcmp(password, confirm))
            mx_send_auth_request(login, password, chat, RQ_SIGN_UP);
        else
            gtk_label_set_text(GTK_LABEL(label_error), MX_ERRMSG_DIFPASS);
    }
}

static void req_login(t_chat *chat) {
    GObject *label_error = gtk_builder_get_object(chat->builder,
                                                  "label_autherror_login");
    char *login = mx_get_buffer_text("buffer_login", chat->builder);
    char *password = mx_get_buffer_text("buffer_password", chat->builder);

    if (is_valid_auth_data(login, password, GTK_LABEL(label_error))) {
        mx_send_auth_request(login, password, chat, RQ_LOG_IN);
    }
}

static void choose_auth(GtkButton *btn, t_chat *chat) {
    GtkNotebook *note = GTK_NOTEBOOK(gtk_builder_get_object(chat->builder,
                                                            "notebook_auth"));
    guint page_num = gtk_notebook_get_current_page(note);

    if (page_num == 0)
        req_login(chat);
    else
        req_signup(chat);
    (void)btn;
}

void mx_connect_authorization(t_chat *chat) {
    GtkButton *btn_confirm = GTK_BUTTON(gtk_builder_get_object(chat->builder,
                                                       "btn_auth_confirm"));

    g_signal_connect(btn_confirm, "clicked", G_CALLBACK(choose_auth), chat);
}
