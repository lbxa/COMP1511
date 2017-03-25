  /*
  *  doomsday.c
  *  A program to test a function dayOfWeek which determines which
  *  day of the week a particular date falls on.
  *  (only for dates after the start of the Gregorian calendar).
  *
  *  Program stub created by Richard Buckland on 17/03/14
  *  This program by YOUR-NAME-HERE
  *  Freely licensed under Creative Commons CC-BY-3.0
  *
  *
  */
  
 #include <stdio.h>
 #include <stdlib.h>
 #include <assert.h>
 #include <math.h>
 #include <string.h>
  
#define THURSDAY 0
#define FRIDAY   1
#define SATURDAY 2
#define SUNDAY   3
#define MONDAY   4
#define TUESDAY  5
#define WEDNESDAY 6

#define JANUARY 1
#define FREBRUARY 2
#define MARCH 3
#define APRIL 4
#define MAY 5
#define JUNE 6
#define JULY 7
#define AUGUST 8
#define SEPTEMBER 9
#define OCTOBER 10
#define NOVEMBER 11
#define DECEMBER 12
  
#define TRUE 1
#define FALSE 0
#define DAYS_PER_WEEK 7

int dayOfWeek (int doomsday, int leapYear, int month, int day);

int main (int argc, char *argv[]) {
 
   assert (dayOfWeek (THURSDAY,  FALSE,  4,  4) == THURSDAY);
   assert (dayOfWeek (FRIDAY,    FALSE,  6,  6) == FRIDAY);
   assert (dayOfWeek (MONDAY,    FALSE,  8,  8) == MONDAY);
   assert (dayOfWeek (WEDNESDAY, FALSE, 10, 10) == WEDNESDAY);
   assert (dayOfWeek (FRIDAY,    FALSE, 12, 12) == FRIDAY);
   assert (dayOfWeek (THURSDAY,  FALSE,  9,  5) == THURSDAY);
   assert (dayOfWeek (FRIDAY,    FALSE,  5,  9) == FRIDAY);
   assert (dayOfWeek (SUNDAY,    FALSE,  7, 11) == SUNDAY);
   assert (dayOfWeek (TUESDAY,   FALSE, 11,  7) == TUESDAY);
   assert (dayOfWeek (WEDNESDAY, FALSE,  3,  7) == WEDNESDAY);

   assert (dayOfWeek (THURSDAY,  FALSE,  4,  5) == FRIDAY);
   assert (dayOfWeek (SATURDAY,  FALSE,  6,  5) == FRIDAY);
   assert (dayOfWeek (MONDAY,    FALSE,  8,  9) == TUESDAY);
   assert (dayOfWeek (WEDNESDAY, FALSE, 10,  9) == TUESDAY);
   assert (dayOfWeek (FRIDAY,    FALSE, 12, 20) == SATURDAY);
   assert (dayOfWeek (THURSDAY,  FALSE,  9,  9) == MONDAY);
   assert (dayOfWeek (FRIDAY,    FALSE,  5,  5) == MONDAY);
   assert (dayOfWeek (SUNDAY,    FALSE,  7,  7) == WEDNESDAY);
   assert (dayOfWeek (TUESDAY,   FALSE, 11, 11) == SATURDAY);
   assert (dayOfWeek (THURSDAY,  FALSE,  3, 30) == SATURDAY);

   assert (dayOfWeek (TUESDAY,   FALSE,  2,  28) == TUESDAY);
   assert (dayOfWeek (TUESDAY,   FALSE,  2,  27) == MONDAY);
   assert (dayOfWeek (THURSDAY,  FALSE,  1,  3)  == THURSDAY);
   
   // Please add your own unit tests here with a comment beside, 
   // to indicate that you wrote them For example:
   //Angela Finlayson
   assert (dayOfWeek (WEDNESDAY, FALSE, 8, 31) == FRIDAY); 
   // Stanley Su
   assert (dayOfWeek (TUESDAY, TRUE, 8, 18) == FRIDAY); 
   // Alex Huang
   assert (dayOfWeek (MONDAY, TRUE, 1, 1) == FRIDAY); 
   // Felicia Ee
   assert (dayOfWeek (TUESDAY, TRUE, 2, 28) == MONDAY); 
   //Maksim Lisau
   assert (dayOfWeek (SATURDAY, FALSE, 1, 2) == FRIDAY);
   //Angeni Bai
   assert (dayOfWeek (SATURDAY, FALSE, 3, 15) == SUNDAY); 
   //Marcus Handley
   assert (dayOfWeek (WEDNESDAY, FALSE, 12, 19) == dayOfWeek (WEDNESDAY, TRUE, 12, 19) ); 
   // Alex Tan
   assert (dayOfWeek (FRIDAY, TRUE, 2, 29) == FRIDAY); 
   // Luke Fisk-Lennon
   assert (dayOfWeek (MONDAY, TRUE, 1, 9) == SATURDAY); 
   // Jarrod Li
   assert (dayOfWeek (THURSDAY, TRUE, 2, 29) == THURSDAY); 
   //Mirela Tomicic
   assert (dayOfWeek (FRIDAY, TRUE, 1, 3) == THURSDAY); 
   // Andrew Yu
   assert (dayOfWeek (TUESDAY, FALSE, 3, 16) == THURSDAY); 
   //Samuel Hagan
   assert (dayOfWeek (SUNDAY, FALSE, 7, 11) == SUNDAY); 
   //Tracey Chiu
   assert (dayOfWeek (TUESDAY, FALSE, 4, 6) == THURSDAY); 
   //Andrew Timkov
   assert (dayOfWeek (MONDAY, TRUE, 12, 31) == SATURDAY); 
   //Matthew Darley
   assert (dayOfWeek (TUESDAY, FALSE, 12, 25) == MONDAY); 
   //Nicholas Austen
   assert (dayOfWeek (TUESDAY, FALSE, 12, 5) == TUESDAY); 
   //Christina Shi
   assert (dayOfWeek (FRIDAY, TRUE, 2, 29) == FRIDAY); 
   //Noa Challis 
   assert (dayOfWeek (MONDAY, FALSE, 8, 10) == WEDNESDAY); 
   //Evan Lee
   assert (dayOfWeek (FRIDAY, TRUE, 11, 24) == MONDAY); 
   // Callum Predavec
   assert (dayOfWeek (WEDNESDAY, TRUE, 2, 29) == WEDNESDAY); 
   // Joel Perry
   assert (dayOfWeek (TUESDAY, FALSE, 11, 11) == SATURDAY); 
   // Phoebe Zuo 
   assert (dayOfWeek (SATURDAY, FALSE, 3, 1) == SUNDAY); 
   // Sebastien Higgs
   assert (dayOfWeek (MONDAY, FALSE, 2, 25) == FRIDAY); 
   // Nicholas Patrikeos
   assert (dayOfWeek (TUESDAY, FALSE, 3, 25) == SATURDAY); 
   //Rahul Kumar
   assert (dayOfWeek (MONDAY, TRUE, 2, 2) == TUESDAY); 
   // Lucas Barbosa
   assert (dayOfWeek (MONDAY, FALSE, 12, 4) == MONDAY);

   printf ("all tests passed - You are awesome!\n");

   return EXIT_SUCCESS;
}


