#include "client.h"

void mx_msgcreate_own_content(GtkWidget *box_info, t_gmsg *gmsg) {
    if (gmsg->type == DB_TEXT_MSG) {
        mx_widget_set_class(box_info, "box_own_msg_info");
        mx_msgcreate_label_text(box_info, gmsg, TRUE);
    }
    else {
        mx_widget_set_class(box_info, "box_own_sticker_info");
        mx_msgcreate_img_sticker(box_info, gmsg, TRUE);
    }
}

void mx_msgcreate_content(GtkWidget *box_main,
                                 GtkWidget *box_info, t_gmsg *gmsg) {
    if (gmsg->type == DB_TEXT_MSG) {
        mx_widget_set_class(box_info, "box_msg_info");
        mx_msgcreate_label_text(box_info, gmsg, FALSE);
    }
    else {
        mx_widget_set_class(box_info, "box_sticker_info");
        mx_msgcreate_img_sticker(box_info, gmsg, FALSE);
    }
    mx_msgcreate_label_login(box_main, gmsg);
}
