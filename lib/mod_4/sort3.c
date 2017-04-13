#include <stdio.h>
#include <stdlib.h>

void sort(int first, int second, int third);

int main(int argc, char **argv) { 

	int first, second, third; 
	scanf ("%d %d %d", &first, &second, &third);
	sort(first, second, third);

	return EXIT_SUCCESS;

}

void sort(int first, int second, int third) {
	int array[3];
	array[0] = first;
	array[1] = second;
	array[2] = third;

	for (int i = 0; i < 3; i++) {
		int key = array[i];
		int previousElement = i - 1;

		while ((previousElement >= 0) && (array[previousElement] > key)) {
			array[previousElement + 1] = array[previousElement];
			previousElement -= 1;
		}
		
		array[previousElement + 1] = key;
		
	}

	for (int i = 0; i < 3; i++) {
		printf("%d\n", array[i]);
	}
}
