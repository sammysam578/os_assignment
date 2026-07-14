#include <stdio.h>
#include <string.h>

// Maximum number of files
#define MAX_FILES 10

// Default login credentials
char username[] = "admin";
char password[] = "novadrive";

// structure of file 
struct File
{
    char name[30];
    int size;
    char content[100];
};

//  For Storing files
struct File files[MAX_FILES];
int totalFiles = 0;

// User authentication
int login()
{
    char user[20];
    char pass[20];

    printf("===== NovaDrive Secure File System =====\n\n");

    printf("Username: ");
    scanf("%s", user);

    printf("Password: ");
    scanf("%s", pass);

   // checks the username and password for verifying
    if(strcmp(user, username) == 0 &&
       strcmp(pass, password) == 0)
    {
        printf("\nLogin Successful!\n");
        return 1;
    }

    printf("\nInvalid Username or Password!\n");
    return 0;
}

// Creating a new file
void createFile()
{
    if(totalFiles == MAX_FILES)
    {
        printf("\nStorage Full!\n");
        return;
    }

    printf("\nEnter File Name: ");
    scanf("%s", files[totalFiles].name);

    printf("Enter File Size (KB): ");
    scanf("%d", &files[totalFiles].size);

    totalFiles++;

    printf("File Created Successfully.\n");
}

// For Displaying all stored files
void readFiles()
{
    printf("\n===== Stored Files =====\n");

    if(totalFiles == 0)
    {
        printf("No Files Available.\n");
        return;
    }

    for(int i=0;i<totalFiles;i++)
    {
        printf("%d. %s (%d KB)\n",
               i+1,
               files[i].name,
               files[i].size);
    }
}

// Write data into a file
void writeFile()
{
    char fileName[30];

    printf("\nEnter File Name: ");
    scanf("%s", fileName);

    for(int i = 0; i < totalFiles; i++)
    {
        if(strcmp(files[i].name, fileName) == 0)
        {
            printf("Enter File Content: ");

            scanf(" %[^\n]", files[i].content);

            printf("Data Written Successfully.\n");
            return;
        }
    }

    printf("File Not Found.\n");
}

int main()
{
    // Stop the program if login fails
    if(!login())
        return 0;

    
    int choice;

    do
    {
        printf("\n===== NovaDrive Secure File System =====\n");
        printf("1. Create File\n");
        printf("2. Read Files\n");
        printf("3. Write File\n");
        printf("4. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                createFile();
                break;

            case 2:
                readFiles();
                break;

            case 3:
                writeFile();
                break;

            case 4:
                printf("\nExiting System...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    }while(choice != 4);

    return 0;
}
