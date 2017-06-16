// quiz A
// predict what will be printed by each line and then run the program to confirm

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define EVEN 0
#define INDEX_AT_ZERO 1
#define SYMBOL "="

void hourGlass(int size);
     
int main (int argc, char *argv[]) {
  
    int size = 0;
    printf("Insert your ODD size: ");
    scanf("%d", &size);

    hourGlass(size); 
    
    printf ("quiz done!\n");
    return EXIT_SUCCESS;
}

void hourGlass(int size) {
    assert(size % 2 != EVEN);
    
    char *hourGlass[size][size];
    int firstRow, firstItem;
    firstRow = firstItem = 0;
    int lastRow = size - 1;
    
    // populating the arrat
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            hourGlass[j][i] = " ";
        }
    }
    
    // putting in em arsterixes
    for (int i = 0; i < size; i++) {
        hourGlass[i][i] = "\\";
        hourGlass[i][size - i - INDEX_AT_ZERO] = "/";
        
        hourGlass[firstRow][i] = SYMBOL;
        hourGlass[lastRow][i] = SYMBOL;
        hourGlass[lastRow][firstItem] = SYMBOL;
        
    }
    
    // printing em out boi
    for (int j = 0; j < size; j++) {
        for (int i = 0; i < size; i++) {
            printf("%s", hourGlass[j][i]);
        }
        printf("\n");
    }
    
}

     
