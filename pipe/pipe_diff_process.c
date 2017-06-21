#include <stdio.h>
#include <unistd.h>

int main() {
    int pipefd[2];
    pipe(pipefd);

    pid_t pid = fork();
    if(pid != 0) {
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        close(pipefd[0]);
        execlp("wc", "wc", "-l", NULL);
    }
    else {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        close(pipefd[1]);

        execlp("ls", "ls", NULL);
    }
    return 0;
}
