#include  "server.h"

/*
 * Function:  mx_insert_contact
 * -------------------------------
 * adds an entry to the user contact database
 * 
 * db: closed database structure
 * user_id: user ID of the contact owner
 * contact_id: the user with whom the contact exists
 * type: contact type
 */
void mx_insert_contact(sqlite3 *db, guint64 user_id, guint64 contact_id,
                       gint8 type) {
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gchar *request = NULL;

    mx_delete_contact(db, user_id, contact_id);
    sqlite3_str_appendf(sqlite_str, "insert into contacts(user_id, contact_id,"
                                    " type)values(%llu, %llu, %d)", user_id, 
                        contact_id, type);
    request = sqlite3_str_finish(sqlite_str);
    mx_error_sqlite(sqlite3_exec(db, request, 0, 0, 0), "insert_contact");
    sqlite3_free(request);
}

/*
 * Function: mx_delete_contact
 * -------------------------------
 * deletes a record from users' contact data
 * 
 * db: closed database structure
 * user_id: user ID of the contact owner
 * contact_id: the user with whom the contact exists
 */
void mx_delete_contact(sqlite3 *db, guint64 user_id, guint64 contact_id) {
    sqlite3_str *sqlite_str = sqlite3_str_new(db);
    gchar *request = NULL;

    sqlite3_str_appendf(sqlite_str, "delete from contacts where user_id = %llu"
                                    " and contact_id = %llu",
                        user_id, contact_id);
    request = sqlite3_str_finish(sqlite_str);
    mx_error_sqlite(sqlite3_exec(db, request, 0, 0, 0), "delete contact");
    sqlite3_free(request);
}

/*
 * Function: create_object_contact
 * -------------------------------
 * creates and returns an json object with the contact
 * information it takes from the database using the stmt object
 * 
 * stmt: the sql operator is compiled in binary form
 */
static cJSON *create_object_contact(sqlite3_stmt *stmt) {
    cJSON *contact = cJSON_CreateObject();

    cJSON_AddNumberToObject(contact, "user_id", sqlite3_column_int64(stmt, 0));
    cJSON_AddNumberToObject(contact, "contact_id",
                            sqlite3_column_int64(stmt, 1));
    cJSON_AddNumberToObject(contact, "type", sqlite3_column_int(stmt, 2));
    return contact;
}

/*
 * Function: mx_get_contacts
 * -------------------------------
 * takes from the database all records about
 * the specified type of user contacts and returns in json format
 * 
 * db: closed database structure
 * user_id: user id
 * type: type of contacts
 * 
 * return: json array, if contacts not found return empty array json
 */
cJSON *mx_get_contacts(sqlite3 *db, guint64 user_id, gint8 type) {
    sqlite3_stmt *stmt;
    gint32 rv = SQLITE_OK;
    cJSON *contacts = cJSON_CreateArray();


    rv = sqlite3_prepare_v2(db, "select * from contacts where user_id = ?1 "
                                "and type = ?2", -1, &stmt, 0);
    mx_error_sqlite(rv, "get_contacts");
    sqlite3_bind_int64(stmt, 1, user_id);
    sqlite3_bind_int(stmt, 2, type);
    while ((rv = sqlite3_step(stmt) == SQLITE_ROW))
        cJSON_AddItemToArray(contacts, create_object_contact(stmt));
    mx_error_sqlite(rv, "get_contacts");
    return contacts;
}


