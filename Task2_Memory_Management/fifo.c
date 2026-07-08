#include <stdio.h>

#define FRAME_SIZE 3
#define TOTAL_PAGES 10

// Page reference string
int pages[TOTAL_PAGES] = {1, 2, 3, 2, 4, 1, 5, 2, 1, 3};

// Memory frames
int frames[FRAME_SIZE];

// Points to the frame that will be replaced next
int nextFrame = 0;

// Display current frames
void showFrames()
{
    printf("Frames: ");

    for (int i = 0; i < FRAME_SIZE; i++)
    {
        if (frames[i] == -1)
            printf("- ");
        else
            printf("%d ", frames[i]);
    }

    printf("\n");
}

// Check whether page is already loaded
int pageExists(int page)
{
    for (int i = 0; i < FRAME_SIZE; i++)
    {
        if (frames[i] == page)
            return 1;
    }

    return 0;
}

// FIFO Page Replacement
void fifo()
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

int main()
{
    // Initialize frames
    for (int i = 0; i < FRAME_SIZE; i++)
    {
        frames[i] = -1;
    }

    fifo();

    return 0;
}
