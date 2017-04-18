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
#include <math.h>

#define MAX_STEPS 256
#define MAX_DISTANCE 2
#define ORIGIN 0
#define MAX_PLANE_WIDTH 512

typedef struct _complex_number {
    double real;
    double imaginary;
} ComplexNumber;
 
int escapeSteps(double x, double y);
double euclidean(double x1, double y1, double x2, double y2);
double square(double base);

int main(void) {

  // X:7.600000, Y:62.350000, Steps:1
  int steps = escapeSteps(7.600000, 62.350000);
  printf("%d\n", steps);

  return EXIT_SUCCESS;
}

int escapeSteps(double x, double y) {
    ComplexNumber Z;
    Z.real      = 0;
    Z.imaginary = 0;

    ComplexNumber C;
    C.real      = x;
    C.imaginary = y;

    int i = 0;
    double dist = 0;
    while ((i < MAX_STEPS) && (dist <= MAX_DISTANCE)) {
        double tmpZReal = Z.real;
        Z.real = square(Z.real) - square(Z.imaginary) + C.real;
        Z.imaginary = 2 * (tmpZReal * Z.imaginary) + C.imaginary;
        dist = euclidean(ORIGIN, ORIGIN, Z.real, Z.imaginary);
        i++;
    }
    int numberOfSteps = i;
    return numberOfSteps;
}

double euclidean(double x1, double y1, double x2, double y2) {
    return sqrt(square(y2 - y1) + square(x2 - x1));
}

double square(double base) {
    return base * base;
}