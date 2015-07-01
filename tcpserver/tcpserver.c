#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h> 

int main(int argc, char *argv[])
{
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr; 

#define MAX_FILE_SIZE 1024000
#define SEG_SIZE 1024

    char sendBuff[SEG_SIZE];
    time_t ticks; 

    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, '0', sizeof(serv_addr));
    memset(sendBuff, '0', sizeof(sendBuff)); 

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(80); 

    int rcvbuf;
    int sndbuf;
    int m=sizeof(rcvbuf);
    int n=sizeof(sndbuf);
    getsockopt(listenfd, SOL_SOCKET, SO_RCVBUF, (void *)&rcvbuf, &m);
    getsockopt(listenfd, SOL_SOCKET, SO_SNDBUF, (void *)&sndbuf, &n);
    printf("socket rcv buffer size [%d]\n", rcvbuf);
    printf("socket snd buffer size [%d]\n", sndbuf);

    bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

    listen(listenfd, 10); 


    FILE *fp;

    while(1)
    {
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL); 

        //ticks = time(NULL);
        //snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));
        int filesize;
        int start=0;
        int segsize;
        int ret;
        char *filebuffer;

        fp=fopen("./tcpfile", "r");

        fseek(fp, 0, SEEK_END);
        filesize = ftell(fp);
        fseek(fp, 0, SEEK_SET);
        printf("filesize=[%d]\n", filesize);

        filebuffer=(char *)malloc(filesize);

        while ((ret = fread(filebuffer, 1, MAX_FILE_SIZE, fp)) != 0)
        {
            start=0;
            printf("ret=[%d]\n", ret);
            printf("start=[%d]\n", start);
            while(start<filesize)
            {
                segsize = filesize - start;
                if(segsize > SEG_SIZE)
                    segsize = SEG_SIZE;

                //if((ret=write(connfd, filebuffer + start, segsize))!=segsize)
                if((ret=send(connfd, filebuffer + start, segsize, 0))!=segsize)
                {
                    printf("send error [%d]\n", ret);
                }

                start+=segsize;
            }
        }

        if(fp)
            fclose(fp);

        if(filebuffer)
            free(filebuffer);

        close(connfd);
        sleep(1);
     }
}
