#include <arpa/inet.h>
 
int main() {
    int a = 0x12345678;
    int b = htonl(a);
    if (b == a)
        printf("Big Endian\n");
    else
        printf("Little Endian\n");
    return 0;
}
