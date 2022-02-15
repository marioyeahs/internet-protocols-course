// Echo server program
#include "headerFiles.h"

#define IP_ADDR "192.168.0.11" //192.168.0.11
#define PORT 8080
#define BUF_SIZE 256

int main(void)
{
    // Declaration and definition
    int listenfd;                  // Listen socket descriptor
    int connectfd;                 // Connecting socket descriptor
    int n;                         // Number of bytes in each reception
    int bytesToRecv;               // Total bytes to receive
    int processID;                 // ID of the child process
    char buffer[256];              // Data buffer
    char *movePtr;                 // Pointer to the buffer
    struct sockaddr_in serverAddr; // Server address
    struct sockaddr_in clientAddr; // Client address
    int clAddrLen;                 // Length of client address
    int  len_rx, len_tx = 0;                     /* received and sent length, in bytes */
    char buff_tx[BUF_SIZE] = "Hello client, I am the server";
    char buff_rx[BUF_SIZE];   /* buffers for reception  */

    // Create listen socket
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
    {
        printf("Failed to create listen socket\n");
        return -1;
    }
    else
    {
        printf("Socket created\n");
    }
    // Bind listen socket to the local address and port, asigna una direccion IP y un puerto al socket
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(IP_ADDR);
    serverAddr.sin_port = htons(PORT);
    if (bind(listenfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) != 0)
    {
        fprintf(stderr, "[SERVER-error]: socket bind failed. %d: %s \n", errno, strerror(errno));
        return -1;
    }
    else
    {
        printf("Socket binded\n");
    }
    // Listen to connection requests
    if (listen(listenfd, 5) != 0)
    {
        printf("Error listen");
    }
    else
    {
        printf("Socket listening on SERV_PORT: %d \n\n", ntohs(serverAddr.sin_port));
    }

    int len = sizeof(clientAddr);
    // Handle the connection
    while(1)
    {
        connectfd = accept(listenfd, (struct sockaddr *)&clientAddr, &len); // tamaño de la direccion socket cliente
        if (connectfd < 0)
        {
            printf("\nFailed to connect\n");
            return -1;
        }
        else
        {
            printf("\nSocket connected\n");
             while(1) /* read data from a client socket till it is closed */ 
            {  
                /* read client message, copy it into buffer */
                len_rx = read(connectfd, buff_rx, sizeof(buff_rx));  
                
                if(len_rx == -1)
                {
                    fprintf(stderr, "[SERVER-error]: connfd cannot be read. %d: %s \n", errno, strerror( errno ));
                }
                else if(len_rx == 0) /* if length is 0 client socket closed, then exit */
                {
                    printf("[SERVER]: client socket closed \n\n");
                    close(connectfd);
                    break; 
                }
                else
                {
                    write(connectfd, buff_tx, strlen(buff_tx));
                    printf("[SERVER]: %s \n", buff_rx);
                }            
            }  
        }
        // processID = fork();
        // if (processID == 0)
        // // Child process
        // {
        //     close(listenfd);
        //     bytesToRecv = 256;
        //     movePtr = buffer;
        //     while ((n = recv(connectfd, movePtr, bytesToRecv, 0)) > 0) //recv, a process receive data from another process on a remote machine, return the # of bytes
        //     {
        //         movePtr = movePtr + n;
        //         bytesToRecv = bytesToRecv - n;
        //     } // End of while
        //     send(connectfd, buffer, 256, 0); //send, proceso envía datos a otro proceso en una máquina remota, return the # of bytes
        //     exit(0);
        // }                 // End of if
        // close(connectfd); // Back to parent process
    }                     // End of while loop
} // End of echo server program