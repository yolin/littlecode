#include <stdio.h>
//#include <sys/vfs.h>
//#include "sys/syscall.h"
//#include <linux/unistd.h>

#if 1
typedef struct {
    int val[2];
} __kernel_fsid_t;



struct statfs {
    int f_type;
    int f_bsize;
    unsigned long long f_blocks;
    unsigned long long f_bfree;
    unsigned long long f_bavail;
    unsigned long long f_files;
    unsigned long long f_ffree;
    __kernel_fsid_t f_fsid;
    int f_namelen;
    int f_frsize;
//  int f_flags;
    int f_spare[5];
};

#endif
//#define __NR_mysyscall (__NR_SYSCALL_BASE+378)
//#define mysyscall(a,b) syscall(__NR_mysyscall,(a),(b))

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

//    printf("yolin test mysyscall\n");
//    mysyscall(4,3);


    printf("yolin test statfs call\n");
    int i = statfs(argv[1], &sfs);
    int percent = (sfs.f_blocks - sfs.f_bfree ) * 100 / (sfs.f_blocks - sfs.f_bfree + sfs.f_bavail);

    printf("%s  %llu  %llu  %llu  %d%% \n",  argv[1], bsize*sfs.f_blocks, bsize*(sfs.f_blocks - sfs.f_bfree), bsize*sfs.f_bavail, percent);

    return 0;

}
