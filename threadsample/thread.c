#include <stdio.h>
#include <pthread.h>

#define NUMT 600

static void *pull_one_url(void *i)
{
    printf("I'm thread[%d]\n", i);
    pthread_detach(pthread_self());
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char **argv)
{
    pthread_t tid[NUMT];
    int i;
    int error;

    while(1)
    {
        printf("start\n");

        for(i=0; i< NUMT; i++) {
            error = pthread_create(&tid[i],
                    NULL, /* default attributes please */
                    pull_one_url,
                    (void *)i);
            if(0 != error)
                fprintf(stderr, "Couldn't run thread number %d, errno %d\n", i, error);
            else
                fprintf(stderr, "Thread %d run ok\n", i);
        }

#if 0
        /* now wait for all threads to terminate */
        for(i=0; i< NUMT; i++) {
            error = pthread_join(tid[i], NULL);
            fprintf(stderr, "Thread %d terminated\n", i);
        }
#endif

        printf("end sleep 5\n");
        sleep(5);
    }
    return 0;
}
