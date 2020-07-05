#pragma once

#include "utils.h"
#include "sqlite3.h"
#include "protocol.h"
#include <gtk/gtk.h>
#include <glib.h>
#include <gio/gio.h>

/*
 * Icons and images paths
 */
#define MX_IMGS_PATH "../src/gui/resources/"
#define MX_STICKER_PATH MX_IMGS_PATH"stickers/"
#define MX_GUI_PATH "../src/gui/gui.glade"
#define MX_IMG_EYE MX_IMGS_PATH"eye.png"
#define MX_IMG_CLOSEDEYE MX_IMGS_PATH"closed-eye.png"

/*
 * Error messages for authorization
 */
#define MX_ERRMSG_INVALID_LOGIN "Login can be minimum 3 symbol of a-z, 0-9, -"
#define MX_ERRMSG_NODATA "Please, enter login and password"
#define MX_ERRMSG_DIFPASS "Passwords must match"
#define MX_ERRMSG_INCCRDATA "The login or password inccorect"
#define MX_ERRMSG_USEREXIST "User already exist"
#define MX_ERRMSG_CLIEXIST "User already authorized"

/*
 * Controll-headerbar
 */
#define MX_ROOM_CTRL 0
#define MX_MSG_CTRL 1

/*
 * Keybord
 */
#define MX_KEY_ENTER (gint)65293
#define MX_KEY_SHIFT (gint)65505

/*
 * GtkListBox of room lists
 */
#define MX_LOCAL_ROOMS "listbox_rooms"
#define MX_GLOBAL_ROOMS "listbox_global_rooms"

/*
 * Themes
 */
#define MX_DARK_THEME "../src/gui/resources/dark-theme.css"
#define MX_LIGHT_THEME "../src/gui/resources/light-theme.css"
#define MX_THEME_FILE "set-theme"

/*
 * Settings
 */
#define MX_BUF_MSGS 30
#define MX_RECONN_DELAY_S 4

/*
 * Time flags
 */
#define MX_TIME_SHORT 0
#define MX_TIME_LONG 1

/*
 * Formatting characters
 */
#define MX_FT_SCRATCH "~~"
#define MX_FT_BOLD "**"
#define MX_FT_IMPORTANT "``"
#define MX_FT_ITALIC "##"
#define MX_FT_UNDER "__"

/*
 * Formatting spans
 */
#define MX_OP_SCRATCH "<span strikethrough=\"true\">%s</span>"
#define MX_OP_BOLD "<span font_weight=\"bold\">%s</span>"
#define MX_OP_IMPORTANT "<span background=\"#FF698C7F\">%s</span>"
#define MX_OP_ITALIC "<span font_style=\"italic\">%s</span>"
#define MX_OP_UNDER "<span underline=\"single\">%s</span>"
#define MX_CLOSE_SPAN "</span>"

/* Groom
 * ----------
 * box_rooms: GtkLisBox of all rooms
 * page: GtkStack page of this room with messages
 * row_room: pointer to room GtkListBoxRow
 * stack_msg: GtkStack of pages with messages
 * box_messages: GtkListBox of all messages or room
 * label_name: pointer to GtkLabel with room name
 * members: hash table with all members in room
 * is_watched: flag that check is watched new messages in room
 * id: room id
 * room_name: name of room
 * customer: customer's login
 * customer_id: customer's id
 * date: creation date of room
 * desc: description of room
 * is_updated: flag that check is room has new messages
 * uploaded: count of uploaded messages
 * power: power that room used
 */
typedef struct s_groom t_groom;

/* Gmsg
 * ----------
 * row_msg: pointer to message GtkListBoxRow
 * label_text: pointer to GtkLabel with message content
 * label_power: pointer to label with message power
 * type: type of message (STICKER, FILE ...)
 * msg: text of message
 * login: login of sender
 * date: send date
 * room_id: room that contains this message
 * message_id: message id
 * power: power that message used
 * select_all: count of all selected messages
 * select_own: count of own selected messages
 * select_another: count of selected messages from another users
 * select_notedit: count of selected not editable messages
 */
typedef struct s_gmsg t_gmsg;

