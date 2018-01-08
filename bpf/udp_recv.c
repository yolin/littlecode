#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/filter.h>
#include <sys/ioctl.h>

int createSocket(int port)
{
    int fd;
    struct sockaddr_in local_addr;

    if ((fd = socket(PF_INET, SOCK_RAW, IPPROTO_UDP)) < 0) {
        printf("socket open failed!\n");
        exit(1);
    }



struct sock_filter BPF_code[]= {
{ 0x28, 0, 0, 0x0000000c },
{ 0x15, 0, 6, 0x000086dd },
{ 0x30, 0, 0, 0x00000014 },
{ 0x15, 0, 15, 0x00000011 },
{ 0x28, 0, 0, 0x00000036 },
{ 0x15, 12, 0, 0x00001388 },
{ 0x28, 0, 0, 0x00000038 },
{ 0x15, 10, 11, 0x00001388 },
{ 0x15, 0, 10, 0x00000800 },
{ 0x30, 0, 0, 0x00000017 },
{ 0x15, 0, 8, 0x00000011 },
{ 0x28, 0, 0, 0x00000014 },
{ 0x45, 6, 0, 0x00001fff },
{ 0xb1, 0, 0, 0x0000000e },
{ 0x48, 0, 0, 0x0000000e },
{ 0x15, 2, 0, 0x00001388 },
{ 0x48, 0, 0, 0x00000010 },
{ 0x15, 0, 1, 0x00001388 },
{ 0x6, 0, 0, 0x00001000 },
{ 0x6, 0, 0, 0x00000000 },
    };
struct sock_fprog Filter; 
Filter.len = 20;
Filter.filter = BPF_code;


setsockopt(fd, SOL_SOCKET, SO_ATTACH_FILTER, &Filter, sizeof(Filter));


char *opt;
opt = "lo";
setsockopt(fd, SOL_SOCKET, SO_BINDTODEVICE, opt, 2);


    /* int sock_opt = 1; */
    /* if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (void*)&sock_opt, sizeof(sock_opt)) < 0) { */
    /*     printf("setsockopt failed!\n"); */
    /*     exit(1); */
    /* } */


    /* sock_opt = 1; */
    /* if (setsockopt(fd, SOL_SOCKET, SO_REUSEPORT, (void*)&sock_opt, sizeof(sock_opt)) < 0) { */
    /*     printf("setsockopt failed!\n"); */
    /*     exit(1); */
    /* } */


    /* bzero((char *) &local_addr, sizeof(local_addr)); */
    /* local_addr.sin_family = AF_INET; */
    /* local_addr.sin_addr.s_addr = ntohl(INADDR_ANY); */
    /* local_addr.sin_port = htons(port); */

    /* if (bind(fd, (struct sockaddr *)&local_addr, sizeof(local_addr)) < 0) */
    /* { */
    /*     printf("bind failed\n"); */
    /* } */

    return fd;
}

void* worker(void* pfd)
{
    int fd = *(int*)pfd;
    char buffer[1024];

    while (1)
    {
        if (recv(fd, buffer, sizeof(buffer) - 1, 0) < 0)
        {
            printf("udp recv failed!\n");
            exit(1);
        }
        printf("socket %d received: %s\n", fd, buffer);
        //cout << "socket " << fd << " received:" << buffer << endl;
    }
}

int main(int argc, char* argv[])
{
    int *pfd, localPort, peerPort;
    char *peerIP;
    char buffer[1024];
    struct sockaddr_in local_addr, peer_addr;

    if (4 != argc)
    {
        exit(1);
    }

    localPort = atoi(argv[1]);
    peerIP = argv[2];
    peerPort = atoi(argv[3]);

    int i = 0;
    while (1)
    {
        pfd = malloc(sizeof(int));
        *pfd = createSocket(localPort);
        printf("socket %d opened\n", *pfd);

       // if ((i >= 3) && (i < 6))
       // {
       //     bzero((char *) &peer_addr, sizeof(peer_addr));
       //     peer_addr.sin_family = AF_INET;
       //     peer_addr.sin_addr.s_addr = inet_addr(peerIP);
       //     peer_addr.sin_port = htons(peerPort);

       //     if (connect(*pfd , (struct sockaddr *)&peer_addr , sizeof(peer_addr)) < 0)
       //     {
       //         printf("udp connect failed!\n");
       //         exit(1);
       //     }
       // }

        pthread_t workerThread;
        pthread_create(&workerThread, NULL, worker, pfd);
        pthread_detach(workerThread);
        getchar();
        i++;
    }

    return 0;
}