// given the doomsday for a year, and whether or not it is a
// leap year, this function return the day of the week for any
// given month and day in the year.

/*
*   Doomsdays:
*   Jan 3
*   Jan 4 [LEAP YEAR]
*   Feb 28 
*   Feb 29 [LEAP YEAR]
*   Apr 4 [4/4]
*   May 9 [9/5]
*   Jun 6 [6/6] 
*   Aug 8 [8/8]
*   Oct 10 [10/10]
*   Nov 11 [7/11]
*   Dec 12 [12/12]
*/

int dayOfWeek (int doomsday, int leapYear, int month, int day) {
int dayOfWeek = 0;

// The following condition statements execute depending on the month. They
// then add the day of the month to the doomsday and subtract the date of
// the first doomsday of the month to get the day in terms of the first day
// of the month. This is then reduced (mod 7) to a number 0 to 6. Which
// will be returned at the end of the function (as the dayOfWeek variable).
// In the case of January and February, an extra condition is required to
// determine the first day of the month based on whether or not it is a
// leap year.
 
   if (month == JANUARY) {                         
                                                   
      if (leapYear == TRUE) {                      
                                                   
         dayOfWeek = (doomsday + day + 3) % DAYS_PER_WEEK;     
                                                               
      } else {                                                 
                                                              
         dayOfWeek = (doomsday + day + 4) % DAYS_PER_WEEK;

      }
      
   } else if (month == FREBRUARY) {

      if (leapYear == TRUE) {

         dayOfWeek = (doomsday + day + 6) % DAYS_PER_WEEK;

      } else {

         dayOfWeek = (doomsday + day) % DAYS_PER_WEEK;
      }
      
   } else if (month == MARCH) {

      dayOfWeek = (doomsday + day) % DAYS_PER_WEEK;

   } else if (month == APRIL) {

      dayOfWeek = (doomsday + day + 3) % DAYS_PER_WEEK;

   } else if (month == MAY) {

      dayOfWeek = (doomsday + day + 5) % DAYS_PER_WEEK;

   } else if (month == JUNE) {

      dayOfWeek = (doomsday + day + 1) % DAYS_PER_WEEK;

   } else if (month == JULY) {

      dayOfWeek = (doomsday + day + 3) % DAYS_PER_WEEK;

   } else if (month == AUGUST) {

      dayOfWeek = (doomsday + day + 6) % DAYS_PER_WEEK;

   } else if (month == SEPTEMBER) {

      dayOfWeek = (doomsday + day + 2) % DAYS_PER_WEEK;

   } else if (month == OCTOBER) {

      dayOfWeek = (doomsday + day + 4) % DAYS_PER_WEEK;

   } else if (month == NOVEMBER) {

      dayOfWeek = (doomsday + day) % DAYS_PER_WEEK;

   } else if (month == DECEMBER) {

      dayOfWeek = (doomsday + day + 2) % DAYS_PER_WEEK;

   }

   return (dayOfWeek);
}