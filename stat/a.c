#include <stdio.h>
#include <sys/vfs.h>

static long kscale(long b, long bs)
{
    return ( b * (long long) bs + 1024/2 ) / 1024;
}

int main(int argc,char *argv[])
{
    struct statfs sbuf;
    int ret;

    if(argc<2)
    {
        printf("%s [path]\n", argv[0]);
        return 0;
    }

    printf("%s\n", argv[1]);

    if ((ret=statfs(argv[1], &sbuf)) != 0) {
        printf("error![%d]\n",ret);
        return (-1);
    }

    printf(" %9lu %9lu %9lu \n",
            kscale(sbuf.f_blocks, sbuf.f_bsize),
            kscale(sbuf.f_blocks - sbuf.f_bfree, sbuf.f_bsize),
            kscale(sbuf.f_bavail, sbuf.f_bsize));

    return 0;
}
