#include <stdio.h>
#include <pthread.h>

// all threads using same variable
int completedTasks = 0;

// Mutex is added here for shared variable
pthread_mutex_t lock;

// Mutexes used for deadlock prevention
pthread_mutex_t gpsLock;
pthread_mutex_t sensorLock;

// Thread for navigation
void *navigationThread(void *arg)
{
    printf("Navigation Module started.\n");
    printf("Finding the best route.\n");

    // task counter made 
   for (int i = 0; i < 100000; i++)
    {
        pthread_mutex_lock(&lock);
        completedTasks++;
        pthread_mutex_unlock(&lock);
    }
    printf("Navigation Module finished.\n");
    return NULL;
}

// Thread for obstacle detection
void *obstacleThread(void *arg)
{
    printf("Obstacle Detection Module started.\n");
    printf("Checking nearby objects.\n");
    

    //task counter made
    for (int i = 0; i < 100000; i++)
    {
        pthread_mutex_lock(&lock);
        completedTasks++;
        pthread_mutex_unlock(&lock);
    }
    printf("Obstacle Detection Module finished.\n");
    return NULL;
}

// Thread for speed control
void *speedThread(void *arg)
{
   printf("Speed Control Module started.\n");
   printf("Maintaining safe speed.\n");
   

   //task counter made
   for (int i = 0; i < 100000; i++)
    {
        pthread_mutex_lock(&lock);
        completedTasks++;
        pthread_mutex_unlock(&lock);

    }
    printf("Speed Control Module finished.\n");
    return NULL;
}

// Displaying the  final result
void showResult()
{
    printf("\nCompleted Tasks : %d\n", completedTasks);
    printf("Expected Value  : 300000\n");
    printf("Synchronization with mutex is done for the shared data.\n");
    printf("All modules completed.\n");
}

// Round Robin scheduler
void roundRobinScheduler()
{
    printf("\nRound Robin Scheduler Simulation\n");

    char *processes[] = {
        "Navigation Module",
        "Obstacle Detection Module",
        "Speed Control Module"
    };
    int totalRounds = 3;
    int timeQuantum = 2;

    for (int round = 1; round <= totalRounds; round++)
    {
        printf("Scheduling Round %d\n", round);


        for (int i = 0; i < 3; i++)
        {
          
            printf("%s is running.\n", processes[i]);
            printf("Time Quantum = 2 ms\n");
            printf("%s completed its turn.\n\n", processes[i]);
            printf("Scheduler switched to the next module.\n\n");
        }
    }

    printf("Round Robin scheduling completed.\n");
    printf("All modules received equal CPU time.\n");
}

// Demonstrating deadlock prevention
void deadlockPrevention()
{
    printf("\nDeadlock Prevention\n");

    // Locking resources in the same order
    pthread_mutex_lock(&gpsLock);
    printf("GPS resource locked.\n");

    pthread_mutex_lock(&sensorLock);
    printf("Sensor resource locked.\n");

    printf("Vehicle modules accessed shared resources safely.\n");
    printf("Deadlock was prevented.\n");

    // Unlock in reverse order
    pthread_mutex_unlock(&sensorLock);
    pthread_mutex_unlock(&gpsLock);

    printf("Resources released successfully.\n");
}


int main()
{
    // Creating thread variables
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;

    printf("NovaDrive Vehicle Control System...\n\n");

    // Initialize mutex
    pthread_mutex_init(&lock, NULL);
    
    pthread_mutex_init(&gpsLock, NULL);
    pthread_mutex_init(&sensorLock, NULL);

    // Creating three threads
    pthread_create(&thread1, NULL, navigationThread, NULL);
    pthread_create(&thread2, NULL, obstacleThread, NULL);
    pthread_create(&thread3, NULL, speedThread, NULL);

    // Waiting for all threads to  finish   
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);

 // Destroying mutex
    pthread_mutex_destroy(&lock);

  // Displaying the final results 
    showResult();
    roundRobinScheduler();
    deadlockPrevention();

    pthread_mutex_destroy(&lock);
    pthread_mutex_destroy(&gpsLock);
    pthread_mutex_destroy(&sensorLock);
    return 0;
}
