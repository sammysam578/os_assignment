#include <stdio.h>
#include <pthread.h>

/* Navigation Module */
void *navigationThread(void *arg)
{
    printf("Navigation Module is running.\n");
    return NULL;
}

/* Obstacle Detection Module */
void *obstacleThread(void *arg)
{
    printf("Obstacle Detection Module is running.\n");
    return NULL;
}

/* Speed Control Module */
void *speedThread(void *arg)
{
    printf("Speed Control Module is running.\n");
    return NULL;
}

int main()
{
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    printf("Starting Vehicle Control System...\n\n");

    pthread_create(&thread1, NULL, navigationThread, NULL);
    pthread_create(&thread2, NULL, obstacleThread, NULL);
    pthread_create(&thread3, NULL, speedThread, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("\nAll vehicle modules completed.\n");

    return 0;
}
