// Lucas Barbosa
// 24/03/2017
// Program to print out wonderous numbers 

#include <stdio.h>
#include <stdlib.h>

int printWondrous (int start);

int main(int argc, char **argv) {
   
   printWondrous(3);
   return EXIT_SUCCESS;
   
}

int printWondrous (int start) {
   
   /*
    *  counter = 1;
    *  wonderousNumber = start;
    *
    *  WHILE wonderousNumber <> 1
    *    IF number is even THEN
    *       next term = half the current term
    *    ENDIF
    *    IF number is odd THEN
    *       next term = 3 timers current term plus 1
    *    ENDIF
    *    counter = counter + 1
    *  ENDWHILE
    *
    */
    
   int counter = 1;
   int wonderousNumber = start;
   
   printf("%d ", start); 
    
   while(wonderousNumber != 1) {
      if (wonderousNumber % 2 == 0) {
         wonderousNumber /= 2;
      } else {
         wonderousNumber = (wonderousNumber * 3) + 1;
      } 
      
      printf("%d ", wonderousNumber);
      counter += 1;  
   }
   printf("\n");
   return counter;
}