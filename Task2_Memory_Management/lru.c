#include <stdio.h>

#define FRAME_SIZE 3
#define TOTAL_PAGES 10

// Page reference string
int pages[TOTAL_PAGES] = {1,2,3,2,4,1,5,2,1,3};

// Memory frames
int frames[FRAME_SIZE];

// Display frames
void showFrames()
{
    printf("Frames: ");

    for(int i=0;i<FRAME_SIZE;i++)
    {
        if(frames[i]==-1)
            printf("- ");
        else
            printf("%d ",frames[i]);
    }

    printf("\n");
}

int main()
{
    for(int i=0;i<FRAME_SIZE;i++)
    {
        frames[i]=-1;
    }

    printf("LRU Page Replacement\n");

    showFrames();

    return 0;
}
