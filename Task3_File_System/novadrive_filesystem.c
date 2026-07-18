#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Maximum number of files
#define MAX_FILES 10

// Defult login credentials
char username[] = "admin";
char password[] = "novadrive";

// Stores owner, group and others permissions
struct Permission
{
    char owner[4];
    char group[4];
    char others[4];
};

// Structure representing a file
struct File
{
    char name[30];
    int size;
    char content[100];

    struct Permission permission;
};

//  For Storing files
struct File files[MAX_FILES];
int totalFiles = 0;

// Function prototype for audit logging
void writeLog(char action[], char fileName[]);

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

    // Default file permissions
    strcpy(files[totalFiles].permission.owner, "rwx");
    strcpy(files[totalFiles].permission.group, "r--");
    strcpy(files[totalFiles].permission.others, "---");
   
    // Record file creation in the audit log
    writeLog("Created", files[totalFiles].name);

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
       // Check read permission
       if(strchr(files[i].permission.owner, 'r') == NULL)
       {
            printf("\n%s : Read Permission Denied.\n",
                   files[i].name);
            continue;
       }
        printf("\nFile %d\n", i + 1);
        printf("Name       : %s\n", files[i].name);
        printf("Size       : %d KB\n", files[i].size);
        printf("Owner Permission  : %s\n", files[i].permission.owner);
        printf("Group Permission  : %s\n", files[i].permission.group);
        printf("Others Permission : %s\n", files[i].permission.others);
        printf("Content    : %s\n", files[i].content);
  
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
           // Check write permission
           if(strchr(files[i].permission.owner, 'w') == NULL)
           {
               printf("Write Permission Denied.\n");
               return;
            }
            printf("Enter File Content: ");

            scanf(" %99s", files[i].content);

            printf("Data Written Successfully.\n");
            
            // Record file 
            writeLog("Written", fileName);
            return;
        }
    }

    printf("File Not Found.\n");
}

// Delete an existing file
void deleteFile()
{
    char fileName[30];

    printf("\nEnter File Name: ");
    scanf("%s", fileName);

    for(int i=0;i<totalFiles;i++)
    {
        if(strcmp(files[i].name,fileName)==0)
        {
            for(int j=i;j<totalFiles-1;j++)
            {
                files[j]=files[j+1];
            }

            totalFiles--;

            printf("File Deleted Successfully.\n");
            
            // Record file deletion
            writeLog("Deleted", fileName);
            return;
        }
    }

    printf("File Not Found.\n");
}

// Display permissions of a file
void showPermission()
{
    char fileName[30];

    printf("\nEnter File Name: ");
    scanf("%s", fileName);

    for(int i = 0; i < totalFiles; i++)
    {
        if(strcmp(files[i].name, fileName) == 0)
        {
            printf("\nOwner  : %s\n", files[i].permission.owner);
            printf("Group  : %s\n", files[i].permission.group);
            printf("Others : %s\n", files[i].permission.others);

            return;
        }
    }

    printf("File Not Found.\n");
}

// Change permissions of a file
void changePermission()
{
    char fileName[30];

    printf("\nEnter File Name: ");
    scanf("%s", fileName);

    for(int i = 0; i < totalFiles; i++)
    {
        if(strcmp(files[i].name, fileName) == 0)
        {
            printf("Owner Permission (e.g. rwx): ");
            scanf("%3s", files[i].permission.owner);

            printf("Group Permission (e.g. r--): ");
            scanf("%3s", files[i].permission.group);

            printf("Others Permission (e.g. ---): ");
            scanf("%3s", files[i].permission.others);

            writeLog("Permission Changed", fileName);

            printf("Permissions Updated Successfully.\n");
            return;
        }
    }

    printf("File Not Found.\n");
}

// Encrypt file content using a simple Caesar cipher
void encryptFile()
{
    char fileName[30];

    printf("\nEnter File Name: ");
    scanf("%s", fileName);

    for(int i = 0; i < totalFiles; i++)
    {
        if(strcmp(files[i].name, fileName) == 0)
        {
           // Check write permission
           if(strchr(files[i].permission.owner, 'w') == NULL)
           {
            printf("Write Permission Denied.\n");
            return;
            }
            for(int j = 0; files[i].content[j] != '\0'; j++)
            {
                files[i].content[j]++;
            }

            printf("File Encrypted Successfully.\n");

            // Record encryption in audit log
            writeLog("Encrypted", fileName);

            return;
        }
    }

    printf("File Not Found.\n");
}

// Decrypt file content
void decryptFile()
{
    char fileName[30];

    printf("\nEnter File Name: ");
    scanf("%s", fileName);

    for(int i = 0; i < totalFiles; i++)
    {
        if(strcmp(files[i].name, fileName) == 0)
        {
           // Check write permission
           if(strchr(files[i].permission.owner, 'w') == NULL)
           {
           printf("Write Permission Denied.\n");
           return;
            }
            for(int j = 0; files[i].content[j] != '\0'; j++)
            {
                files[i].content[j]--;
            }

            printf("File Decrypted Successfully.\n");

            // Record decryption in audit log
            writeLog("Decrypted", fileName);

            return;
        }
    }

    printf("File Not Found.\n");
}

// Saving file in audit log
void writeLog(char action[], char fileName[])
{
    FILE *log = fopen("audit.log", "a");

    if(log == NULL)
    {
        printf("Unable to open audit log.\n");
        return;
    }

    fprintf(log, "%s : %s\n", action, fileName);

    fclose(log);
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
        printf("4. Delete File\n");
        printf("5. Show Permissions\n");
        printf("6. Change Permissions\n");
        printf("7. Encrypt File\n");
        printf("8. Decrypt File\n");
        printf("9. Exit\n");

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
                deleteFile();
                break;
            case 5:
                showPermission();
                break;

            case 6:
                changePermission();
                break;

            case 7:
                encryptFile();
                break;

            case 8:
                decryptFile();
                break;

            case 9:
                printf("\nExiting System...\n");
                break;

            default:
                printf("Invalid Choice!\n");
         }

    }while(choice != 9);

    return 0;
}
