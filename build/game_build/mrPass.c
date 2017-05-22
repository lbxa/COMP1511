/*
 *  Mr Pass.  Brain the size of a planet!
 *
 *  Proundly Created by Richard Buckland
 *  Share Freely Creative Commons SA-BY-NC 3.0. 
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"
#include "mechanicalTurk.h"

#define MAX_STUDENT_TYPES 5
#define NO_STUDENTS 0
#define TRUE 1

action decideAction (Game g) {
   
   action nextAction;
   int playerID = getWhoseTurn(g);
   
   /*
    *  GET resources FROM player
    *  IF resources IS EMPTY:
    *    PASS
    *  ELSE:
    *    START_SPINOFF
    */
   
   int amountOfStudents_BPS = getStudents (g, playerID, STUDENT_BPS);
   int amountOfStudents_MTV = getStudents (g, playerID, STUDENT_MTV);
   int amountOfStudents_ThD = getStudents (g, playerID, STUDENT_THD);
   
   if ((amountOfStudents_BPS > NO_STUDENTS) 
    && (amountOfStudents_MTV > NO_STUDENTS) 
    && (amountOfStudents_ThD > NO_STUDENTS)) {
      
      nextAction.actionCode = START_SPINOFF;
      
   } else {
      
      nextAction.actionCode = PASS;
      
   }
      
   return nextAction;

}
