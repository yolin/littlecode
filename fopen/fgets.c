#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>

int main(int argc, const char *argv[])
{
    char buf[128] = {0};
    char key[32] = {0};
    char value[64] = {0};
    FILE *fp;
    
    fp = fopen("./test", "r");

    if(fp)
    {
        while (fgets(buf, sizeof(buf), fp))
        {
            if (buf[strlen(buf) - 1] == '\n')
                buf[strlen(buf) - 1] = '\0';

            sscanf(buf, "%[^=]=%s\n", key, value);
            printf("[%s] [%s]\n",key, value);
        }
        fclose(fp);
    }
    return 0;
}
