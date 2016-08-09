#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <getopt.h>

char            *dst_host = "localhost";
char            *dst_host2 = "localhost";
int             dst_port    = 0;

void usage(int a)
{
    printf("usage:%d", a);
}

int main(int argc, char **argv)
{
    char            *cpos;
    int             c,tmpport;
    for (;;) {
        c = getopt (argc, argv, "r:h");
        if (c == -1) {
            break;
        }

        switch (c) {

          case 'r':
                // remote [host:]port
                cpos = NULL;
                tmpport = 0;
                if((cpos = strchr(optarg,':'))) {
                    *cpos = '\0';
                    if(optarg && optarg[0])
                        dst_host = optarg;
                    optarg = ++cpos;
                }
                if(optarg && optarg[0]) {
                    tmpport = (int)strtol(optarg, (char **)NULL, 0);
                    if(tmpport) dst_port = tmpport;
                }
                break;

            case '?':
            case 'h':
                usage(0);
                break;
            default:
                usage(1);
                break;
        }
    }
}

