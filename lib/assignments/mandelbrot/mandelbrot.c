/*
 *  mandlebrot.c
 *  HS1917 serve that 512x512 Mandelbrot fractal BMP image...
 *
 *  Created by Tim LambertLucas on 02/04/12.
 *  Touched/Bettered by Lucas Barbosa on 16/04/17.
 *  Containing code created by Richard Buckland on 28/01/11.
 *  Copyright 2012 Licensed under Creative Commons SA-BY-NC 3.0. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include <unistd.h>
#include <netinet/in.h>

#include "pixelColor.h"
#include "mandelbrot.h"

//=============SERVER & CLIENT=============//

inline int  waitForConnection (int serverSocket);
inline int  makeServerSocket  (int portno);
inline void serveBMP          (int socket, double x, double y, int z);
static void serveHTML         (int socket);

#define SIMPLE_SERVER_VERSION    1.0
#define REQUEST_BUFFER_SIZE      1000
#define DEFAULT_PORT             1917
#define NUMBER_OF_PAGES_TO_SERVE 10
#define BYTES_PER_PIXEL          3
#define BITS_PER_PIXEL           (BYTES_PER_PIXEL*8)
// after serving this many pages the server will halt

//=========================================//

#define TRUE       1
#define FALSE      0
#define NULLBYTE   1
#define ALL_POINTS 3

//================URL PARSING==============//

typedef struct _triordinates_of_plane_and_zoom_level {
   double x;
   double y;
   int    z;
} triordinate;

//================MANDELBROT===============//

#define MAX_STEPS       256
#define MAX_DISTANCE    2
#define ORIGIN          0
#define MAX_PLANE_WIDTH 512
#define NEXT_PIXEL      1
#define NEW_COL         0
#define NEW_ROW         0
#define NEXT_COL        1
#define NEXT_ROW        1
#define HALF            2

typedef struct _a_complex_number {
    double real;
    double imaginary;
} ComplexNumber;

inline double square       (double base);
inline double euclidean    (double x1, double y1, double x2, double y2);

//==================MAIN===================//

int main (int argc, char *argv[]) {
   
    printf ("\n/===//===//===//===//===//===//===//===//===//===//===/\n");
    printf ("Starting simple server %f\n", SIMPLE_SERVER_VERSION);
    printf ("Serving pixels since 1965\n");   
    int serverSocket = makeServerSocket (DEFAULT_PORT);   
    printf ("Access this server at http://localhost:%d/\n", DEFAULT_PORT);
    printf ("/===//===//===//===//===//===//===//===//===//===//===/\n\n");
    
    char request[REQUEST_BUFFER_SIZE];
    int clientServed = 0;

    while (TRUE) {
      
        int connectionSocket = waitForConnection (serverSocket);
        // wait for a request to be sent from a web browser, open a new
        // connection for this conversation

        // read the first line of the request sent by the browser  
        int bytesRead;
        bytesRead = read (connectionSocket, request, (sizeof request) 
                          - NULLBYTE);
        assert (bytesRead >= 0); 

        // print entire request to the console 
        printf ("=== Received http request ===\n %s\n", request);

        //send the browser a simple html page using http
        printf ("=== Sending http response ===\n");
        printf ("Total clients served: %d\n", clientServed);
        
        // parse URL
        char *msgToken = strtok(request, "/");
        msgToken = strtok(NULL, "/");
        triordinate ParsedPoints;

        int parsedResult = sscanf(msgToken, "tile_x%lf_y%lf_z%d.bmp", 
                        &ParsedPoints.x, &ParsedPoints.y, &ParsedPoints.z);

        if (parsedResult == ALL_POINTS) {
            serveBMP(connectionSocket, ParsedPoints.x, ParsedPoints.y, 
                     ParsedPoints.z);
        } else {
            serveHTML(connectionSocket);
        }

        // close the connection after sending the page- keep aust beautiful
        close(connectionSocket);
        clientServed++;

   } 
   
   // close the server connection after we are done- keep aust beautiful
   printf ("** shutting down the server **\n");
   close (serverSocket);
   
   return EXIT_SUCCESS; 
}

//=============SERVER & CLIENT=============//

inline void serveBMP (int socket, double inX, double inY, int zoom) {
    
    printf("Coordinates are: %lf, %lf, %d\n", inX, inY, zoom);

    // 1) Send HTTP response message
    char *httpMSG = "HTTP/1.0 200 OK\r\n"
                    "Content-Type: image/bmp\r\n"
                    "\r\n";
    write(socket, httpMSG, strlen(httpMSG));

    // 2) prepare the BMP header (54 bytes)
    unsigned char BMPDefaultHeader[] = {
        'B' , 'M' , 0x5a, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
        0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 
        0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x20, 0x00, 0x36, 0x00, 0x0b, 0x13,
        0x00, 0x00, 0x0b, 0x13, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };

    write(socket, BMPDefaultHeader, sizeof(BMPDefaultHeader));

    // 3) now send the BMP data with exquiseteeeee mandelbrot art
    int totalBytes = MAX_PLANE_WIDTH * MAX_PLANE_WIDTH * BYTES_PER_PIXEL;
    unsigned char bmpData[totalBytes];

    /* 
     *  Multiply every new pixel with the custom distance between pixels.
     *  Distance between pixels = 1 / 2^zoom
     *  [s = 2^-z]
     */

    double distance_per_pixel = 1 / pow(2, zoom);

    int row = 0, col = 0;
    double mandelX, mandelY;
    int pixelPosition = 0;

    /*
    image/bmp format model...
    --------------------------  ^
    |0x0h|0x1h|0x2h|0x3h|0x4h|  | row (y)
    --------------------------  |
    |0x5h|0x6h|0x7h|0x8h|0x9h|  |
    --------------------------  |
    |0xAh|0xBh|0xCh|0xDh|0xEh|  |
    --------------------------  |
    ____________________________|
    col (x)                      0
    */

    while(row < MAX_PLANE_WIDTH) {

        // process new row

        col = NEW_COL;  // reset column index once previous row is finished

        while (col < MAX_PLANE_WIDTH) {
            
            // center pixel (point) relative to zoom:
            mandelX = inX - (MAX_PLANE_WIDTH / HALF) * distance_per_pixel;
            mandelY = inY - (MAX_PLANE_WIDTH / HALF) * distance_per_pixel;

            /*
             *  re-adjust pixel's location relative to:
             *  (coordinates * distance), obviously keep accumilating the
             *  values based on the current column and row, as the loop 
             *  processes each byte. After all we don't wanna be stuck on 
             *  the same set of bytes for the entire Mandelbrot set.
             */

            mandelX += col * distance_per_pixel;
            mandelY += row * distance_per_pixel;

            int steps = escapeSteps(mandelX, mandelY);
            //printf("X:%lf, Y:%lf, Steps:%d\n", mandelX, mandelY, steps);
              
            // colour in me pixelssssss  
            bmpData[pixelPosition] = stepsToRed   (steps);
            pixelPosition += NEXT_PIXEL;
            bmpData[pixelPosition] = stepsToGreen (steps);
            pixelPosition += NEXT_PIXEL; 
            bmpData[pixelPosition] = stepsToBlue  (steps);
            pixelPosition += NEXT_PIXEL;

            // shift the current x coordinate to the next, lets move on!
            mandelX += distance_per_pixel;

            col += NEXT_COL;

        }

        // process brand new shiny column
        
        /*
         *  shift the new y coordinate of the current row
         *  relative to the zoom distance, we're moving up a 512x512 image 
         *  here.
         */

        mandelY -= distance_per_pixel;
        
        row += NEXT_ROW;
    }

    printf("Sending BMP image...\n");
    write (socket, bmpData, sizeof(bmpData));
    // 5) Enjoy the art as the client
}

static void serveHTML (int socket) {
   char* message;
 
   // first send the http response header
   message = "HTTP/1.0 200 Found\n"
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

//================MANDELBROT===============//

int escapeSteps(double x, double y) {
    ComplexNumber Z;
    Z.real      = 0;
    Z.imaginary = 0;

    ComplexNumber C;
    C.real      = x;
    C.imaginary = y;

    int i = 0;
    double dist = 0;
    while ((i < MAX_STEPS) && (dist <= MAX_DISTANCE)) {
        double tmpZReal = Z.real;
        Z.real = square(Z.real) - square(Z.imaginary) + C.real;
        Z.imaginary = 2 * (tmpZReal * Z.imaginary) + C.imaginary;
        dist = euclidean(ORIGIN, ORIGIN, Z.real, Z.imaginary);
        i++;
    }
    int numberOfSteps = i;
    return numberOfSteps;
}

double euclidean(double x1, double y1, double x2, double y2) {
    return sqrt(square(y2 - y1) + square(x2 - x1));
}

double square(double base) {
    return base * base;
}