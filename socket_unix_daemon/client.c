#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "mylog.h"

int main(void) {

    openlog();
    mylog("111111111");
    closelog();
    return 0;
}
