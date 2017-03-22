/*
 * Test if a point is inside a triangle.
 * Julian Saknussemm
 *
 * Given Three points of a triangle, and another arbitrary point 
 * this program determines if that point lies inside
 * the triangle.
 *
 * This is determined by satisfying the following rule:
 * A point P(x,y) is inside triangle A(x0,y0), B(x1,y1), C(x2,y2)
 * iff
 * P is on the same side of the line AB as C
 * P is on the same side of the line BC as A
 * and
 * P is on the same side of the line AC as B
 *
 * A special case exits for a vertical line (inf gradient) when testing 
 * the side of the line
 */
 
#include <stdio.h>
#include <stdlib.h>

#define UNDER_LINE -1 
#define ON_LINE 0 
#define ABOVE_LINE 1  

int testSide( double xTestCoord, double yTestCoord, 
                  double gradient, double yIntercept  );

int isOnSameSide( double xTestCoord, double yTestCoord, double gradient,
                  double yIntercept, double xCoord, double yCoord);
               
int isInTriangle(double aX,double aY,double bX,double bY,double cX,
                 double cY, double xTestCoord, double yTestCoord);
                 
int main(int argc, char* argv[]) {
   double aX;
   double aY;
   double bX;
   double bY;
   double cX;
   double cY;
   double xTestCoord;
   double yTestCoord;
 
   int scanfTotal = 0;
 
   // get input
   printf("Triangle Vertex A (x,y): "); 
   scanfTotal += scanf("%lf,%lf", &aX,&aY);
   printf("Triangle Vertex  B (x,y): "); 
   scanfTotal += scanf("%lf,%lf", &bX,&bY);
   printf("Triangle Vertex  C (x,y): "); 
   scanfTotal += scanf("%lf,%lf", &cX,&cY);
   printf("Test Point (x,y): "); 
   scanfTotal += scanf("%lf,%lf", &xTestCoord,&yTestCoord);
 
   // print error
   if( scanfTotal != 8 ) {
      printf("You're stupid and didn't put in the right inputs!\n");
      return EXIT_FAILURE;
   }
 
   // print answer
   printf("Point (%.2lf,%.2lf) is ", xTestCoord,yTestCoord);
   
   if(isInTriangle(aX,aY,bX,bY,cX,cY,xTestCoord,yTestCoord)) {
      printf("inside");
   } else { 
      printf("outside");
   }
   
   printf(" the Triangle\n");
 
   
   return EXIT_SUCCESS;
}

int testSide( double xTestCoord, double yTestCoord, 
                  double gradient, double yIntercept  ) {   
   int returnValue;       
   if( yTestCoord < gradient * xTestCoord + yIntercept  ) {
      returnValue = UNDER_LINE; // point is under line
   } else if ( yTestCoord == gradient * xTestCoord + yIntercept  ){
      returnValue = ON_LINE; // On the line 
   } else {
      returnValue = ABOVE_LINE; // point is over line 
   }
   return returnValue;
}
 
int isOnSameSide( double xTestCoord, double yTestCoord, double gradient,
                  double yIntercept, double xCoord, double yCoord) {
   // Check if same side
   return (testSide( xTestCoord,yTestCoord, gradient, yIntercept )
   == testSide(xCoord, yCoord, gradient, yIntercept)); 
}

int isInTriangle(double aX,double aY,double bX,double bY,double cX,
                 double cY, double xTestCoord, double yTestCoord){
 
   int line1, line2, line3;
   
   // Calculate Lines
   double gradientAB = (bY-aY)/(bX-aX);
   double yInterceptAB = gradientAB * -bX + bY;
   double gradientAC = (cY-aY)/(cX-aX);
   double gradientBC = (cY-bY)/(cX-bX);
   double yInterceptAC = gradientAC * -cX + cY;
   double yInterceptBC = gradientBC * -cX + cY;
 
   // vertical line checks, avoid divide by zero error 
   if( bX == aX ) {
      line1 = ( (xTestCoord <= aX) == (cX <= aX) );
   } else {
      line1 = isOnSameSide( xTestCoord, yTestCoord, 
                            gradientAB, yInterceptAB,cX,cY);
   }
 
   if( bX == cX ) {
      line2 = ( (xTestCoord <= cX) == (aX <= cX) );
   } else {
      line2 = isOnSameSide(xTestCoord,yTestCoord, 
                           gradientBC, yInterceptBC,aX,aY);
   }
 
   if( cX == aX ) {
      line3 = ( (xTestCoord <= aX ) == (bX <= aX) );
   } else {
      line3 = isOnSameSide(xTestCoord, yTestCoord, 
                           gradientAC,yInterceptAC,bX,bY);
   }
   
   // Are all of them on the same side of the line? 
   return line1 && line2 && line3;
 
}
