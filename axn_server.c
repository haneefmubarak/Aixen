#include "axn_server.h"
#include "heartbeat.h"
#include <thread>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#define BUF_SIZE 1024
#define QUEUE_SIZE 10
int serve (int argc, char **argv) {

	// load our params
	int master = 1;
	if (!strcmp(argv[1], "slave-"))
		master = 0;
    // Is following good?
    // master = strcmp(argv[1], "slave-") == 0 ? 1 : 0;
	int heartbeatPort = atoi(argv[2]);
	int peerPort = atoi(argv[3]);
	int clientPort = atoi(argv[4]);

	if (argc == 6)
		char* upstream = strdup(argv[5]);

    std::thread hb (heartbeat,heartbeatPort);

	//Server stuff
    int serverSocket;
    int clientSocket;
    struct sockaddr_in serverData;
    struct sockaddr_in clientData;
    int clientDataLength;
    char buffer[BUF_SIZE];
    bool isServing;
    bool isConnectedToClient;
    int bytesReceived;
    int pid;

    // Lets start!
    bzero( &serverData, sizeof( serverData ) );
    serverData.sin_family = AF_INET;
    serverData.sin_addr.s_addr = htonl( INADDR_ANY );
    serverData.sin_port = htons( peerPort );
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

        isServing = true;
        while ( isServing ) {
            // accept an incoming connection request
            clientSocket = accept( serverSocket,
                                    (struct sockaddr *)&clientData,
                                    &clientDataLength );
            assert( clientSocket > 0 ); // ensure we have a valid socket

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

                isConnectedToClient = true;
                boot authOk;
                while ( isConnectedToClient ) {
                    // receive any data from the client
                    bytesReceived = recv( clientSocket, buffer, BUF_SIZE, 0 );

                    // terminate the bytes as a string and print the result
                    buffer[bytesReceived]= '\0';
                    printf( "Received:\n%s\n", buffer );
                    if(authOk)
                    {

                    // reply to the client
                    char replyText[] = "Packet received!";
                    strncpy( buffer, replyText, strlen( replyText ) );
                    printf( "Replying with: %s\n", buffer );

                    send( clientSocket, buffer, strlen( replyText ), 0 );
                    }
                    else
                        {
                            if(1)// here check user and password
                            {
                                //good
                                authOk = true;
                            }
                            else
                            {
                                // bad - disconnect
                                isConnectedToClient = false;
                            }
                        }

                }
                // close the connection to the client before exit
                close( clientSocket );

                exit( EXIT_SUCCESS );
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
