#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include <malloc/malloc.h>
#include <stdlib.h>

void Printf(char *format, ...) {
    va_list ap;
    va_start(ap, format);
    char *p;
    int *number;
    for(p=format; *p; p++){
        if (*p!='%')
            putchar(*p);
        else {
            switch (*++p)
            {
            case 'd':
                *number = va_arg(ap, int);
                char *str;
                puts(itoa(number, str 10));
                break;
            default:
                break;
            }
        }
    }
    va_end(ap);
}

int main() {
}
