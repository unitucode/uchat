#include "client.h"

void mx_msgcreate_own_content(GtkWidget *box_info,
                              t_gmsg *gmsg, t_chat *chat) {
    if (gmsg->type == DB_TEXT_MSG) {
        mx_widget_set_class(box_info, "box_own_msg_info");
        mx_msgcreate_label_text(box_info, gmsg, TRUE);
    }
    else if (gmsg->type == DB_STICKER) {
        mx_widget_set_class(box_info, "box_own_sticker_info");
        mx_msgcreate_img_sticker(box_info, gmsg, TRUE);
    }
    else {
        mx_widget_set_class(box_info, "box_own_file_info");
        mx_msgcreate_file(box_info, gmsg, TRUE, chat);
    }
}

void mx_msgcreate_content(GtkWidget *box_main, GtkWidget *box_info,
                          t_gmsg *gmsg, t_chat *chat) {
    if (gmsg->type == DB_TEXT_MSG) {
        mx_widget_set_class(box_info, "box_msg_info");
        mx_msgcreate_label_text(box_info, gmsg, FALSE);
    }
    else if (gmsg->type == DB_STICKER) {
        mx_widget_set_class(box_info, "box_sticker_info");
        mx_msgcreate_img_sticker(box_info, gmsg, FALSE);
    }
    else {
        mx_widget_set_class(box_info, "box_file_info");
        mx_msgcreate_file(box_info, gmsg, FALSE, chat);
    }
    mx_msgcreate_label_login(box_main, gmsg);
}