/* Chat
 * ----------
 * out: data output stream to server
 * in: data input stream to server
 * cli_conn: client connection to server
 * auth_token: authorization token
 * login: user login
 * desc: user description
 * argc: arguments count
 * argv: arguments array
 * id: user id
 * curr_room: current selected room in chat
 * data: dtp data
 * upl_old_msgs: status of uploading
 * builder: gtk builder
 * valid: validation packets
 * error_handler: array of error handlers
 * request_hanlder: array of request handlers
 * msg_placeholder: status of placeholder
 * shift_hold: flag if shift is hold 
 * css_prov: contain css-styles
 */
typedef struct s_chat t_chat;

/* Filter data
 * ----------
 * is_found_rooms: flag of found rooms
 * search_name: contain search name of room
 */
typedef struct s_filter_data t_filter_data;

/* Signal data
 * ----------
 * groom: t_groom for gpointer user_data
 * chat: t_chat for gpointer user_data
 * row_msg: GtkListBoxRow for gpointer user_data
 */
typedef struct s_signal_data t_signal_data;

struct s_groom {
    GtkListBox *box_rooms;
    GtkScrolledWindow *page;
    GtkListBoxRow *row_room;
    GtkStack *stack_msg;
    GtkListBox *box_messages;
    GtkLabel *label_name;
    GHashTable *members;
    gboolean is_watched;
    guint64 id;
    char *room_name;
    char *customer;
    guint64 customer_id;
    guint64 date;
    char *desc;
    gboolean is_updated;
    gint uploaded;
    gdouble power;
    gboolean select_all;
    gboolean select_own;
    gboolean select_another;
    gboolean select_notedit;
};

struct s_gmsg {
    GtkListBoxRow *row_msg;
    GtkLabel *label_text;
    GtkLabel *label_power;
    gint type;
    char *msg;
    char *login;
    guint64 date;
    guint64 room_id;
    guint64 message_id;
    gdouble power;
};

