/*
 *  mandlebrot.c
 *  1917 serve that 3x3 bmp from lab3 Image activity
 *
 *  Created by Tim Lambert on 02/04/12.
 *  Containing code created by Richard Buckland on 28/01/11.
 *  Copyright 2012 Licensed under Creative Commons SA-BY-NC 3.0. 
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>
#include <math.h>

//=============SERVER & CLIENT=============//

inline int waitForConnection (int serverSocket);
inline int makeServerSocket  (int portno);
inline void serveBMP         (int socket);
static void serveHTML        (int socket);

#define SIMPLE_SERVER_VERSION 1.0
#define REQUEST_BUFFER_SIZE 1000
#define DEFAULT_PORT 1917
#define NUMBER_OF_PAGES_TO_SERVE 10
// after serving this many pages the server will halt

//=========================================//

#define TRUE 1
#define FALSE 0

//================Mandelbrt================//

#define MAX_STEPS 256
#define MAX_DISTANCE 2


//===============URL PARSING===============//

typedef struct _triordinate {
    double x;
    double y;
    int z;
} triordinate;

triordinate extract (char *message);

//=========================================//


int main (int argc, char *argv[]) {
   
    printf ("\n----------------------------------------\n");
    printf ("Starting simple server %f\n", SIMPLE_SERVER_VERSION);
    printf ("Serving pixels since 1965\n");   

    int serverSocket = makeServerSocket (DEFAULT_PORT);   
    printf ("Access this server at http://localhost:%d/\n", DEFAULT_PORT);
    printf ("----------------------------------------\n");

    char request[REQUEST_BUFFER_SIZE];

    int numberServed = 0;
    while (numberServed < NUMBER_OF_PAGES_TO_SERVE) {
      
        printf ("*** So far served %d pages ***\n", numberServed);

        int connectionSocket = waitForConnection (serverSocket);
        // wait for a request to be sent from a web browser, open a new
        // connection for this conversation

        // read the first line of the request sent by the browser  
        int bytesRead;
        bytesRead = read (connectionSocket, request, (sizeof request)-1);
        assert (bytesRead >= 0); 
        // were we able to read any data from the connection?

        // print entire request to the console 
        printf (" *** Received http request ***\n %s\n", request);

        //send the browser a simple html page using http
        printf (" *** Sending http response ***\n");
        serveHTML(connectionSocket);

        // close the connection after sending the page- keep aust beautiful
        close(connectionSocket);

        numberServed++;
   } 
   
   // close the server connection after we are done- keep aust beautiful
   printf ("** shutting down the server **\n");
   close (serverSocket);
   
   return EXIT_SUCCESS; 
}

//=============SERVER & CLIENT=============//

inline void serveBMP (int socket) {

    // now send the BMP
    unsigned char bmp[] = {
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0x00,0x0e,0x07,0x07,0x07,0x66,0x07,0x07,
        0x07,0x07,0x07,0x00,0x00,0x0d,0x07,0x07,
        0x07,0x07,0x07,0x07,0xff,0xff,0xff,0x00,
        0x00,0x0d
    };

    write (socket, bmp, sizeof(bmp));
}

// start the server listening on the specified port number
inline int makeServerSocket (int portNumber) { 
   
    // create socket
    int serverSocket = socket (AF_INET, SOCK_STREAM, 0);
    assert (serverSocket >= 0);   
    // error opening socket

    // bind socket to listening port
    struct sockaddr_in serverAddress;
    memset ((char *) &serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family      = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port        = htons (portNumber);

    // let the server start immediately after a previous shutdown
    int optionValue = 1;
    setsockopt (
        serverSocket,
        SOL_SOCKET,
        SO_REUSEADDR,
        &optionValue, 
        sizeof(int)
    );

    int bindSuccess = 
    bind (
        serverSocket, 
        (struct sockaddr *) &serverAddress,
        sizeof (serverAddress)
    );

    assert (bindSuccess >= 0);
    // if this assert fails wait a short while to let the operating 
    // system clear the port before trying again

    return serverSocket;
}

// wait for a browser to request a connection,
// returns the socket on which the conversation will take place
inline int waitForConnection (int serverSocket) {
    // listen for a connection
    const int serverMaxBacklog = 10;
    listen (serverSocket, serverMaxBacklog);

    // accept the connection
    struct sockaddr_in clientAddress;
    socklen_t clientLen = sizeof (clientAddress);

    int connectionSocket = 
    accept (
        serverSocket, 
        (struct sockaddr *) &clientAddress, 
        &clientLen
    );

    assert (connectionSocket >= 0);
    // error on accept

    return (connectionSocket);
}

static void serveHTML (int socket) {
   char* message;
 
   // first send the http response header
   message =
      "HTTP/1.0 200 Found\n"
      "Content-Type: text/html\n"
      "\n";
   printf ("about to send=> %s\n", message);
   write (socket, message, strlen (message));
 
   message =
      "<!DOCTYPE html>\n"
      "<script src=\"http://almondbread.cse.unsw.edu.au/tiles.js\"></script>"
      "\n";
   write (socket, message, strlen (message));
}

//================Mandelbrt================//

int escapeSteps(double x, double y) {
    int n = 0;
    int ok_flag = TRUE;
    double zx = 0, zy = 0;
    double prevZx, prevZy;
    while ((sqrt((zx*zx)+(zy*zy)) <= MAX_DISTANCE) && ok_flag == TRUE) {
        prevZx = zx;
        prevZy = zy;
        zx = (prevZx*prevZx)-(prevZy*prevZy)+x;
        zy = ((2*prevZx)*prevZy)+y;
        n++;
        if (n >= MAX_STEPS) {
            ok_flag = FALSE;
        }
    }
    return n;
}

//=========================================//
