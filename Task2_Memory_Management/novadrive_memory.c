#include <stdio.h>

#define FRAME_SIZE 3
#define TOTAL_PAGES 10

// Page reference string
int pages[TOTAL_PAGES] = {1, 2, 3, 2, 4, 1, 5, 2, 1, 3};

// Physical memory frames
int frames[FRAME_SIZE];
int recent[FRAME_SIZE];

//adding the data names 
const char *dataNames[] =
{
    "",
    "Navigation Data",
    "GPS Cache",
    "Sensor Data",
    "Camera Buffer",
    "Speed Control Data"
};

// Points to the next frame to replace
int nextFrame = 0;

// Display memory frames
void showFrames()
{
    printf("Current Memory Frames: ");

    for (int i = 0; i < FRAME_SIZE; i++)
    {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }

    printf("\n");
}

// Check if a page already exists in memory
int pageExists(int page)
{
    for (int i = 0; i < FRAME_SIZE; i++)
    {
        if (frames[i] == page)
        {
            return 1;
        }
    }

    return 0;
}

void resetFrames()
{
    for(int i = 0; i < FRAME_SIZE; i++)
    {
        frames[i] = -1;
        recent[i] = -1;
    }
}

// FIFO Page Replacement
void fifoPageReplacement()
{
    printf("\nFIFO Page Replacement\n\n");
    
    int pageHits = 0;
    int pageFaults = 0;
    
    for (int i = 0; i < TOTAL_PAGES; i++)
    {
        int page = pages[i];

        if (pageExists(page))
        {
           pageHits++;
           printf("Accessing %s -> Hit\n", dataNames[page]);
        }
        else
        {   
            pageFaults++;
            printf("Accessing %s -> Page Fault\n", dataNames[page]);

            frames[nextFrame] = page;
            nextFrame = (nextFrame + 1) % FRAME_SIZE;
        }

        showFrames();
        printf("\n");
    }
    printf("\nPage Hits   : %d\n", pageHits);
    printf("Page Faults : %d\n", pageFaults);
}

void lruPageReplacement()
{
    printf("\nLRU Page Replacement\n\n");

    resetFrames();

    int pageHits = 0;
    int pageFaults = 0;

    for(int time = 0; time < TOTAL_PAGES; time++)
    {
        int page = pages[time];
        int found = 0;

        // Check if page exists
        for(int i = 0; i < FRAME_SIZE; i++)
        {
            if(frames[i] == page)
            {
               found = 1;
               recent[i] = time;
               break;
             }
         }

         if(found)
         {
            pageHits++;
            printf("Accessing %s -> Hit\n", dataNames[page]);
         }
         else
         {
             pageFaults++;
             printf("Accessing %s -> Page Fault\n", dataNames[page]);
             int replace = -1;

             //To fFind an empty frame
             for(int i = 0; i < FRAME_SIZE; i++)
             {
                 if(frames[i] == -1)
                 {
                    replace = i;
                    break;
                  }
              }

              // If memory is full, replace the least recently used page
              if(replace == -1)
              {
                  replace = 0;

                  for(int i = 1; i < FRAME_SIZE; i++)
                  {
                      if(recent[i] < recent[replace])
                      {
                         replace = i;
                      }
                   }
              }

              frames[replace] = page;
              recent[replace] = time;
         }

         showFrames();
         printf("\n");
    }

    printf("\n");
    printf("Page Hits   : %d\n", pageHits);
    printf("Page Faults : %d\n", pageFaults);
    resetFrames();

    
}

int main()
{
    printf("NovaDrive Memory Management Simulation\n\n");

    // Initialize all frames as empty
    //for (int i = 0; i < FRAME_SIZE; i++)
    //{
      //  frames[i] = -1;
    //}
    resetFrames();

    printf("Page Reference String:\n");
    printf("\nNovaDrive Data Mapping\n");
    printf("----------------------------\n");

    for (int i = 0; i < TOTAL_PAGES; i++)
    {
        printf("%d ", pages[i]);
    }

    printf("\n\n");

    showFrames();

    fifoPageReplacement();
    lruPageReplacement();
    return 0;
}