struct s_chat {
    GDataOutputStream *out;
    GDataInputStream *in;
    GSocketConnection *conn;
    GSocketClient *cli_conn;
    char *auth_token;
    char *login;
    gchar *desc;
    gint argc;
    char **argv;
    gsize id;
    t_groom *curr_room;
    t_dtp *data;
    gboolean upl_old_msgs;
    GtkBuilder *builder;
    gboolean valid;
    void (*error_handler[ER_COUNT_ERRS])(GtkBuilder *builder);
    gboolean (*request_handler[RQ_COUNT_REQUEST])(t_dtp *dtp,
                                                  struct s_chat *chat);
    gboolean msg_placeholder;
    gboolean shift_hold;
    GtkCssProvider *css_prov;
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

/*
 * Utils
 */
gdouble mx_get_used_power(guint64 chars);
gssize mx_send(GDataOutputStream *out, t_dtp *dtp);
t_chat *mx_init_chat(GSocketConnection *connection, gint argc, char **argv);
void mx_receiver(GObject *source_object, GAsyncResult *res,
                 gpointer user_data);
void mx_init_handlers(t_chat *chat);
void mx_init_errors(t_chat *chat);
void mx_get_data(t_chat *chat);
void mx_upload_file(gchar *path, gint room_id, t_chat *chat);
void mx_send_ready(GSocketConnection *conn);

/*
 * Request handlers
 */
gboolean mx_error_handler(t_dtp *data, t_chat *chat);
gboolean mx_authorization_handler(t_dtp *token, t_chat *chat);
gboolean mx_new_room_handler(t_dtp *data, t_chat *chat);
gboolean mx_msg_handler(t_dtp *data, t_chat *chat);
gboolean mx_rooms_hanlder(t_dtp *data, t_chat *chat);
gboolean mx_log_out_handler(t_dtp *token, t_chat *chat);
gboolean mx_new_msgs_hanlder(t_dtp *data, t_chat *chat);
gboolean mx_upd_room_desc_handler(t_dtp *data, t_chat *chat);
gboolean mx_upd_room_name_handler(t_dtp *data, t_chat *chat);
gboolean mx_upd_user_desc_handler(t_dtp *data, t_chat *chat);
gboolean mx_update_users_handler(t_dtp *data, t_chat *chat);
gboolean mx_del_room_handler(t_dtp *data, t_chat *chat);
gboolean mx_edit_msg_handler(t_dtp *data, t_chat *chat);
gboolean mx_del_msg_handler(t_dtp *data, t_chat *chat);
gboolean mx_upload_file_handler(t_dtp *data, t_chat *chat);
gboolean mx_search_rooms_handler(t_dtp *data, t_chat *chat);
gboolean mx_join_room_handler(t_dtp *data, t_chat *chat);
gboolean mx_get_members_handler(t_dtp *data, t_chat *chat);
gboolean mx_member_info_handler(t_dtp *data, t_chat *chat);
gboolean mx_new_member_handler(t_dtp *data, t_chat *chat);
gboolean mx_ban_member_handler(t_dtp *data, t_chat *chat);
gboolean mx_search_msgs_handler(t_dtp *data, t_chat *chat);
gboolean mx_del_hist_handler(t_dtp *data, t_chat *chat);
gboolean mx_old_msgs_hanlder(t_dtp *data, t_chat *chat);
gboolean mx_upd_room_power_handler(t_dtp *data, t_chat *chat);
void mx_download_file(guint64 room_id, guint64 msg_id, t_chat *chat);
void mx_file_read(gsize size, gchar *name, GInputStream *in);

/*
 * Request creation
 */
t_dtp *mx_new_room_request(char *room_name, char *desc, t_room_type type);
t_dtp *mx_msg_request(char *msg, guint64 room_id);
t_dtp *mx_token_request(char *token);
t_dtp *mx_log_in_request(char *login, char *pass);
t_dtp *mx_sign_up_request(char *login, char *pass);
t_dtp *mx_get_rooms_request(guint64 date);
t_dtp *mx_log_out_request(char *token);
t_dtp *mx_get_new_msgs_request(guint64 date, guint64 room_id);
t_dtp *mx_upd_room_desc_request(guint64 room_id, char *desc);
t_dtp *mx_upd_room_name_request(guint64 room_id, char *name);
t_dtp *mx_upd_user_desc_request(char *desc);
t_dtp *mx_del_room_request(guint64 room_id);
t_dtp *mx_upd_user_name_request(char *name);
t_dtp *mx_del_msg_request(guint64 room_id, guint64 msg_id);
t_dtp *mx_edit_msg_request(char *msg, guint64 room_id, guint64 msg_id);
t_dtp *mx_search_rooms_request(char *room_name);
t_dtp *mx_join_room_request(guint64 room_id);
t_dtp *mx_get_members_request(guint64 room_id);
t_dtp *mx_member_info_request(guint64 user_id);
t_dtp *mx_ban_member_request(guint64 room_id, guint64 user_id);
t_dtp *mx_sticker_request(char *sticker, guint64 room_id);
t_dtp *mx_search_msgs_request(char *msg, guint64 room_id);
t_dtp *mx_del_hist_request(guint64 room_id);
t_dtp *mx_old_msgs_request(guint64 date, guint64 room_id);
t_dtp *mx_upload_file_request(const char *name, goffset size,
                              char *token, guint64 room_id);
t_dtp *mx_download_file_request(guint64 room_id, guint64 msg_id,
                                gchar *token);
gboolean mx_handle_request(char *request, t_chat *chat);

/*
 * Error handlers
 */
void mx_err_auth_data_handler(GtkBuilder *builder);
void mx_err_user_exist_handler(GtkBuilder *builder);
void mx_err_cli_exist_handler(GtkBuilder *builder);

/*
 * Gui functions
 */
GtkBuilder *mx_init_window(gint argc, char **argv);
void mx_init_gui(t_chat *chat);
gint mx_start_gui(t_chat *chat);
void mx_start_main_window(t_chat *chat);
void mx_add_groom(t_groom *room, t_chat *chat);
void mx_delete_groom(t_groom *room);
t_groom *mx_create_groom(cJSON *room);
t_gmsg *mx_create_gmsg(cJSON *msg, t_chat *chat);
gboolean mx_delete_gmsg(t_gmsg *gmsg);
GtkWidget *mx_create_reg_message_row(t_gmsg *gmsg,
                                     gboolean is_own, t_chat *chat);
void mx_add_message_to_room_new(t_gmsg *msg, t_chat *chat);
void mx_add_message_to_room_old(t_gmsg *msg, t_chat *chat);
void mx_logout_client(t_chat *chat);
void mx_reset_addroom(GtkButton *btn, GtkBuilder *builder);
void mx_reset_auth(GtkNotebook *note, GtkWidget *page,
                   guint page_num, GtkBuilder *builder);
void mx_errmsg_wrong_authdata(GtkBuilder *builder);
void mx_errmsg_user_exist(GtkBuilder *builder);
void mx_delete_row_room(GtkListBoxRow *row, GtkBuilder *builder);
void mx_set_default_room_sett(GtkBuilder *builder);
void mx_set_current_room_sett(GtkBuilder *builder);
void mx_gupd_room_desc(guint64 id, char *desc, GtkBuilder *builder);
void mx_gupd_room_name(guint64 id, char *name, GtkBuilder *builder);
void mx_gupd_room_power(guint64 id, gdouble value, GtkBuilder *builder);
void mx_gdel_room(guint64 id, GtkBuilder *builder);
void mx_gdel_msg(guint64 msg_id, guint64 room_id, GtkBuilder *builder);
void mx_gupd_msg_text(guint64 msg_id, guint64 room_id,
                      char *text, GtkBuilder *builder);
void mx_gupd_msg_power(guint64 msg_id, guint64 room_id,
                       gdouble power, GtkBuilder *builder);
void mx_reset_messege_room(t_groom *new_selected, GtkBuilder *builder);
void mx_reset_room_for_search(GtkBuilder *builder);
void mx_hide_msg_editing(GtkButton *btn, GtkBuilder *builder);
void mx_set_room_widgets_visibility(GtkBuilder *builder, gboolean visibility);
void mx_switch_room_header(GtkBuilder *builder, gint page_index);
void mx_unselect_curr_room_messages(GtkBuilder *builder);
void mx_select_msg(gpointer *eventbox, gpointer *event, t_signal_data *data);
GtkWidget *mx_create_reg_message_row(t_gmsg *gmsg,
                                     gboolean is_own, t_chat *chat);
GtkWidget *mx_msgcreate_eventbox();
GtkWidget *mx_msgcreate_box_main(GtkWidget *eventbox, gboolean is_own);
void mx_msgcreate_box_info(GtkWidget *box_main, t_gmsg *gmsg,
                           gboolean is_own, t_chat *chat);
void mx_msgcreate_label_login(GtkWidget *box_main, t_gmsg *gmsg);
void mx_msgcreate_label_text(GtkWidget *box_info,
                             t_gmsg *gmsg, gboolean is_own);
void mx_msgcreate_img_sticker(GtkWidget *box_info,
                              t_gmsg *gmsg, gboolean is_own);
void mx_msgcreate_file(GtkWidget *box_info, t_gmsg *gmsg,
                       gboolean is_own, t_chat *chat);
GtkWidget *mx_create_message_row(t_chat *chat, t_gmsg *gmsg);
void mx_msgcreate_box_energy(GtkWidget *box_status, t_gmsg *gmsg);
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
void mx_set_room_members(GtkBuilder *builder, t_groom *groom);
void mx_show_user_info(GtkBuilder *builder, gchar *login, gchar *desc);
void mx_gupd_clear_history(GtkBuilder *builder, guint64 room_id);
void mx_search_members(GtkBuilder *builder, gchar *search_login);
gboolean mx_stop_search_members(gpointer *entry,
                                gpointer *data, GtkBuilder *builder);
void mx_msgcreate_own_content(GtkWidget *box_info,
                              t_gmsg *gmsg, t_chat *chat);

void mx_msgcreate_content(GtkWidget *box_main, GtkWidget *box_info,
                          t_gmsg *gmsg, t_chat *chat);
t_groom *mx_init_groom(void);
void mx_add_messages_box(t_groom *room, t_chat *chat);
void mx_add_to_sett_members(gint *key,
                            gchar *value, GtkBuilder *builder);
void mx_add_to_info_members(gint *key,
                            gchar *value, GtkBuilder *builder);
void mx_reset_select_count(t_groom *groom);
void mx_open_files_dir(GtkButton *btn, t_chat *chat);
void mx_req_send_message(GtkButton *btn, t_chat *chat);
void mx_req_edit_message(GtkButton *btn, t_chat *chat) ;

/*
 * Gui utils
 */
void mx_scrlldwnd_connect(gchar *name, GtkWidget *scroll, GtkBuilder *builder,
                          t_groom *room);
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
t_groom *mx_get_groom_by_id(guint64 room_id, GtkBuilder *builder);
gboolean mx_is_same_groom(t_groom *groom, GtkBuilder *builder);
t_gmsg *mx_get_selected_gmsg(GtkBuilder *builder);
t_gmsg *mx_get_gmsg_by_id(guint64 msg_id, guint64 room_id,
                          GtkBuilder *builder);
void mx_unselect_room(t_groom *groom, GtkBuilder *builder);
void mx_entry_set_icon_by_path(GtkEntry *entry, gchar *path,
                               GtkEntryIconPosition icon_pos);
t_signal_data *mx_create_sigdata(t_chat *chat, t_groom *groom,
                                 GtkListBoxRow *row_msg);
void mx_free_sigdata(t_signal_data *data);
char *mx_msgpage_name(gint id);
gboolean mx_widget_is_visible(gchar *widget_name, GtkBuilder *builder);
void mx_widget_set_class(GtkWidget *widget, gchar *class);
void mx_widget_remove_class(GtkWidget *widget, gchar *class);
t_filter_data *mx_create_filter_data(gchar *search_name);
void mx_free_filter_data(t_filter_data *filter_data);
gchar *mx_get_string_time(guint64 miliseconds, gint8 format);
void mx_connect_set_placeholder(t_chat *chat);
void mx_connect_unset_placeholder(t_chat *chat);
void mx_connect_addroom(t_chat *chat);
void mx_connect_send_message(t_chat *chat);
void mx_connect_profile_settings(t_chat *chat);
void mx_connect_room_settings(t_chat *chat);
void mx_connect_message_ctrl(t_chat *chat);
void mx_connect_authorization(t_chat *chat);
void mx_connect_search(t_chat *chat);
void mx_connect_join_to_room(t_chat *chat);
void mx_connect_stickers(t_chat *chat);
void mx_connect_ban_member(t_chat *chat);
void mx_connect_filechooser(t_chat *chat);
gchar *mx_get_filename(gchar *full_name);
gboolean mx_is_file_image(gchar *filename);
gboolean mx_is_file_animation(gchar *filename);
void mx_trim_message(gchar **message);
void mx_label_set_num(gchar *widgetname, GtkBuilder *builder, gint number);

/*
 * Gui callbacks
 */
void mx_show_edit_msg(GtkButton *btn, t_chat *chat);
void mx_delete_selected_msgs(GtkButton *btn, t_chat *chat);
void mx_unselect_msg(GtkButton *btn, GtkBuilder *builder);
void mx_req_get_member_info(GObject *popup, t_chat *chat);
void mx_req_edit_desc(GtkButton *btn, t_chat *chat);
void mx_req_logout(GtkButton *btn, t_chat *chat);
void mx_set_profile_info(GtkButton *btn, t_chat *chat);
void mx_set_room_sett(GtkButton *btn, t_chat *chat);
void mx_req_room_sett(GtkButton *btn, t_chat *chat);
void mx_req_room_clear(GtkButton *btn, t_chat *chat);
void mx_req_room_del(GtkButton *btn, t_chat *chat);
void mx_start_search_room(GtkSearchEntry *sentry, t_chat *chat);
void mx_start_search_msgs(GtkSearchEntry *sentry, t_chat *chat);
void mx_start_search_members(GtkSearchEntry *sentry, t_chat *chat);
void mx_reset_addroom(GtkButton *btn, GtkBuilder *builder);
void mx_set_current_room_sett(GtkBuilder *builder);
void mx_select_room(GtkWidget *event_box, GdkEventButton *event,
                    gpointer *user_data);
void mx_show_join_to_room(GtkWidget *event_box, GdkEventButton *event,
                          gpointer *user_data);
void mx_send_message_handle_enter(GtkTextView *textview,
                                  GdkEvent *event, t_chat *chat);
void mx_send_message_handle_shift(GtkWidget *textview,
                                  GdkEvent *event, t_chat *chat);

void mx_send_auth_request(char *login, char *password,
                          t_chat *chat, t_request_type request_type);
void mx_css_connect(char *theme, t_chat *chat);
void mx_css_connect_from_file(t_chat *chat);
void mx_connect_theme_switcher(t_chat *chat);
void change_theme_icon(t_chat *chat, gchar *icon_name);
gchar *mx_format_text(gchar *text);
gdouble mx_get_used_power(guint64 chars);


/* UNIT-TEST Utils */

void mx_activate_content_test(GtkWidget *window, t_chat *chat);
int mx_gui_unit_test(t_chat *chat, int argc, char **argv);
gchar *mx_get_text_from_buffer(GtkTextBuffer *buffer);
void mx_get_buffer_text_unit(GtkButton *btn, t_chat *chat);
