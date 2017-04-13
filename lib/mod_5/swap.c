#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y);

int main(int argc, char **argv) {
	
   int x = 10;
   int y = 3;
	
	printf("%d, %d\n", x, y);
	swap(&x, &y);
	printf("%d, %d\n", x, y);
    
	return EXIT_SUCCESS;
	
}

void swap(int *x, int *y) {

	int tmp = '\0';
   tmp  = (int)(*x);
   (*x) = (int)(*y);
   (*y) = (int)tmp;

}


