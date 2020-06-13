#pragma once

#include "utils.h"
#include "protocol.h"
#include "sqlite3.h"
#include <gtk/gtk.h>
#include "protocol.h"

#define MX_IMGS_PATH "../src/gui/resources/"
#define MX_GUI_PATH "../src/gui/gui.glade"
#define MX_IMG_EYE MX_IMGS_PATH"eye.png"
#define MX_IMG_CLOSEDEYE MX_IMGS_PATH"closed-eye.png"

#define MX_ERRMSG_INVALID_LOGIN "Login can be minimum 3 symbol of a-z, 0-9, -"
#define MX_ERRMSG_NODATA "Please, enter login and password"
#define MX_ERRMSG_DIFPASS "Passwords must match"
#define MX_ERRMSG_INCCRDATA "The email or password inccorect"
#define MX_ERRMSG_USEREXIST "User already exist"


//settings
#define MX_BUF_MSGS 50
#define MX_MAX_LENGTH_QUEUE 30
#define MX_RECONN_ATTEMPTS 6
#define MX_RECONN_DELAY_S 4

typedef struct s_groom t_groom;
typedef struct s_gmsg t_gmsg;
typedef struct s_chat t_chat;
typedef struct s_con_data t_con_data;

struct s_groom {
    GtkListBox *box_rooms;
    GtkScrolledWindow *page;
    GtkListBoxRow *row_room;
    GtkStack *stack_msg;
    GtkListBox *box_messages;
    GtkLabel *label_name;
    int id;
    char *room_name;
    char *customer;
    long int date;
    char *desc;
    bool is_updated;
};

struct s_gmsg {
    GtkListBoxRow *row_msg;
    char *msg;
    char *login;
    long int date;
    int room_id;
    int message_id;
};

struct s_con_data {
    t_ssl_con *ssl;
    char **argv;
};

struct s_chat {
    char *auth_token;
    char *login;
    t_con_data *con_data;
    t_groom *curr_room;
    SSL *ssl;
    t_dtp *data;
    GtkBuilder *builder;
    GAsyncQueue *queue;
    bool valid;
    void (*error_handler[ER_COUNT_ERRS])(GtkBuilder *builder);
    bool (*request_handler[RQ_COUNT_REQUEST])(t_dtp *dtp, struct s_chat *chat);
};

typedef struct s_signal_data {
    t_groom *groom;
    GtkBuilder *builder;
    GtkListBoxRow *row_msg;
}              t_signal_data;

int mx_tcp_connect(const char *host, const char *serv);
t_chat *mx_init_chat(void);
void mx_signup(SSL *ssl);
void mx_login(SSL *ssl);
void *mx_receiver(void *arg);
void mx_init_handlers(t_chat *chat);
void mx_init_errors(t_chat *chat);
void mx_get_data(t_chat *chat);
bool mx_connect(t_chat *chat);
bool mx_reconnect(t_chat *chat);

//handlers
bool mx_error_handler(t_dtp *data, t_chat *chat);
bool mx_authorization_handler(t_dtp *token, t_chat *chat);
bool mx_new_room_handler(t_dtp *data, t_chat *chat);
bool mx_msg_handler(t_dtp *data, t_chat *chat);
bool mx_rooms_hanlder(t_dtp *data, t_chat *chat);
bool mx_log_out_handler(t_dtp *token, t_chat *chat);
bool mx_new_msgs_hanlder(t_dtp *data, t_chat *chat);
bool mx_upd_room_desc_handler(t_dtp *data, t_chat *chat); // HANDLER FOR ROOM UPDATE DESCRIPTION REQUEST
bool mx_upd_room_name_handler(t_dtp *data, t_chat *chat); // HANDLER FOR ROOM UPDATE NAME REQUEST
bool mx_upd_user_desc_handler(t_dtp *data, t_chat *chat); // HANDLER FOR USER UPDATE DESCRIPTION REQUEST
bool mx_update_users_handler(t_dtp *data, t_chat *chat); // HANDLER FOR USERS ONLINE UPDATE
bool mx_reconnect_hanlder(t_dtp *token, t_chat *chat); // HANDLER FOR RECONNECT
bool mx_del_room_handler(t_dtp *data, t_chat *chat);  // HANDLER FOR DELETE ROOM
bool mx_edit_msg_handler(t_dtp *data, t_chat *chat); // HANDLER FOR EDIT MSG
bool mx_del_msg_handler(t_dtp *data, t_chat *chat); // HANDLER FOR DEL MSG


/*
 *  t_dtp *dtp = mx_upd_room_desc_request(1, "0000000000");
 *  mx_send(chat->ssl, dtp);
 *  mx_free_request(&dtp);
 * 
 * 
 * 
 */
