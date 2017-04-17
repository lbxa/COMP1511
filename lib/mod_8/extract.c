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
#include "extract.h"
 
typedef struct _triordinate {
   double x;
   double y;
   int z;
} triordinate;
 
triordinate extract (char *message);

double myAtoD (char *message);
 
long myAtoL (char *message); 

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
    double datax, datay;
    int dataz;
    sscanf(message, "http://almondbread.cse.unsw.edu.au:7191/tile_x%lf_y%lf_z%d.bmp", &datax,&datay,&dataz);

    triordinate returnValues;
    returnValues.x = datax;
    returnValues.y = datay;
    returnValues.z = dataz;
    return returnValues;
}

///////////////////////////////////////

double myAtoD (char *message) {
    double value;
    sscanf(message,"%lf",&value);
    return value;
}
 
long myAtoL (char *message) {
    long value;
    sscanf(message,"%ld",&value);
    return value;
}
