#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int v4tov6(char *mac_addr, char* output)
{
	char *pch = NULL, *saveptr = NULL, *delim=":";
	char link_locoal[64] = "fe80::", tmp[6][3];
	int i = 0, buf = 0;

	pch = strtok_r(mac_addr, delim, &saveptr);
	while (pch != NULL )
	{
        printf("-->[Yolin] %s\n", pch);
		sprintf(tmp[i], "%s", pch);
		pch = strtok_r(NULL, delim, &saveptr);
		i++;
	}
	buf = (int)strtol(tmp[0], NULL, 16);

	sprintf(output, "fe80::%x%s:%sff:fe%s:%s%s", (buf ^ (1 << 1)), tmp[1], tmp[2], tmp[3], tmp[4], tmp[5]);

	return 0;
}

int main(int argc, const char *argv[])
{
    char buf[20]={0};
    char mac[20]="00:aa:bb:cc:dd:10";

    printf("-->[Yolin] %s\n", mac);
    v4tov6(mac, buf);
    printf("-->[Yolin:%s:%d:%s] %s\n", __FILE__, __LINE__, __FUNCTION__,buf);
    return 0;
}
