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
    // Server socket descriptor
    int serverSocket;
    int clientSocket;

    // Buffer for receiving client messages
    char buffer[100];

    // Server and client address structures
    struct sockaddr_in serverAddress;
    struct sockaddr_in clientAddress;

    // Stores the size of client address
    socklen_t clientLength = sizeof(clientAddress);

    // Create TCP socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    if(serverSocket < 0)
    {
        printf("Socket Creation Failed.\n");
        return 1;
    }

    printf("Server Socket Created Successfully.\n");

    // Configure server address
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    // Bind socket to port
    if(bind(serverSocket,
            (struct sockaddr *)&serverAddress,
            sizeof(serverAddress)) < 0)
    {
        printf("Bind Failed.\n");
        close(serverSocket);
        return 1;
    }

    printf("Server Bound To Port %d\n", PORT);

    // Listen for incoming connections
    if(listen(serverSocket, 5) < 0)
    {
        printf("Listen Failed.\n");
        close(serverSocket);
        return 1;
    }

    printf("NovaDrive Server Waiting For Client...\n");

    // Accept an incoming client connection
    clientSocket = accept(serverSocket,
                         (struct sockaddr *)&clientAddress,
                         &clientLength);

    if(clientSocket < 0)
    {
       printf("Client Connection Failed.\n");
       close(serverSocket);
       return 1;
    }

    printf("Client Connected Successfully.\n");

    // Receive message from client
    recv(clientSocket, buffer, sizeof(buffer), 0);

    printf("Client Message : %s\n", buffer);

    // Reply to client
    char reply[] = "Hello Client";

    send(clientSocket, reply, strlen(reply) + 1, 0);

    // Close client socket
    close(clientSocket);

    // Close socket
    close(serverSocket);

    return 0;
}
