#pragma once

#include "utils.h"
#include "sqlite3.h"
#include "protocol.h"
#include <gtk/gtk.h>
#include <glib.h>
#include <gio/gio.h>

#define MX_IMGS_PATH "../src/gui/resources/"
#define MX_STICKER_PATH MX_IMGS_PATH"stickers/"
#define MX_GUI_PATH "../src/gui/gui.glade"
#define MX_IMG_EYE MX_IMGS_PATH"eye.png"
#define MX_IMG_CLOSEDEYE MX_IMGS_PATH"closed-eye.png"

#define MX_ERRMSG_INVALID_LOGIN "Login can be minimum 3 symbol of a-z, 0-9, -"
#define MX_ERRMSG_NODATA "Please, enter login and password"
#define MX_ERRMSG_DIFPASS "Passwords must match"
#define MX_ERRMSG_INCCRDATA "The login or password inccorect"
#define MX_ERRMSG_USEREXIST "User already exist"

#define MX_ROOM_CTRL 0
#define MX_MSG_CTRL 1

#define MX_LOCAL_ROOMS "listbox_rooms"
#define MX_GLOBAL_ROOMS "listbox_global_rooms"

//settings
#define MX_BUF_MSGS 13
#define MX_MAX_LENGTH_QUEUE 30
#define MX_RECONN_ATTEMPTS 6
#define MX_RECONN_DELAY_S 4

// flag time
#define MX_TIME_SHORT 0
#define MX_TIME_LONG 1

//formatting
#define MX_FT_SCRATCH "~~"
#define MX_FT_BOLD "**"
#define MX_FT_IMPORTANT "``"
#define MX_FT_ITALIC "##"
#define MX_FT_UNDER "__"

#define MX_OP_SCRATCH "<span strikethrough=\"true\">%s</span>"
#define MX_OP_BOLD "<span font_weight=\"bold\">%s</span>"
#define MX_OP_IMPORTANT "<span background=\"#FF698C7F\">%s</span>"
#define MX_OP_ITALIC "<span font_style=\"italic\">%s</span>"
#define MX_OP_UNDER "<span underline=\"single\">%s</span>"

#define MX_CLOSE_SPAN "</span>"

typedef struct s_groom t_groom;
typedef struct s_gmsg t_gmsg;
typedef struct s_chat t_chat;
typedef struct s_filter_data t_filter_data;
typedef struct s_signal_data t_signal_data;
typedef struct s_gsticker t_gsticker;

struct s_groom {
    GtkListBox *box_rooms;
    GtkScrolledWindow *page;
    GtkListBoxRow *row_room;
    GtkStack *stack_msg;
    GtkListBox *box_messages;
    GtkLabel *label_name;
    GHashTable *members;
    gboolean is_watched;
    int id;
    char *room_name;
    char *customer;
    int customer_id;
    long int date;
    char *desc;
    bool is_updated;
    gint uploaded;
};

struct s_gmsg {
    GtkListBoxRow *row_msg;
    GtkLabel *label_text;
    gint type;
    char *msg;
    char *login;
    guint64 date;
    int room_id;
    int message_id;
};

struct s_chat {
    GDataOutputStream *out;
    GDataInputStream *in;
    GSocketConnection *conn;
    GSocketClient *cli_conn;
    GHashTable *stickers;
    char *auth_token;
    char *login;
    int argc;
    char **argv;
    gsize id;
    t_groom *curr_room;
    t_dtp *data;
    gboolean upl_old_msgs;
    GtkBuilder *builder;
    bool valid;
    void (*error_handler[ER_COUNT_ERRS])(GtkBuilder *builder);
    bool (*request_handler[RQ_COUNT_REQUEST])(t_dtp *dtp, struct s_chat *chat);
};

struct s_signal_data {
    t_groom *groom;
    t_chat *chat;
    GtkListBoxRow *row_msg;
};

struct s_filter_data {
    gboolean is_found_rooms;
    gchar *search_name;
};

