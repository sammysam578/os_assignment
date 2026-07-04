#include <stdio.h>
#include <pthread.h>

int completedTasks = 0;

// Thread for navigation
void *navigationThread(void *arg)
{
   for (int i = 0; i < 100000; i++)
    {
        completedTasks++;
    }
    printf("Navigation Module finished.\n");
    return NULL;
}

// Thread for obstacle detection
void *obstacleThread(void *arg)
{
    for (int i = 0; i < 100000; i++)
    {
        completedTasks++;
    }
    printf("Obstacle Detection Module finished.\n");
    return NULL;
}

// Thread for speed control
void *speedThread(void *arg)
{
   for (int i = 0; i < 100000; i++)
    {
        completedTasks++;
    }
    printf("Speed Control Module finished.\n");
    return NULL;
}

int main()
{
    // Creating thread variables
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    printf("NovaDrive Vehicle Control System...\n\n");

    // Creating three threads
    pthread_create(&thread1, NULL, navigationThread, NULL);
    pthread_create(&thread2, NULL, obstacleThread, NULL);
    pthread_create(&thread3, NULL, speedThread, NULL);

    // Waiting for all threads to  finish   
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

    printf("\nCompleted Tasks : %d\n", completedTasks);

    return 0;
}
