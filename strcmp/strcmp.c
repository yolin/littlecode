#include <string.h>
#include <stdio.h>

main(){
    char *a = "abcdef";
    char *b = "abcdefghijk";
    char *c = "abcd";
    char *d = "abcdef";

    printf("strcmp(a, b) : %d\n", strcmp(a, b));
    printf("strcmp(a, b) : %d\n", strcmp(a, c));
    printf("strcmp(a, b) : %d\n", strcmp(b, c));
    printf("strcmp(a, b) : %d\n", strcmp(a, d));
}
