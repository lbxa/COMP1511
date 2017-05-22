/*
 *  MechanicalTurk ~ AKA Clark Kent
 *
 *  Simple game bot, programmed to play Knowledge Island in a competitive 
 *  environment against other bots. 
 *  NOTE: This is not to be mistaken for an AI, as by definition this source
 *        code does not include any trainning data (no where to be stored) nor
 *        does it include any neural networks with reinforcement learning 
 *        techniques. This is just a simple program made to play a game with 
 *        hardcoded strategies. This is due to the lack of accesibility to 
 *        imported data sets, maybe one day this can really be an AI.
 *  
 *  01.05.2017 | Lucas & Sebastian | The Project
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Game.h"
#include "mechanicalTurk.h"

#define MAX_STUDENT_TYPES 5
#define NO_STUDENTS 0
#define TRUE 1
#define FALSE 0

action decideAction (Game liveGame) {
   
   action nextAction;
   int playerID = getWhoseTurn(liveGame);
   
   /*
    *  GET resources FROM player
    *  IF resources IS EMPTY:
    *    pass
    *  ELSE:
    *    start business spinoff
    */
   
   int amountOfStudents_BPS = getStudents (liveGame, playerID, STUDENT_BPS);
   int amountOfStudents_MTV = getStudents (liveGame, playerID, STUDENT_MTV);
   int amountOfStudents_ThD = getStudents (liveGame, playerID, STUDENT_THD);
   
   if ((amountOfStudents_BPS > NO_STUDENTS) 
    && (amountOfStudents_MTV > NO_STUDENTS) 
    && (amountOfStudents_ThD > NO_STUDENTS)) {
      
      nextAction.actionCode = START_SPINOFF;
      
   } else {
      
      nextAction.actionCode = PASS;
      
   }
      
   return nextAction;

}

 
