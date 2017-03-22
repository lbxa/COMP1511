#include <stdio.h>
#include <stdlib.h>

void swap(int *x, int *y);

int main (int argc, char **argv) {

	int x = 5;
	int y = 3;
	
	printf("%d, %d", x, y)
	swap(x, y)
	printf("%d, %d", x, y)
 
	return EXIT_SUCCESS;
	
}

void swap(int *x, int *y) {

	int *tmp = x;
	x = y;
	y = tmp;
	
}
