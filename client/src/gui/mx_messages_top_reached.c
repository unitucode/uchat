#include "client.h"

void mx_box_messages_reached(GtkScrolledWindow *scroll,
                             GtkPositionType pos, t_chat *chat) {
    t_groom *groom = mx_get_selected_groom(chat->builder, MX_LOCAL_ROOMS);

    if (pos == GTK_POS_TOP) {

        puts(groom->room_name);
        puts("NEED OLDER MESSAGE!");
    }
    if (pos == GTK_POS_BOTTOM) {
        puts(groom->room_name);
        puts("CLEAR OLDER MESSAGE!");
    }
    (void)scroll;
}
