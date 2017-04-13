/*
 *  Reverse a string | Lucas Barbosa
 *  12.04.2017
 *  Simple program which reverses string a places it in 
 *  the heap.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define NULLBYTE 1

char *reverse (char *message);

int main (void) {

   printf("%s\n", reverse("Hello there good mam"));

   return EXIT_SUCCESS;
}

char *reverse (char *message) {

   int msglen = strlen(message);
   char *reveredMessage = malloc(msglen + NULLBYTE);

   int index = msglen - NULLBYTE;
   int counter = 0;

   // sometimes you just gotta set that NULLBYTE!
   reveredMessage[msglen] = '\0';

   while (index >= 0) {
      reveredMessage[counter] = (char)message[index];
      counter++;
      index--;  
   }

   return reveredMessage;

}
