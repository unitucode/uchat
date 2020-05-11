#include "utils.h"

void mx_delete_user(t_user **user) {
    mx_free((void**)&(*user)->login);
    mx_free((void**)&(*user)->password); 
    mx_free((void**)&(*user)->token); 
    mx_free((void**)user); 
    *user = NULL;
}
