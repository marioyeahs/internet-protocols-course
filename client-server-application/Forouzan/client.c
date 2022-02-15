// TCP echo client program
#include "headerFiles.h"

#define IP_ADDR "192.168.0.11"
#define PORT 8080

int main(void)
{
    // Declaration and definition
    int fd;               // Socket descriptor
    int n;                // Number of bytes received
    int bytesToRecv;      // Number of bytes to receive
    char sendBuffer[256]; // Send buffer
    char recvBuffer[256]; // Receive buffer
    char *movePtr;        // A pointer the received buffer
    char buf_tx[] = "Hello server. I am a client";      
    char buf_rx[100]; 

    struct sockaddr_in serverAddr; // Server address

    // Create socket
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        printf("Failed to create listen socket\n");
        return -1;
    }
    else
    {
        printf("Socket created\n");
    }
    // Create server socket address
    memset(&serverAddr, 0, sizeof(serverAddr)); //set to 0 each byte of the structure (clear)
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(IP_ADDR);
    inet_pton(AF_INET, IP_ADDR, &serverAddr.sin_addr);
    serverAddr.sin_port = htons(PORT);
    // Connect
    int connectfd = connect(fd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (connectfd != 0)
    {
        printf("Error connecting to server");
        return -1;
    }
    printf("Connected to server %s\n", IP_ADDR);
    /* send test sequences*/
    write(fd, buf_tx, sizeof(buf_tx));
    read(fd, buf_rx, sizeof(buf_rx));
    printf("CLIENT:Received: %s \n", buf_rx);

    /* close the socket */
    close(fd);
    // // Send and receive data
    // fgets(sendBuffer, 256, stdin);
    // send(fd, sendBuffer, strlen(sendBuffer), 0);
    // bytesToRecv = strlen(sendBuffer);
    // movePtr = recvBuffer;
    // while ((n = recv(fd, movePtr, bytesToRecv, 0)) > 0)
    // {
    //     movePtr = movePtr + n;
    //     bytesToRecv = bytesToRecv - n;
    // } // End of while loop
    // recvBuffer[bytesToRecv] = 0;
    // printf("Received from server:");
    // fputs(recvBuffer, stdout);
    // // Close and exit
    // close(fd);
    // exit(0);
} // End of echo client program