#include "server.h"

static void message_old(sqlite3_str **str) {
    sqlite3_str_appendall(*str, " and date < ?1");
    sqlite3_str_appendall(*str, " order by date desc");
}

static void message_new(sqlite3_str **str) {
    sqlite3_str_appendall(*str, " and date > ?1");
    sqlite3_str_appendall(*str, " order by date asc");
}

static void message_curr(sqlite3_str **str) {
    sqlite3_str_appendall(*str, " order by date desc");
}

gchar *mx_create_request_message_by_id(sqlite3 *db, guint64 room_id,
                                      gint8 type) {
    sqlite3_str *str = sqlite3_str_new(db);
    gchar *request = NULL;
    void (*func[])(sqlite3_str **) = {message_curr, message_new, message_old};

    sqlite3_str_appendf(str, "select * from messages where room_id = %llu",
                        room_id);
    func[type](&str);
    request = sqlite3_str_finish(str);
    return request;
}