//api
t_dtp *mx_new_room_request(char *room_name, char *desc);
t_dtp *mx_msg_request(char *msg, int room_id);
t_dtp *mx_token_request(char *token);
t_dtp *mx_log_in_request(char *login, char *pass);
t_dtp *mx_sign_up_request(char *login, char *pass);
t_dtp *mx_get_rooms_request(long int date);
t_dtp *mx_log_out_request(char *token);
t_dtp *mx_get_new_msgs_request(long int date, int room_id);
t_dtp *mx_upd_room_desc_request(int room_id, char *desc); // FOR ROOM UPDATE DESCRIPTION CREATE REQUEST
t_dtp *mx_upd_room_name_request(int room_id, char *name); // FOR ROOM UPDATE NAME CREATE REQUEST
t_dtp *mx_upd_user_desc_request(char *desc); // FOR USER DESCRIPTION UPDATE
t_dtp *mx_del_room_request(int room_id); // FOR DELETE ROOM
t_dtp *mx_edit_msg_request(char *msg, int room_id, int msg_id); // FOR EDIT MSG
t_dtp *mx_upd_user_name_request(char *name); //TODO
t_dtp *mx_del_msg_request(int room_id, int msg_id); // FOR DELETE MESSAGE FROM ROOM
t_dtp *mx_edit_msg_request(char *msg, int room_id, int msg_id); // FOR EDIT MESSAGE IN ROOM

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
t_groom *mx_create_groom(cJSON *room);
t_gmsg *mx_create_gmsg(cJSON *msg);
void mx_delete_gmsg(t_gmsg *gmsg);
GtkWidget *mx_create_message_row(t_gmsg *msg);
void mx_add_message_to_room(t_gmsg *msg, GtkBuilder *builder);
void mx_logout_client(t_chat *chat);
void mx_reset_addroom(GtkButton *btn, GtkBuilder *builder);
void mx_reset_auth(GtkNotebook *note, GtkWidget *page,
                   guint page_num, GtkBuilder *builder);
void mx_connect_authorization(t_chat *chat);
void mx_connect_addroom(t_chat *chat);
void mx_connect_send_message(t_chat *chat);
void mx_connect_profile_settings(t_chat *chat);
void mx_connect_room_settings(t_chat *chat);
void mx_connect_message_ctrl(t_chat *chat);
void mx_connect_test_request(t_chat *chat); // DELETE
void mx_errmsg_wrong_authdata(GtkBuilder *builder);
void mx_errmsg_user_exist(GtkBuilder *builder);
void mx_delete_row_room(GtkListBoxRow *row, GtkBuilder *builder);
void mx_set_default_room_sett(GtkBuilder *builder);
void mx_set_current_room_sett(GtkBuilder *builder);
void mx_gupd_room_desc(int id, char *desc, GtkBuilder *builder);
void mx_gupd_room_name(int id, char *name, GtkBuilder *builder);
void mx_gdel_room(int id, GtkBuilder *builder);
void mx_gdel_msg(int msg_id, int room_id, GtkBuilder *builder);

// gui utils
void mx_scrlldwnd_connect(char *name, GtkWidget *scroll, GtkBuilder *builder);
gchar *mx_entry_get_text(char *entry_name, GtkBuilder *builder);
gchar *mx_get_buffer_text(char *buff_name, GtkBuilder *builder);
void mx_clear_buffer_text(char *buff_name, GtkBuilder *builder);
void mx_clear_label_by_name(char *label_name, GtkBuilder *builder);
void mx_widget_switch_visibility(GtkWidget *usr_ctrl, void *widget);
t_groom *mx_get_selected_groom(GtkBuilder *builder);
t_groom *mx_get_groom_by_id(int room_id, GtkBuilder *builder);
t_gmsg *mx_get_selected_gmsg(GtkBuilder *builder);
void mx_unselect_room(t_groom *groom, GtkBuilder *builder);
void mx_entry_set_icon_by_path(GtkEntry *entry, char *path,
                               GtkEntryIconPosition icon_pos);
t_signal_data *mx_create_sigdata(GtkBuilder *builder, t_groom *groom,
                                 GtkListBoxRow *row_msg);
void mx_free_sigdata(t_signal_data *data);
char *mx_page_name(int id);

// gui wrappers
// void mx_widget_show_all(GtkWidget *widget);
// void mx_widget_destroy(GtkWidget *widget);
// void mx_widget_show(GtkWidget *widget);
void mx_handle_request(t_chat *chat);
void mx_send_auth_request(char *login, char *password,
                          SSL *ssl, t_request_type request_type);
void css_connect();
