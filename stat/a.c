#include <stdio.h>
#include <sys/vfs.h>

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
    printf("size f_blocks[%lu] f_bsize[%lu]\n", sbuf.f_blocks, sbuf.f_bsize);
}
