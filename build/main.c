// extract.c
// Jordan and Lucas
// funtions and types used to extract x,y,z values from a
// string containing a url of the form
// "http://almondbread.cse.unsw.edu.au:7191/tile_x3.14_y-0.141_z5.bmp"
// initially by richard buckland
// 12 April 2017
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
 
typedef struct _triordinate {
   double x;
   double y;
   int z;
} triordinate;
 
triordinate extract (char *message);

int main (int argc, char *argv[]) {
    
    char * message = "http://almondbread.cse.unsw.edu.au:7191/tile_x3.14_y-0.141_z5.bmp";
 
    triordinate dat = extract(message); //struct we need to use for values
 
    printf ("dat is (%f, %f, %d)\n", dat.x, dat.y, dat.z);
 
    assert (dat.x == 3.14);
    assert (dat.y == -0.141);
    assert (dat.z == 5);
 
    return EXIT_SUCCESS;
}

triordinate extract (char *message) {
    triordinate searchValues;

    sscanf(message, "http://almondbread.cse.unsw.edu.au:7191/tile_x%lf_y%lf_z%d.bmp",
           &searchValues.x, &searchValues.y, &searchValues.z);

    triordinate returnValues;
    returnValues.x = searchValues.x;
    returnValues.y = searchValues.y;
    returnValues.z = searchValues.z;
    return returnValues;
}