gssize mx_send(GDataOutputStream *out, t_dtp *dtp);
int mx_tcp_connect(const char *host, const char *serv);
t_chat *mx_init_chat(GSocketConnection *connection, int argc, char **argv);
void mx_receiver(GObject *source_object, GAsyncResult *res, gpointer user_data);
void mx_init_handlers(t_chat *chat);
void mx_init_errors(t_chat *chat);
void mx_get_data(t_chat *chat);
// bool mx_connect(t_chat *chat);
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
bool mx_upload_file_handler(t_dtp *data, t_chat *chat); // HANDLER FOR GET FILE
bool mx_search_rooms_handler(t_dtp *data, t_chat *chat); //HANDLER FOR SEARCHING
bool mx_join_room_handler(t_dtp *data, t_chat *chat); //HANDLER FOR JOIN ROOM
bool mx_get_members_handler(t_dtp *data, t_chat *chat); //HANDLER FOR USERS
bool mx_member_info_handler(t_dtp *data, t_chat *chat); //HANDLER FOR INFO MEMBER
bool mx_new_member_handler(t_dtp *data, t_chat *chat); //HANDLER FOR NEW MEMBER
bool mx_ban_member_handler(t_dtp *data, t_chat *chat); //HANDLER FOR BAN MEMBER
bool mx_search_msgs_handler(t_dtp *data, t_chat *chat); //HANDLER FOR SEARCH MSG
bool mx_del_hist_handler(t_dtp *data, t_chat *chat); //HANDLER FOR DELETE HISTORY
bool mx_old_msgs_hanlder(t_dtp *data, t_chat *chat); //HANDLER FOR UPD MSGS


/*
 *  t_dtp *dtp = mx_upd_room_desc_request(1, "0000000000");
 *  mx_send(chat->ssl, dtp);
 *  mx_free_request(&dtp);
 * 
 * 
 * 
 */
//api
t_dtp *mx_new_room_request(char *room_name, char *desc, t_room_type type);
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
t_dtp *mx_upload_file_request(char *name, goffset size, char *token); // FOR UPLOAD FILE
t_dtp *mx_search_rooms_request(char *room_name); // FOR SEARCHING CHANNEL
t_dtp *mx_join_room_request(int room_id); //FOR JOIN TO ROOM
t_dtp *mx_get_members_request(int room_id); //FOR MEMEBERS
t_dtp *mx_member_info_request(int user_id); //FOR INFO ABOUT MEMBER
t_dtp *mx_ban_member_request(int room_id, int user_id); // FOR BAN MEMBER
t_dtp *mx_sticker_request(char *sticker, int room_id); // FOR STICKER
t_dtp *mx_search_msgs_request(char *msg, int room_id); // FOR SEARCH MSGS
t_dtp *mx_del_hist_request(int room_id); // FOR DELETE HISTORY
t_dtp *mx_old_msgs_request(guint64 date, int room_id); // FOR UPD MSGS REQUEST

//errors api
void mx_err_auth_data_handler(GtkBuilder *builder);
void mx_err_user_exist_handler(GtkBuilder *builder);

//gui
GtkBuilder *mx_init_window(int argc, char **argv);
void mx_init_gui(t_chat *chat);
gint mx_start_gui(t_chat *chat);
void mx_start_main_window(t_chat *chat);
void mx_add_groom(t_groom *room, t_chat *chat);
void mx_delete_groom(t_groom *room);
t_groom *mx_create_groom(cJSON *room);
t_gmsg *mx_create_gmsg(cJSON *msg, t_chat *chat);
void mx_delete_gmsg(t_gmsg *gmsg);
GtkWidget *mx_create_message_row(t_chat *chat,  t_gmsg *gmsg);
void mx_add_message_to_room_new(t_gmsg *msg, t_chat *chat);
void mx_add_message_to_room_old(t_gmsg *msg, t_chat *chat);
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
void mx_connect_search(t_chat *chat);
void mx_connect_join_to_room(t_chat *chat);
void mx_connect_stickers(t_chat *chat);
void mx_connect_test_request(t_chat *chat); // DELETE
void mx_errmsg_wrong_authdata(GtkBuilder *builder);
void mx_errmsg_user_exist(GtkBuilder *builder);
void mx_delete_row_room(GtkListBoxRow *row, GtkBuilder *builder);
void mx_set_default_room_sett(GtkBuilder *builder);
void mx_set_current_room_sett(GtkBuilder *builder);
void mx_gupd_room_desc(gint id, gchar *desc, GtkBuilder *builder);
void mx_gupd_room_name(gint id, gchar *name, GtkBuilder *builder);
void mx_gdel_room(gint id, GtkBuilder *builder);
void mx_gdel_msg(gint msg_id, gint room_id, GtkBuilder *builder);
void mx_gupd_msg_text(gint msg_id, gint room_id,
                      gchar *text, GtkBuilder *builder);
