#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

// PROTOTYPES & STUBS

void swap(int *x, int *y);

int main(void) 
{
	
  int x = 10;
	int y = 3;
	
	printf("%d, %d\n", x, y);
	swap(&x, &y);
	printf("%d, %d\n", x, y);
    
	return 0;
	
}

// FUNCTIONS & DRIVERS

void swap(int *x, int *y) {

	int *tmp;
  *tmp = *x;
	*x = *y;
	*y = *tmp;
	
}


