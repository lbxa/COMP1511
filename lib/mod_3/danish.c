// Lucas Barbosa
// 24/03/17
// A simple yet quite redendant program

#include <stdio.h>
#include <stdlib.h>

void showDanish(void);

int main(int argc, char **argv) {
   
   showDanish();
   
   return EXIT_SUCCESS;
   
}

void showDanish(void) {
   
   int counter = 0;
   
   while (counter < 4) {
      
      if (counter == 2) {
         printf("\n");
      }
      
      printf("** *********\n");
      
      counter += 1;
   }
   
}