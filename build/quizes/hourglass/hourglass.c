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
    
    int col, row;
    col = row = 0;
    
    // populating the array
    while (col < size) {
        row = 0;
        while (row < size) {
            hourGlass[col][row] = " ";
            row++;
        }
        col++;
    }
    
    int i = 0;
    
    // putting in em arsterixes
    while (i < size) {
        hourGlass[i][i] = "\\";
        hourGlass[i][size - i - INDEX_AT_ZERO] = "/";
        
        hourGlass[firstRow][i] = SYMBOL;
        hourGlass[lastRow][i] = SYMBOL;
        hourGlass[lastRow][firstItem] = SYMBOL;
        i++; 
    }
    
    col = row = 0;
    
    // printing em out boi
    while (col < size) {
        row = 0;
        while (row < size) {
            printf("%s", hourGlass[col][row]);
            row++;
        }
        printf("\n");
        col++;
    }
    
}

     
