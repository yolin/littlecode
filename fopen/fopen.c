#include <stdio.h>
#include <string.h>

int main()
{
    FILE *fp;
    char buf[11]={0};

    fp=fopen("./test", "rw+");

    while(fgets(buf, sizeof(buf), fp) != NULL)
    {
        if (buf[strlen(buf) - 1] == '\n')
            buf[strlen(buf) - 1] = '\0';
        printf("---1--\n");
        printf("%d\n",strlen(buf));
        printf("%s\n",buf);
        printf("---2--\n");
    }
}
