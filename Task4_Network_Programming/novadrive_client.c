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

    // Send message
    send(clientSocket, message, strlen(message)+1, 0);

    // Receive reply
    recv(clientSocket, buffer, sizeof(buffer), 0);

    printf("Server Reply : %s\n", buffer);

    close(clientSocket);

    return 0;
}
