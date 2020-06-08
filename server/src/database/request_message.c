#include "server.h"

static void message_old(sqlite3_str **str) {
    sqlite3_str_appendall(*str, " WHERE DATE < ?1");
}

static void message_new(sqlite3_str **str) {
    sqlite3_str_appendall(*str, " WHERE DATE > ?1");
}

static void message_curr(sqlite3_str **str) {
    str++;
    str--;
}

char *mx_create_request_message(t_db_gmp *pr) {
    sqlite3_str *str = sqlite3_str_new(pr->db);
    char *request = NULL;
    void (*func[])(sqlite3_str **) = {message_curr, message_new, message_old};

    sqlite3_str_appendall(str, "SELECT * FROM ");
    sqlite3_str_appendall(str, pr->name_room);
    func[pr->flag](&str);
    sqlite3_str_appendall(str, " ORDER BY DATE");
    request = sqlite3_str_finish(str);
    return request;
}
