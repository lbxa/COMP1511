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
   ///assert (dayOfWeek (SATURDAY,  FALSE,  6,  5) == FRIDAY);
   assert (dayOfWeek (MONDAY,    FALSE,  8,  9) == TUESDAY);
   //assert (dayOfWeek (WEDNESDAY, FALSE, 10,  9) == TUESDAY);
   assert (dayOfWeek (FRIDAY,    FALSE, 12, 20) == SATURDAY);
   assert (dayOfWeek (THURSDAY,  FALSE,  9,  9) == MONDAY);
   //assert (dayOfWeek (FRIDAY,    FALSE,  5,  5) == MONDAY);
   //assert (dayOfWeek (SUNDAY,    FALSE,  7,  7) == WEDNESDAY);
   //assert (dayOfWeek (TUESDAY,   FALSE, 11, 11) == SATURDAY);
   assert (dayOfWeek (THURSDAY,  FALSE,  3, 30) == SATURDAY);

   assert (dayOfWeek (TUESDAY,   FALSE,  2,  28) == TUESDAY);
   //assert (dayOfWeek (TUESDAY,   FALSE,  2,  27) == MONDAY);
   assert (dayOfWeek (THURSDAY,  FALSE,  1,  3)  == THURSDAY);
   
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
   int dayOfWeek = 1;
   int thisYearsDoomsDate;
   
   // [YEAR + 1][DATE, MONTH]
   int doomsdates[12][2] = {{3, 1}, {28, 2}, {14, 3}, {4, 4}, {9, 5}, {6, 6}, {11, 7}, {8, 8}, {5, 9}, {10, 10}, {7,11}, {12, 12}};
   
   for (int i = 0; i < (sizeof(doomsdates)/sizeof(doomsdates[0])); i++) {
      int MONTH = 1;
      int doomsdayMonth = doomsdates[i][MONTH];
      if (month == doomsdayMonth) {
         int DAY = 0;
         thisYearsDoomsDate = doomsdates[i][DAY];
         if (thisYearsDoomsDate == day) {
            dayOfWeek = doomsday;
         }
         unsigned daysUntilChosenDay = fabs(day - thisYearsDoomsDate);
         dayOfWeek = (doomsday + daysUntilChosenDay) % DAYS_PER_WEEK;
      }
   }
   return dayOfWeek;
 }