#include <stdio.h>
#include <sys/vfs.h>


#define BLOCK_SIZE 4 //k

int main(int argc, char * argv[])
{
    struct statfs sfs;
    int bsize;

    if(argc<2)
    {
        printf("%s [mount point] (block size:default 4k)\n", argv[0]);
        return 0;
    }

    printf("%s\n", argv[1]);

    if(argv[2])
        bsize=atoi(argv[2]);
    else
        bsize=BLOCK_SIZE;

    int i = statfs(argv[1], &sfs);
    int percent = (sfs.f_blocks - sfs.f_bfree ) * 100 / (sfs.f_blocks - sfs.f_bfree + sfs.f_bavail);

    printf("%s  %llu  %llu  %llu  %d%% \n",  argv[1], bsize*sfs.f_blocks, bsize*(sfs.f_blocks - sfs.f_bfree), bsize*sfs.f_bavail, percent);

    return 0;

}
