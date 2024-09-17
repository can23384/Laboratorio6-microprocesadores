#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

void *PrintHello(void *paramID) {
    int *id;
    id = (int *)paramID;
    printf("Hello World! from thread #%d!\n", *id);
    pthread_exit(NULL);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t threadID;
    int rc, t, param;

    for (t = 0; t < NUM_THREADS; t++) {
        printf("In main: creating thread %d\n", t);
        param = t;

        rc = pthread_create(&threadID, NULL, PrintHello, (void *)&param);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }

        rc = pthread_join(threadID, NULL);
        if (rc) {
            printf("ERROR; return code from pthread_join() is %d\n", rc);
            exit(-1);
        }
    }

    printf("All threads completed.\n");
    return 0;
}