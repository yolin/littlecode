#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

int test(const char *fmt, ...)
{
    va_list args;
    const char *args1;

    va_start(args, fmt);
    args1 = va_arg(args,const char *);
    va_end(args);

    printf("fmt=%s args1=%s", fmt, args1);
}

int main
{
    test("arg1", "arg2");
}