void mx_reset_messege_room(t_groom *new_selected, GtkBuilder *builder);
void mx_hide_msg_editing(GtkButton *btn, GtkBuilder *builder);
void mx_set_room_widgets_visibility(GtkBuilder *builder, bool visibility);
void mx_switch_room_header(GtkBuilder *builder, gint page_index);
void mx_unselect_curr_room_messages(GtkBuilder *builder);
void mx_select_msg(gpointer *eventbox, gpointer *event, t_signal_data *data);
GtkWidget *mx_create_reg_message_row(t_gmsg *gmsg, gboolean is_own);
GtkWidget *mx_msgcreate_eventbox();
GtkWidget *mx_msgcreate_box_main(GtkWidget *eventbox, gboolean is_own);
void mx_msgcreate_box_info(GtkWidget *box_main, t_gmsg *gmsg, gboolean is_own);
void mx_msgcreate_label_login(GtkWidget *box_main, t_gmsg *gmsg);
void mx_msgcreate_label_text(GtkWidget *box_info,
                             t_gmsg *gmsg, gboolean is_own);
void mx_msgcreate_img_sticker(GtkWidget *box_info,
                              t_gmsg *gmsg, gboolean is_own);
void mx_msgcreate_label_time(GtkWidget *box_info,
                             t_gmsg *gmsg, gboolean is_own);
void mx_search_delim_set_visibility(GtkBuilder *builder, gboolean is_visible);
gboolean mx_stop_search_room(gpointer *entry,
                             gpointer *data, GtkBuilder *builder);
void mx_search_local_rooms(GtkBuilder *builder, t_filter_data *data);
void mx_search_global_rooms(GtkBuilder *builder);
void mx_add_room_row(t_groom *room, t_chat *chat, gchar *listbox_name);
void mx_clear_global_search(GtkBuilder *builder);
void mx_box_messages_reached(GtkScrolledWindow *scroll,
                             GtkPositionType pos, t_chat *chat);
gboolean mx_stop_search_message(gpointer *entry,
                                gpointer *data, GtkBuilder *builder);
void mx_add_message_to_found(t_gmsg *gmsg, t_chat *chat);
void mx_clear_found_msgs(GtkBuilder *builder);

// gui utils
void mx_scrlldwnd_connect(gchar *name, GtkWidget *scroll, GtkBuilder *builder);
gchar *mx_entry_get_text(gchar *entry_name, GtkBuilder *builder);
gchar *mx_get_buffer_text(gchar *buff_name, GtkBuilder *builder);
void mx_clear_buffer_text(gchar *buff_name, GtkBuilder *builder);
void mx_clear_label_by_name(gchar *label_name, GtkBuilder *builder);
void mx_widget_set_visibility(GtkWidget *widget, gboolean is_visible);
void mx_widget_set_visibility_by_name(GtkBuilder *builder,
                                      gchar *name, gboolean is_visible);
void mx_widget_switch_visibility(GtkWidget *usr_ctrl, GtkWidget *widget);
void mx_widget_switch_visibility_by_name(GtkBuilder *builder, gchar *name);
t_groom *mx_get_selected_groom(GtkBuilder *builder, gchar *list_name);
t_groom *mx_get_groom_by_id(gint room_id, GtkBuilder *builder);
t_gmsg *mx_get_selected_gmsg(GtkBuilder *builder);
t_gmsg *mx_get_gmsg_by_id(gint msg_id, gint room_id, GtkBuilder *builder);
void mx_unselect_room(t_groom *groom, GtkBuilder *builder);
void mx_entry_set_icon_by_path(GtkEntry *entry, gchar *path,
                               GtkEntryIconPosition icon_pos);
t_signal_data *mx_create_sigdata(t_chat *chat, t_groom *groom,
                                 GtkListBoxRow *row_msg);
void mx_free_sigdata(t_signal_data *data);
char *mx_msgpage_name(gint id);
gboolean mx_widget_is_visible(gchar *widget_name, GtkBuilder *builder);
void mx_widget_set_class(GtkWidget *widget, gchar *class);
gboolean mx_unset_placeholder(GtkWidget *textview, GdkEvent  *event,
                                   gpointer *user_data);
gboolean mx_set_placeholder(GtkWidget *textview, GdkEvent *event,
                                   gpointer *user_data);
t_filter_data *mx_create_filter_data(gchar *search_name);
void mx_free_filter_data(t_filter_data *filter_data);
gchar *mx_get_string_time(guint64 miliseconds, gint8 format);

    // gui wrappers
    // void mx_widget_show_all(GtkWidget *widget);
    // void mx_widget_destroy(GtkWidget *widget);
    // void mx_widget_show(GtkWidget *widget);
    void mx_upload_file(char *path, t_chat *chat);
bool mx_handle_request(char *request, t_chat *chat);
void mx_send_auth_request(char *login, char *password,
                          t_chat *chat, t_request_type request_type);
void mx_css_connect();
gchar *mx_format_text(gchar *text);
