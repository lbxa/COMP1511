#include <stdio.h>
#include <stdlib.h>

typedef struct {
   char stack[100];
   int size;
   int items;
} stack_struct;

int main(int argc, char **argv) { 
   
   stack_struct *myStruct = (stack_struct *)malloc(sizeof(myStruct));
   myStruct->size = 5;

	return EXIT_SUCCESS;

}