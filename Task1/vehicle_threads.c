#include <stdio.h>
#include <pthread.h>

// Thread for navigation
void *navigationThread(void *arg)
{
    printf("Navigation Module started.\n");
    printf("Finding the best route.\n");
    printf("Navigation completed.\n");
    return NULL;
}

// Thread for obstacle detection
void *obstacleThread(void *arg)
{
    printf("Obstacle Detection Module started.\n");
    printf("Checking nearby objects.\n");
    printf("Road is clear.\n");
    return NULL;
}

// Thread for speed control
void *speedThread(void *arg)
{
    printf("Speed Control Module started.\n");
    printf("Maintaining safe speed.\n");
    printf("Speed check completed.\n");
    return NULL;
}

int main()
{
    // Creating thread variables
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    printf("Starting Vehicle Control System...\n\n");

    // Creating three threads
    pthread_create(&thread1, NULL, navigationThread, NULL);
    pthread_create(&thread2, NULL, obstacleThread, NULL);
    pthread_create(&thread3, NULL, speedThread, NULL);

    // Waiting for all threads to  finish   
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("\nAll vehicle modules completed.\n");

    return 0;
}
