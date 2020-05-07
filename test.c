#include "sqlite3.h"
#include <stdio.h>

int main () {
    sqlite3* DB;
    int vlad = 0; 
    vlad = sqlite3_open("vlad.db", &DB);

    if (vlad) {
        printf("error open DB");
        return -1;
    }
    else {
        printf("create DB!!!!");
        return 0;
    }
}