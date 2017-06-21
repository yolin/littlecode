#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define die(e) do { fprintf(stderr, "%s\n", e); exit(EXIT_FAILURE); } while (0);

int main() {
    int link[2];
    pid_t pid;
    char buf[4096];

    if (pipe(link)==-1)
        die("pipe");

    if ((pid = fork()) == -1)
        die("fork");

    if(pid == 0) {

        dup2 (link[1], STDOUT_FILENO); //0:read 1:write, stdout as pip write (link[1])
        close(link[0]);
        close(link[1]);
        execl("/bin/ls", "ls", "-1", (char *)0); //output will goto pip write--> link[1]
        die("execl");

    } else {

        close(link[1]);
        int nbytes = read(link[0], buf, sizeof(buf)); //read pip read
        printf("Output: (%.*s)\n", nbytes, buf);
        wait(NULL);

    }
    return 0;
}
