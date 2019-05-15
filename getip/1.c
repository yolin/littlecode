#include <stdio.h>
#include <unistd.h>
#include <string.h> /* for strncpy */

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>

int main()
{
    int fd;
    struct ifreq ifr;
    char mac[6]={0};

    fd = socket(AF_INET, SOCK_DGRAM, 0);

    /* I want to get an IPv4 IP address */
    ifr.ifr_addr.sa_family = AF_INET;

    /* I want IP address attached to "eth0" */
    strncpy(ifr.ifr_name, "enp2s0", IFNAMSIZ-1);

    ioctl(fd, SIOCGIFADDR, &ifr);

    /* I want mac attached to "eth0" */
    if (ioctl(fd, SIOCGIFHWADDR, (caddr_t)&ifr) < 0) {
        return 1;
    }
    memcpy(mac, ifr.ifr_hwaddr.sa_data, 6);


    close(fd);

    /* display result */
    printf("%s\n", inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
    printf("%.02x:%.02x:%.02x:%.02x:%.02x:%.02x", mac[0]&0xff,mac[1]&0xff,mac[2]&0xff,mac[3]&0xff,mac[4]&0xff,mac[5]&0xff);

    return 0;
}
