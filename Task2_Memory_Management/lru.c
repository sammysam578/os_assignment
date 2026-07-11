#include <stdio.h>

#define FRAME_SIZE 3
#define TOTAL_PAGES 10

// Page reference string
int pages[TOTAL_PAGES] = {1,2,3,2,4,1,5,2,1,3};

// Memory frames
int frames[FRAME_SIZE];
// Stores recent page usage
int recent[FRAME_SIZE];

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
        recent[i] = -1;
    }

    printf("LRU Page Replacement\n");
   

    for(int i = 0; i < TOTAL_PAGES; i++)
    {
        printf("%d ", pages[i]);
    }

    printf("\n\n");

    showFrames();
    for(int time = 0; time < TOTAL_PAGES; time++)
    {
        int page = pages[time];
        int found = 0;

        // Check whether page already exists
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
           printf("Page %d -> Hit\n", page);
        }
        else
        {
            printf("Page %d -> Page Fault\n", page);

            int replace = -1;

            //Finding empty frame
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
// Display frames after every page reference
showFrames();
printf("\n");
}

return 0;
}
