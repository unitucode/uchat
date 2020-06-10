#pragma once

#include "utils.h"
#include "protocol.h"
#include "sqlite3.h"
#include <gtk/gtk.h>
#include "protocol.h"

#define MX_GUI_PATH "../src/gui/gui.glade"

#define MX_ERRMSG_INVALID_LOGIN "Login can be minimum 3 symbol of a-z, 0-9, -"
#define MX_ERRMSG_NODATA "Please, enter login and password"
#define MX_ERRMSG_DIFPASS "Passwords must match"
#define MX_ERRMSG_INCCRDATA "The email or password inccorect"
#define MX_ERRMSG_USEREXIST "User already exist"


//settings
#define MX_BUF_MSGS 50
#define MX_MAX_LENGTH_QUEUE 10

typedef struct s_groom t_groom;
typedef struct s_gmsg t_gmsg;
typedef struct s_chat t_chat;

struct s_groom {
    GtkListBox *box_rooms;
    GtkScrolledWindow *page;
    GtkListBoxRow *row_room;
    GtkStack *stack_msg;
    GtkWidget *box_messages;
    int id;
    char *room_name;
    char *customer;
    long int date;
    char *desc;
    bool is_updated;
};

struct s_gmsg {
    char *msg;
    char *login;
    long int date;
    char *room_name;
    int id_message;
};

struct s_chat {
    char *auth_token;
    char *login;
    SSL *ssl;
    t_dtp *data;
    GtkBuilder *builder;
    GAsyncQueue *queue;
    bool valid;
    void (*error_handler[ER_COUNT_ERRS])(GtkBuilder *builder);
    bool (*request_handler[RQ_COUNT_REQUEST])(t_dtp *dtp, struct s_chat *chat);
};

int mx_tcp_connect(const char *host, const char *serv);
t_chat *mx_init_chat(void);
void mx_signup(SSL *ssl);
void mx_login(SSL *ssl);
void *mx_receiver(void *arg);
void mx_init_handlers(t_chat *chat);
void mx_init_errors(t_chat *chat);
void mx_get_data(t_chat *chat);

//handlers
bool mx_error_handler(t_dtp *data, t_chat *chat);
bool mx_authorization_handler(t_dtp *token, t_chat *chat);
bool mx_new_room_handler(t_dtp *data, t_chat *chat);
bool mx_update_users_handler(t_dtp *data, t_chat *chat);
bool mx_msg_handler(t_dtp *data, t_chat *chat);
bool mx_rooms_hanlder(t_dtp *data, t_chat *chat);
bool mx_log_out_handler(t_dtp *token, t_chat *chat);
bool mx_new_msgs_hanlder(t_dtp *data, t_chat *chat);

//api
t_dtp *mx_new_room_request(char *room_name, bool is_private, char *pass);
t_dtp *mx_msg_request(char *msg, char *room_name);
t_dtp *mx_token_request(char *token);
t_dtp *mx_log_in_request(char *login, char *pass);
t_dtp *mx_sign_up_request(char *login, char *pass);
t_dtp *mx_get_rooms_request(long int date);
t_dtp *mx_log_out_request(char *token);
t_dtp *mx_get_new_msgs_request(long int date, char *room_name);
t_dtp *mx_upd_room_desc_request(int room_id, char *desc); //TODO

//errors api
void mx_err_auth_data_handler(GtkBuilder *builder);
void mx_err_user_exist_handler(GtkBuilder *builder);

//gui
GtkBuilder *mx_init_window(int argc, char **argv);
void mx_init_gui(t_chat *chat);
int mx_start_gui(t_chat *chat);
void mx_start_main_window(t_chat *chat);
void mx_add_groom(t_groom *room, GtkBuilder *builder);
void mx_delete_groom(t_groom *room);
t_groom *mx_create_groom(char *room_name, char *customer, int id,
                         long int date);
t_gmsg *mx_create_gmsg(cJSON *msg);
void mx_delete_gmsg(t_gmsg **gmsg);
GtkWidget *mx_create_message_row(t_gmsg *msg);
void mx_add_message_to_room(t_gmsg *msg, GtkBuilder *builder);

// gui utils
void mx_scrlldwnd_connect(char *name, GtkWidget *scroll, GtkBuilder *builder);
gchar *mx_get_buffer_text(char *buff_name, GtkBuilder *builder);
void mx_clear_buffer_text(char *buff_name, GtkBuilder *builder);
void mx_clear_label_by_name(char *label_name, GtkBuilder *builder);
void mx_widget_switch_visibility(GtkWidget *usr_ctrl, void *widget);
void mx_reset_addroom(GtkButton *btn, GtkBuilder *builder);
void mx_connect_authorization(t_chat *chat);
void mx_connect_addroom(t_chat *chat);
void mx_connect_send_message(t_chat *chat);
void mx_connect_profile_settings(t_chat *chat);
t_groom *mx_get_selected_groom(GtkBuilder *builder);
t_groom *mx_get_groom_by_name(char *name, GtkBuilder *builder);

//gui wrappers
// void mx_widget_show_all(GtkWidget *widget);
// void mx_widget_destroy(GtkWidget *widget);
// void mx_widget_show(GtkWidget *widget);
void mx_handle_request(t_chat *chat);
void mx_send_auth_request(char *login, char *password,
                          SSL *ssl, t_request_type request_type);
