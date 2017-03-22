/*
 *	Lucas & Andrew
 *	03/08/2017
 *	Our simple little program to find if the 
 *	chosen year is a leap year or not.
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0
#define START_GREG_CAL 1582

int isLeapYear(int year); 

int main(int argc, char *argv[]) {

	int user_year;
	
	printf("please enter the year you are interested in\n");
	scanf("%d", &user_year);

	assert(user_year > START_GREG_CAL);
	
	int leapResult = isLeapYear(user_year);
	
	if (leapResult == TRUE) {
		printf("%d is a leap year!\n", user_year);
	} else {
		printf("%d is not a leap year!\n", user_year);
	}
	
	return EXIT_SUCCESS;

}

int isLeapYear(int year) {
	/*
	 *	- Centuries are NOT leap years
	 *	- Every 400 years IS a leap year
	 */
	if (year % 400 == 0) {
		return TRUE;
	} else if (year % 4 == 0 && !( year % 100 == 0)) {
		return TRUE;
	} else {
		return FALSE;
	}
}
