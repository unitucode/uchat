#include "client.h"

void mx_reset_auth(GtkNotebook *note, GtkWidget *page,
                   guint page_num, GtkBuilder *builder) {
    GtkButton *checkbtn_login = GTK_BUTTON(gtk_builder_get_object(builder,
                                                          "checkbtn_login"));
    GtkButton *checkbtn_signup = GTK_BUTTON(gtk_builder_get_object(builder,
                                                          "checkbtn_signup"));

    mx_clear_buffer_text("buffer_login", builder);
    mx_clear_buffer_text("buffer_password", builder);
    mx_clear_buffer_text("buffer_password_confirm", builder);
    mx_clear_label_by_name("label_autherror_login", builder);
    mx_clear_label_by_name("label_autherror_signup", builder);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbtn_login), 0);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(checkbtn_signup), 0);
    (void)note;
    (void)page;
    (void)page_num;
}

void mx_close_auth(GtkButton *btn, GtkDialog *dialog) {
    gtk_widget_destroy(GTK_WIDGET(dialog));
    (void)btn;
}

void mx_show_password(GtkToggleButton *btn, GtkEntry *entry) {
    gtk_entry_set_visibility(entry, gtk_toggle_button_get_active(btn));
}

void mx_errmsg_wrong_authdata(GtkBuilder *builder) {
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder,
                                                       "label_autherror_login"));

    gtk_label_set_text(label, "The email or password inccorect");
}

void mx_errmsg_user_exist(GtkBuilder *builder) {
    GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder,
                                                       "label_autherror_signup"));

    gtk_label_set_text(label, "User already exist");
}

static bool is_valid_auth_data(char *login, char *pass, GtkLabel *label) {
    // GtkLabel *label = GTK_LABEL(gtk_builder_get_object(builder,
    //                                                   "label_autherror"));

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

static void req_signup(t_chat *chat) {
    GObject *label_error = gtk_builder_get_object(chat->builder,
                                                  "label_autherror_signup");
    char *login = mx_get_buffer_text("buffer_login", chat->builder);
    char *password = mx_get_buffer_text("buffer_password", chat->builder);
    t_dtp *dtp = NULL;
    char pass[33];

    if (is_valid_auth_data(login, password, GTK_LABEL(label_error))) {
        pass[32] = '\0';
        mx_md5(pass, (const unsigned char*)password, strlen(password));
        dtp = mx_sign_up_request(login, pass);
        mx_send(chat->ssl, dtp);
        mx_free_request(&dtp);
    }
}

static void req_login(t_chat *chat) {
    GObject *label_error = gtk_builder_get_object(chat->builder,
                                                  "label_autherror_login");
    char *login = mx_get_buffer_text("buffer_login", chat->builder);
    char *password = mx_get_buffer_text("buffer_password", chat->builder);
    t_dtp *dtp = NULL;
    char pass[33];

    if (is_valid_auth_data(login, password, GTK_LABEL(label_error))) {
        pass[32] = '\0';
        mx_md5(pass, (const unsigned char*)password, strlen(password));
        dtp = mx_log_in_request(login, pass);
        mx_send(chat->ssl, dtp);
        mx_free_request(&dtp);
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
