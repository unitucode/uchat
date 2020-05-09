#include "utils.h"
#include "json.h"

/*
 * Convert all json types to string
 */
static char *val_convert_to_str(json_value *key) {
    char retstr[MX_BUF_SIZE];

    if (key->type == json_string)
        return strdup(key->u.string.ptr);
    else if (key->type == json_integer) {
        sprintf(retstr, "%lld", key->u.integer);
        return  strdup(retstr);
    }
    else if (key->type == json_double) {
        sprintf(retstr, "%f", key->u.dbl);
        return  strdup(retstr);
    }
    else if (key->type == json_boolean) {
        if (key->u.boolean)
            return strdup("true");
        return strdup("false");
    }
    return NULL;
}

/*
 * Return value of key from "config.json" in allocated string format
 */
char *mx_get_config_val(char *key) {
    json_value *json = mx_open_config();
    char *retstr = NULL;

    for (unsigned int i = 0; i < json->u.object.length; i++)
        if (!strcmp(key, json->u.object.values[i].name))
            retstr = val_convert_to_str(json->u.object.values[i].value);
    json_value_free(json);
    return retstr;
}
