#include <stdio.h>
#include <string.h>

// Default login credentials
char username[] = "admin";
char password[] = "novadrive";

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

   // checks the username and password
    if(strcmp(user, username) == 0 && strcmp(pass, password) == 0)
    {
        printf("\nLogin Successful!\n");
        return 1;
    }

    printf("\nInvalid Username or Password!\n");
    return 0;
}

int main()
{
    // Stop the program if login fails
    if(!login())
        return 0;

    printf("\nSystem Ready.\n");

    return 0;
}
