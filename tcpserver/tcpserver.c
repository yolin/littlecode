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
#include <fcntl.h>
#include <signal.h>
#include <pthread.h> 

char command[50];

void *do_web_server(void *argu) {
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

    //signal(SIGCHLD, SIG_IGN);

    FILE *fp;

    while (1)
    {
        printf("pthread do_webserver:\n");
        connfd = accept(listenfd, (struct sockaddr*)NULL, NULL);    

        printf("copy command!!!\n");
        snprintf(command, sizeof(command), "/littlecode/tcpserver/1.sh");
        printf("copy command[%s]!!!\n",command);

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
    return NULL;    
}    

void *do_command(void *argu) {     // 每隔一秒鐘印出一次 Mary 的函數
    FILE *fp;
    int rc =0 ;
    char result_buf[50];

    while (1) {    

        printf("pthread do_command:\n");
        fp = popen(command, "r");

        if(NULL == fp)
        {
            perror("popen error!");
            exit(1);
        }
        while(fgets(result_buf, sizeof(result_buf), fp) != NULL)
        {
            /*为了下面输出好看些，把命令返回的换行符去掉*/
            if('\n' == result_buf[strlen(result_buf)-1])
            {
                result_buf[strlen(result_buf)-1] = '\0';
            }
            printf("command[%s] output[%s]\n", command, result_buf);
        }

        /*等待命令执行完毕并关闭管道及文件指针*/
        rc = pclose(fp);
        if(-1 == rc)
        {
            perror("pclose error!");
            exit(1);
        }
        else
        {
            printf("command[%s] status[%d] return[%d]\n", command, rc, WEXITSTATUS(rc));
        }
        sleep(1);
    } 
    return NULL;    
}    

int main(int argc, char *argv[])
{

    pthread_t thread1, thread2;     // 宣告兩個執行緒
    pthread_create(&thread1, NULL, &do_web_server, NULL);    // 執行緒 print_george
    pthread_create(&thread2, NULL, &do_command, NULL);    // 執行緒 print_mary
    while (1) {     // 主程式每隔一秒鐘
        printf("----------------\n");    // 就印出分隔行
        sleep(1);     // 停止一秒鐘
    }    



}
