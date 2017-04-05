/*
 *  Lucas & Jordan
 *  5/4/17
 *  Testing memory with GCC
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main (int argc, char **argv) {
 
   int canaryA = 42;
   int testArray[10] = {0,1,2,3,4,5,6,7,8,9};
   int canaryB = 99;
      
   printf("[IGNORE]%d\n", canaryA + canaryB);

   int index;

   printf("%p\n", &canaryA);
   printf("%p\n", &canaryB);

   printf ("Enter an array index between 0 and 9\n");
   scanf ("%d", &index);
   printf ("testArray[%d]=%d,\n",index, testArray[index]);

   return EXIT_SUCCESS;

}



