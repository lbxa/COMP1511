/*
 *  doomsday.v2.c | Doomsday Mark 2 
 *  A program to test a function dayOfWeek which determines which
 *  day of the week a particular date falls on.
 *  (only for dates after the start of the Gregorian calendar).
 *
 *  Program stub created by Richard Buckland on 17/03/14
 *  This program by YOUR-NAME-HERE
 *  Freely licensed under Creative Commons CC-BY-3.0
 *
 *  IMPROVEMENTS in Mark II:
 *
 *  - <getAnchor()> does not really on lines of if/else logic blocks.
 *  - <dayOfWeek>   also does not really on likes of if/else logic blocks. 
 *  - Reduced amount of lines through better algorithms.
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
#define FEBRUARY 2
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

#define JAN_DOOM 3
#define FEB_DOOM 28
#define MAR_DOOM 7
#define APR_DOOM 4
#define MAY_DOOM 9
#define JUN_DOOM 6
#define JUL_DOOM 11
#define AUG_DOOM 8
#define SEP_DOOM 5
#define OCT_DOOM 10 
#define NOV_DOOM 7
#define DEC_DOOM 12

#define TRUE 1
#define FALSE 0
#define DAYS_IN_WEEK 7
#define LEAP_YEAR_EXTRA 1
#define MULT_OF_7 35

int dayOfWeek (int doomsday, int leapYear, int month, int day);
int getAnchor (int leapYear, int month);
int absVal    (int negNum);
void runTests (void);

int main (int argc, char *argv[]) {
 
   runTests();

   return EXIT_SUCCESS;
}


/*  
 *  Given the doomsday for a year, and whether or not it is a
 *  leap year, this function will return the day of the week for any
 *  given month and day in the year.
 */ 

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
   
   int dayOfWeek               = 0;
   int anchorDay               = 0;
   int dayDifferenceToDoomsday = 0;
   int daysPassedFromDoomsday  = 0;

   anchorDay = getAnchor(leapYear, month);
   dayDifferenceToDoomsday = day - anchorDay;

   // Make sure to pass in absolute value of |dayDifferenceToDoomsday|
   daysPassedFromDoomsday = absVal(dayDifferenceToDoomsday);

   daysPassedFromDoomsday = (dayDifferenceToDoomsday + MULT_OF_7);
   daysPassedFromDoomsday %= DAYS_IN_WEEK;

   // modulo from weekly value to find exact date
   dayOfWeek = (doomsday + daysPassedFromDoomsday) % DAYS_IN_WEEK;
   
   return dayOfWeek;
}

int getAnchor (int leapYear, int month) {
   int anchorDay = 0;
   // [MONTH][DOOMSDATE, MONTH]
   int MONTHS = 12;
   int doomsdayCalendar[12][2] = {{JAN_DOOM, JANUARY}, 
                                  {FEB_DOOM, FEBRUARY}, 
                                  {MAR_DOOM, MARCH}, 
                                  {APR_DOOM, APRIL}, 
                                  {MAY_DOOM, MAY}, 
                                  {JUN_DOOM, JUNE}, 
                                  {JUL_DOOM, JULY}, 
                                  {AUG_DOOM, AUGUST}, 
                                  {SEP_DOOM, SEPTEMBER}, 
                                  {OCT_DOOM, OCTOBER}, 
                                  {NOV_DOOM, NOVEMBER}, 
                                  {DEC_DOOM, DECEMBER}};
   int i = 0;
   while ( i < MONTHS ) {
      int CURR_MONTH = 1;
      int CURR_DAY   = 0;
      if ( month == doomsdayCalendar[i][CURR_MONTH] ) {
         
         anchorDay = doomsdayCalendar[i][CURR_DAY];

         if ( leapYear == TRUE && 
            ( month == JANUARY || month == FEBRUARY ) ) {
            anchorDay += LEAP_YEAR_EXTRA;
         }
      }
      i++;
   }
   return anchorDay;
}

int absVal ( int negNum ) {
   int posVal = 0;
   if ( negNum >= 0 ) {
      posVal = negNum;
   } else {
      posVal = -negNum;
   }
   return posVal;
}

void runTests(void) {

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
   assert (dayOfWeek (WEDNESDAY, FALSE, 12, 19) == WEDNESDAY ); 
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
   assert (dayOfWeek (MONDAY, FALSE, 12, 4) == SUNDAY);
   printf ("all tests passed - You are awesome!\n");

}