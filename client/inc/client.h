#pragma once

#include "utils.h"
#include "protocol.h"
#include "sqlite3.h"
#include <gtk/gtk.h>
#include "protocol.h"

#define MX_GUI_PATH "../src/gui/gui.glade"

typedef struct s_groom {
    GtkListBox *box_rooms;
    GtkScrolledWindow *page;
    GtkListBoxRow *row_room;
    GtkStack *stack_msg;
    int id;
    char *room_name;
    char *customer;
}              t_groom;

typedef struct s_gmsg {
    char *msg;
    char *login;
    long int date;
    char *room_name;
    int id_message;
}              t_gmsg;

typedef struct s_chat {
    char *auth_token;
    SSL *ssl;
    GtkBuilder *builder;
    t_dtp *data;
    GAsyncQueue *queue;
    bool valid;
    bool (*request_handler[RQ_COUNT_REQUEST])(t_dtp *dtp, struct s_chat *chat);
}              t_chat;

int mx_tcp_connect(const char *host, const char *serv);
t_chat *mx_init_chat(void);
void mx_signup(SSL *ssl);
void mx_login(SSL *ssl);
void *mx_receiver(void *arg);
void mx_init_receiver(t_chat *chat);

//handlers
bool mx_error_handle(t_dtp *data, t_chat *chat);
bool mx_authorization(t_dtp *token, t_chat *chat);
bool mx_new_room(t_dtp *data, t_chat *chat);
bool mx_update_users(t_dtp *data, t_chat *chat);
bool mx_msg(t_dtp *data, t_chat *chat);

//api
t_dtp *mx_new_room_request(char *room_name, bool is_private, char *pass);
t_dtp *mx_token_request(char *token);
t_dtp *mx_log_in_request(char *login, char *pass);
t_dtp *mx_sign_up_request(char *login, char *pass);

//gui
GtkBuilder *mx_init_window(int argc, char **argv);
void mx_init_gui(t_chat *chat);
int mx_start_gui(t_chat *chat);
void mx_start_main_window(t_chat *chat);
void mx_add_groom(t_groom *room, GtkBuilder *builder);
void mx_delete_groom(t_groom **room);
t_groom *mx_create_groom(char *room_name, char *customer, int id);
t_gmsg *mx_create_gmsg(cJSON *msg);
void mx_delete_gmsg(t_gmsg **gmsg);

// gui utils
void mx_scrlldwnd_connect(char *name, GtkWidget *scroll, GtkBuilder *builder);
gchar *mx_get_buffer_text(char *buff_name, GtkBuilder *builder);
void mx_clear_buffer_text(char *buff_name, GtkBuilder *builder);
void mx_widget_switch_visibility(GtkWidget *usr_ctrl, void *widget);
void mx_reset_addroom(GtkButton *btn, GtkBuilder *builder);
void mx_connect_authorization(t_chat *chat);
void mx_errmsg_wrong_authdata(GtkBuilder *builder);
void mx_errmsg_user_exist(GtkBuilder *builder);

//gui wrappers
// void mx_widget_show_all(GtkWidget *widget);
// void mx_widget_destroy(GtkWidget *widget);
// void mx_widget_show(GtkWidget *widget);
void mx_handle_request(t_chat *chat);
