/*
*  simpleServer.c
*  1917 lab 4
*
*  Richard Buckland 28/01/11, 30/3/14.
*  Licensed under Creative Commons SA-BY-NC 3.0, share freely.
*
*/
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <netinet/in.h>
#include <unistd.h>
 
int waitForConnection (int serverSocket);
int makeServerSocket (int portno);
void serveHTML (int socket);
 
#define SIMPLE_SERVER_VERSION 2.0
#define REQUEST_BUFFER_SIZE 1000
#define DEFAULT_PORT 7191
#define NUMBER_OF_PAGES_TO_SERVE 10
// after serving this many pages the server will halt
 
int main (int argc, char* argv[]) {
 
    printf ("************************************\n");
    printf ("Starting simple server %f\n", SIMPLE_SERVER_VERSION);
    printf ("Serving poetry since 2011\n");
    printf ("Access this server at http://localhost:%d/\n", DEFAULT_PORT);
    printf ("************************************\n");
 
    int serverSocket = makeServerSocket(DEFAULT_PORT);
    // holds the actual request
    char request[REQUEST_BUFFER_SIZE];
    int numberServed = 0;
    while (numberServed < NUMBER_OF_PAGES_TO_SERVE) {
        printf ("*** So far served %d pages ***\n", numberServed);
 
        // STEP 1. wait for a request to be sent from a web browser, 
        // then open a new connection for this conversation
        int connectionSocket = waitForConnection(serverSocket);
 
        // STEP 2. read the first line of the request
        int bytesRead = recv (connectionSocket, request, sizeof(request) - 1, 0);
        assert (bytesRead >= 0);
        // check that we were able to read some data from the connection
 
        // echo entire request to the console for debugging
        printf (" *** Received http request ***\n %s\n", request);
 
        // STEP 3. send the browser a simple html page using http
        printf (" *** Sending http response ***\n");
        serveHTML (connectionSocket);
 
        // STEP 4. close the connection after sending the page- keep aust beautiful
        close (connectionSocket);
        ++numberServed;
    }
 
    // close the server connection after we are done- keep aust beautiful
    printf ("** shutting down the server **\n");
    close (serverSocket);
  
    return EXIT_SUCCESS;
}
 
