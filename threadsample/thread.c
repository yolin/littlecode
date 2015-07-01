#include <stdio.h>
#include <pthread.h>

#define NUMT 800
#define METHOD_1

static void *pull_one_url(void *i)
{
    printf("I'm thread[%d]\n", (int)i);
#ifdef METHOD_1
    pthread_detach(pthread_self());
#endif
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

#ifdef METHOD_2
            pthread_attr_t attr;
            pthread_attr_init (&attr);
            pthread_attr_setdetachstate (&attr, PTHREAD_CREATE_DETACHED);
            error = pthread_create(&tid[i],
                    &attr,
                    pull_one_url,
                    (void *)i);
            pthread_attr_destroy (&attr);
#else
            error = pthread_create(&tid[i],
                    NULL, /* default attributes please */
                    pull_one_url,
                    (void *)i);
#endif

            if(0 != error)
            {
                fprintf(stderr, "Couldn't run thread number %d, errno %d\n", i, error);
            }
            else
            {
                fprintf(stderr, "Thread %d run ok\n", i);
            }
        }

#ifdef METHOD_3
        // DUT cannot handle over 678 threads, PC cannot handle over 381
        // if use multithread, not recommand
        /* now wait for all threads to terminate */
        for(i=0; i< NUMT; i++) {
            error = pthread_join(tid[i], NULL);
            fprintf(stderr, "Thread %d terminated\n", i);
        }
#endif

        printf("end sleep 5\n");
        sleep(5);
    }

    pthread_exit(NULL);
    return 0;
}
