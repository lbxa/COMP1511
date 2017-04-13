// Lucas Barbosa
// 23/03/17
// Insertion sorting values via reference

#include <stdio.h>
#include <stdlib.h>

void sort(int *first, int *second, int *third);
void swap(int *x, int *y);

int main(int argc, char **argv) { 

	int first, second, third; 
	scanf ("%d %d %d", &first, &second, &third);
	sort(&first, &second, &third);
   printf("%d\n%d\n%d\n", first, second, third);

	return EXIT_SUCCESS;

}

void sort(int *first, int *second, int *third) {
	
   int array[3];
	array[0] = (*first);
	array[1] = (*second);
	array[2] = (*third);

	for (int i = 0; i < 3; i++) {
		int key = array[i];
		int previousElement = i - 1;

		while ((previousElement >= 0) && (array[previousElement] > key)) {
			array[previousElement + 1] = array[previousElement];
			previousElement -= 1;
		}
		
		array[previousElement + 1] = key;
		
	}

   swap(first, &array[0]);
   swap(second, &array[1]);
   swap(third, &array[2]);

}

void swap(int *x, int *y) {

	int tmp = '\0';
   tmp  = (int)(*x);
   (*x) = (int)(*y);
   (*y) = (int)tmp;

}
