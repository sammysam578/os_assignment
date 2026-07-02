/*
 * Demonstrates the creation and execution of a single POSIX thread.
 */

#include <stdio.h>
#include <pthread.h>

/* Function executed by the thread */
void* workerThread(void* arg)
{
    printf("Worker thread started.\n");

    for (int i = 1; i <= 5; i++)
    {
        printf("Worker thread step %d\n", i);
    }

    printf("Worker thread completed.\n");

    return NULL;
}

int main(void)
{
    pthread_t thread;

    printf("Main thread started.\n");

    /* Create a new thread */
    if (pthread_create(&thread, NULL, workerThread, NULL) != 0)
    {
        printf("Error creating thread.\n");
        return 1;
    }

    /* Wait for thread to finish */
    pthread_join(thread, NULL);

    printf("Main thread finished.\n");

    return 0;
}
