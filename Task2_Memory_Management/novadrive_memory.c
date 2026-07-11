#include <stdio.h>

#define FRAME_SIZE 3
#define TOTAL_PAGES 10

// Page reference string
int pages[TOTAL_PAGES] = {1, 2, 3, 2, 4, 1, 5, 2, 1, 3};

// Physical memory frames
int frames[FRAME_SIZE];
int recent[FRAME_SIZE];
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

    for (int i = 0; i < TOTAL_PAGES; i++)
    {
        int page = pages[i];

        if (pageExists(page))
        {
            printf("Page %d -> Hit\n", page);
        }
        else
        {
            printf("Page %d -> Page Fault\n", page);

            frames[nextFrame] = page;
            nextFrame = (nextFrame + 1) % FRAME_SIZE;
        }

        showFrames();
        printf("\n");
    }
}
void lruPageReplacement()
{
    printf("\nLRU Page Replacement\n\n");

    resetFrames();

    
}

int main()
{
    printf("NovaDrive Memory Management Simulation\n\n");

    // Initialize all frames as empty
    for (int i = 0; i < FRAME_SIZE; i++)
    {
        frames[i] = -1;
    }

    printf("Page Reference String:\n");

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