void serveHTML(int socket) {
    const char* message =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "\r\n"
        "<!DOCTYPE html>\n"
        "<html lang=\"en\">\n"
        "  <head>\n"
        "    <meta charset=\"utf-8\"/>\n"
        "    <meta name=\"viewport\" content=\"width=device-width\"/>\n"
        "    <meta name=\"title\" content=\"A Fairy Song\"/>\n"
        "    <meta name=\"author\" content=\"Lucas Barbosa\"/>\n"
        "    <title>A Fairy Song</title>\n"
        "    <link rel=\"icon shortcut\" href=\"http://img.clipartall.com/shakespeare-clipart-shakespeare-clipart-350_417.png\"/>\n"
        "  </head>\n"
        "  <body>\n"
        "  <style>\n"
        "    * {margin: 0; padding: 0;}\n"
        "    [class*=\"poem-container\"]{\n"
        "      display: block;\n"
        "      width: 500px; height: 100vh;\n"
        "      margin: 0 auto;\n"
        "      background: -webkit-linear-gradient(red, yellow);\n"
        "      background: -moz-linear-gradient(red, yellow);\n"
        "      background: -ms-linear-gradient(red, yellow);\n"
        "      background: -o-linear-gradient(red, yellow);\n"
        "      background: linear-gradient(red, yellow);\n"
        "      display: flex;\n"
        "      box-shadow: 0 0 50px 50px #ccc;\n"
        "      /* transitions */\n"
        "      -webkit-transition: all ease 0.33s;\n"
        "      -moz-transition: all ease 0.33s;\n"
        "     -ms-transition: all ease 0.33s;\n"
        "      -o-transition: all ease 0.33s;\n"
        "      transition: all ease 0.33s;\n"
        "      -webkit-animation: pulsate 1s ease-out;\n"
        "      -webkit-animation-iteration-count: 1; }\n"
        "    @-webkit-keyframes pulsate {0%{-webkit-transform: scale(0.01, 0.01); opacity: 0.0;}\n"
        "    50% {opacity: 1.0;} 100% {-webkit-transform: scale(1.0, 1.0); opacity: 1;}}\n"
        "    [class*=\"poem-container\"]:hover {color: #fff;}\n"
        "    [class*=\"poem-content\"]\n"
        "    { width: auto; text-align: left; margin: 30px auto 0; line-height: 20px;}\n"
        "  </style>\n"
        "  <div class=\"poem-container\">\n"
        "    <div class=\"poem-content\">\n"
        "    <h1>A Fairy Song ~ Shakespeare</h1><br><br>\n"
        "      <p>A Fairy Song by William Shakespeare</p>\n"
        "      <p>Over hill, over dale,</p>\n"
        "      <p>Thorough bush, thorough brier,</p>\n"
        "      <p>Over park, over pale,</p>\n"
        "      <p>Thorough flood, thorough fire!</p>\n"
        "      <p>I do wander everywhere,</p>\n"
        "      <p>Swifter than the moon’s sphere;</p>\n"
        "      <p>And I serve the Fairy Queen,</p>\n"
        "      <p>To dew her orbs upon the green;</p>\n"
        "      <p>The cowslips tall her pensioners be;</p>\n"
        "      <p>In their gold coats spots you see;</p>\n"
        "      <p>Those be rubies, fairy favor’s;</p>\n"
        "      <p>In those freckles live their savors;</p>\n"
        "      <p>I must go seek some dewdrops here,</p>\n"
        "      <p>And hang a pearl in every cowslip’s ear.</p>\n"
        "    </div>\n"
        "  </div>\n"
        "  </body>\n"
        "</html>\n";

    // echo the http response to the console for debugging purposes
    printf ("VVVV about to send this via http VVVV\n");
    printf ("%s\n", message);
    printf ("^^^^ end of message ^^^^\n");

    // send the http response to the web browser which requested it
    send (socket, message, strlen(message), 0);
}
 
// start the server listening on the specified port number
int makeServerSocket (int portNumber) {
 
    // create socket
    int serverSocket = socket (AF_INET, SOCK_STREAM, 0);
    assert (serverSocket >= 0);
    // check there was no error in opening the socket
 
    // bind the socket to the listening port  (7191 in this case)
    struct sockaddr_in serverAddress;
    serverAddress.sin_family      = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port        = htons (portNumber);
 
    // tell the server to restart immediately after a previous shutdown
    // even if it looks like the socket is still in use
    // otherwise we might have to wait a little while before rerunning the
    // server once it has stopped
    const int optionValue = 1;
    setsockopt (serverSocket, SOL_SOCKET, SO_REUSEADDR, &optionValue, sizeof (int));
 
    int bindSuccess = bind (serverSocket, (struct sockaddr*)&serverAddress, sizeof (serverAddress));
 
    assert (bindSuccess >= 0);
    // if this assert fails wait a short while to let the operating
    // system clear the port before trying again
 
    return serverSocket;
}
 
// wait for a browser to request a connection,
// returns the socket on which the conversation will take place
int waitForConnection (int serverSocket) {
 
    // listen for a connection
    const int serverMaxBacklog = 10;
    listen (serverSocket, serverMaxBacklog);
 
    // accept the connection
    struct sockaddr_in clientAddress;
    socklen_t clientLen = sizeof (clientAddress);
    int connectionSocket = accept (serverSocket, (struct sockaddr*)&clientAddress, &clientLen);
    assert (connectionSocket >= 0);
    // check for connection error
 
    return connectionSocket;
}

/*
this code calls these external networking functions
try to work out what they do from seeing how they are used,
then google them for full details. 

recv
close
send
socket
setsockopt
bind
listen
accept
*/