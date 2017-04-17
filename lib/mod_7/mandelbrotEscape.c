/* 
 * Jordan and Lucas
 * 5/04/2017
 * this program finds the amount of steps it takes to
 * escape the mandelbrot set with a given set of coords
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define MAX_STEPS 256
#define MAX_DISTANCE 2
#define ORIGIN 0

typedef struct _complex_number {
    double real;
    double imaginary;
} ComplexNumber;

double square    (double base);
double euclidean (double x1, double y1, double x2, double y2);
int escapeSteps  (double x, double y);

int main(void) {

    int stepsRes = escapeSteps(-1, -1);
    printf("%d\n", stepsRes);

    return EXIT_SUCCESS;
}

int escapeSteps(double x, double y) {
    
    /*
     *  ƒ[c](z) = (z)^2 + c
     *  c = a + bi
     *  dist = z
     *  IF dist <= MAX_DISTANCE && steps <= 256:
     *      (a + bi)^2 = a^2 + 2abi - b^2
     *      in which ƒ[c](z) = a^2 - b^2 + 2abi + a + bi
     *      sub in x & y
     *      ƒ[c](z) = x^2 - y^2 + 2xyi + x + yi
     *  ENDIF
     */

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
        // Real: x^2 - y^2 + x
        Z.real = square(Z.real) - square(Z.imaginary) + C.real;
        // Imaginary: 2xy + y
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
