#include <stdio.h>
#include <sys/stat.h>
int main(void)
{
    struct    stat sbuf;
    if (stat("/opt", &sbuf) != 0) {
        return (-1);
    }
    printf("size %lu\n", sizeof(sbuf));
}
