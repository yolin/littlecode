#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>

int my_system(char *output, int size, char *fmt, ...) {
    int link[2];
    pid_t pid;
    char cmd[1024];
    char buf[4096];
    va_list ap;
    int len=0, outputlen=0;

    if (pipe(link)==-1)
        return -1;

    if ((pid = fork()) == -1)
        return -1;

    if(pid == 0) {
        dup2 (link[1], STDOUT_FILENO); //0:read 1:write, stdout as pip write (link[1])
        close(link[0]);
        close(link[1]);
        va_start(ap, fmt);
        vsnprintf(cmd, sizeof(cmd), fmt, ap);
        va_end(ap);
        system(cmd);
        exit(0);
    } else {
        close(link[1]);
        while(outputlen=read(link[0], buf, sizeof(buf)))
        {
            if(len + outputlen > size)
            {
                //protect
                output[len]='\0';
                break;
            }
            memcpy(output+len, buf, outputlen);
            len += outputlen;
            printf("-->[Yolin:%s:%d:%s]len[%d]\n", __FILE__, __LINE__, __FUNCTION__,len);
        }
        wait(NULL);
    }
    return 0;
}
int main(int argc, const char *argv[])
{
    char buf[43]={0};
    int len;
    
    my_system(buf, sizeof(buf), "ls");

    return 0;
}
