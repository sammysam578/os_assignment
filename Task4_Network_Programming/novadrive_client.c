/*
    NovaDrive Network Programming
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>

#define PORT 8080

int main()
{
    int clientSocket;

    struct sockaddr_in serverAddress;
    char username[50];
    char password[50];

    char authResponse[100];
    char message[100] = "Hello Server";

    char buffer[100];

    // Create socket
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(clientSocket < 0)
    {
        printf("Socket Creation Failed.\n");
        return 1;
    }

    printf("Client Socket Created Successfully.\n");

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to server
    if(connect(clientSocket,
               (struct sockaddr *)&serverAddress,
               sizeof(serverAddress)) < 0)
    {
        printf("Connection Failed.\n");
        close(clientSocket);
        return 1;
    }

    printf("Connected To Server.\n");
   // Get login details from user
   printf("Username: ");
   scanf("%s", username);
   printf("Password: ");
   scanf("%s", password);
    // Combine username and password
    char loginData[100];

    sprintf(loginData,
           "%s:%s",
           username,
           password);
    // Send login information
    if(send(clientSocket,
            loginData,
            strlen(loginData)+1,
            0) < 0)
     {
     printf("Failed to send login data.\n");
     close(clientSocket);
     return 1;
     }

    // Receive authentication result
    int authReceived = recv(clientSocket,
                        authResponse,
                        sizeof(authResponse)-1,
                        0);
    if(authReceived <= 0)
    {
        printf("Authentication response failed.\n");
        close(clientSocket);
        return 1;
    }

    authResponse[authReceived]='\0';
    printf("%s\n", authResponse);
     // Send message after authentication    
    if(send(clientSocket,
           message,
           strlen(message)+1,
           0) < 0)
    {
    printf("Failed to send message.\n");
    close(clientSocket);
    return 1;
    }
 
    // Receive reply
    int replyReceived = recv(clientSocket,
                         buffer,
                         sizeof(buffer)-1,
                         0);
    if(replyReceived <= 0)
    {
        printf("Server disconnected.\n");
        close(clientSocket);
        return 1;
    }
    buffer[replyReceived]='\0';
    printf("Server Reply : %s\n", buffer);

    close(clientSocket);

    return 0;
}
