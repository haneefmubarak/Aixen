#include "heartbeat.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define BUF_SIZE 1024
#define QUEUE_SIZE 10
int heartbeat(int port) {

	//Server stuff
    int serverSocket;
    int clientSocket;
    struct sockaddr_in serverData;
    struct sockaddr_in clientData;
    int clientDataLength;
    char buffer[BUF_SIZE];
    int isServing;
    int isConnectedToClient;
    int bytesReceived;
    int pid;

    // Lets start!
    bzero( &serverData, sizeof( serverData ) );
    serverData.sin_family = AF_INET;
    serverData.sin_addr.s_addr = htonl( INADDR_ANY );
    serverData.sin_port = htons( port );
    serverSocket = socket( PF_INET, SOCK_STREAM, IPPROTO_TCP );

    //bind to address
    int bindResult = bind( serverSocket, (struct sockaddr *)&serverData, sizeof( serverData ) );
    if ( bindResult < 0 ) {
        printf( "Error: Unable to bind socket" );
        close( serverSocket );
    } else if ( listen( serverSocket, QUEUE_SIZE ) < 0 ) {
        // listening for incoming connections failed
        printf( "Error: Unable to listen" );
        close( serverSocket );
    } else {
        //here get the client socket and fork itself
        clientDataLength = sizeof( clientData );

        isServing = 1;
        while ( isServing ) {
            // accept an incoming connection request
            clientSocket = accept( serverSocket,
                                    (struct sockaddr *)&clientData,
                                    &clientDataLength );
            //assert( clientSocket > 0 ); // ensure we have a valid socket

            char *clientAddress = inet_ntoa( clientData.sin_addr );
            int clientPort = ntohs( clientData.sin_port );

            printf( "Accepted Connection from: %s:%d\n", clientAddress, clientPort );

            // fork off into another process
            // this creates another process with the identical program state
            // except that pid == 0 in the child process
            pid = fork( );


            if ( pid == 0 ) {
                // we are the child process
                // close the connection on the listening socket
                // (it's being used by the parent process)
                close( serverSocket );

                isConnectedToClient = 1;
                while ( isConnectedToClient ) {
                    // receive any data from the client
                    bytesReceived = recv( clientSocket, buffer, BUF_SIZE, 0 );

                    // terminate the bytes as a string and print the result
                    buffer[bytesReceived]= '\0';
                    printf( "Received:\n%s\n", buffer );
                    bzero(&buffer,sizeof(buffer));
                    // reply to the client
                    char replyText[] = "Online!";
                    strncpy( buffer, replyText, strlen( replyText ) );
                    printf( "Replying with: %s\n", buffer );

                    send( clientSocket, buffer, strlen( replyText ), 0 );
                }
                // close the connection to the client before exit
                close( clientSocket );

                exit( 0 );
            } else {
                // we are in the parent process

                // close the connection to the client
                // (it's being used by the child process)
                close( clientSocket );
            }
        }
    }

	return 0;
}
