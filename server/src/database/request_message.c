#include "server.h"

static void message_old(sqlite3_str **str) {
    sqlite3_str_appendall(*str, "' WHERE DATE < ?1");
}

static void message_new(sqlite3_str **str) {
    sqlite3_str_appendall(*str, "' WHERE DATE > ?1");
}

static void message_curr(sqlite3_str **str) {
    sqlite3_str_appendall(*str, "'");
}

// to delete
char *mx_create_request_message(sqlite3 *database, char *name_room, int flag) {
    sqlite3_str *str = sqlite3_str_new(database);
    char *request = NULL;
    void (*func[])(sqlite3_str **) = {message_curr, message_new, message_old};

    sqlite3_str_appendall(str, "SELECT * FROM '");
    sqlite3_str_appendall(str, name_room);
    func[flag](&str);
    // sqlite3_str_appendall(str, "' ORDER BY DATE DESC");
    request = sqlite3_str_finish(str);
    return request;
}

char *mx_create_request_message_by_id(sqlite3 *database, 
                                      unsigned long long int id, int flag) {
    sqlite3_str *str = sqlite3_str_new(database);
    char *request = NULL;
    void (*func[])(sqlite3_str **) = {message_curr, message_new, message_old};

    sqlite3_str_appendall(str, "select * from ");
    sqlite3_str_appendf(str, "'room%d", id);
    func[flag](&str);
    sqlite3_str_appendall(str, " order by id_message desc");
    request = sqlite3_str_finish(str);
    return request;
}
