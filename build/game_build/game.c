#include "game.h"
#include "mechanicalTurk.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

typedef struct _game * Game;

typedef struct _game { 
   int currentTurn;
 } game;

/* **** Functions which change the game aka SETTERS **** */
// make a new game, given the disciplines produced by each
// region, and the value on the dice discs in each region.
// note: each array must be NUM_REGIONS long
// eg if you are using my sample game struct above this function
// would need to set the field currentTurn to -1.  (because the turn
// number is -1 at the start of the game)
// the ordering of the regions is column by column left to right,
// going from the top of each column to the bottom before moving 
// to the next column to the right.
//
// so to create the default game as shown on the badly drawn map:
//

#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \
STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, \
STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}


//   Game g = newGame (disciplines, dice);
Game newGame(int discipline[], int dice[]) {
    Game game = malloc(sizeof(game));
    return game;
}

// free all the memory malloced for the game
void disposeGame(Game g) {
    free(g);
}

// make the specified action for the current player and update the 
// game state accordingly.  
// The function may assume that the action requested is legal.
// START_SPINOFF is not a legal action here
void makeAction(Game g, action a) {
    printf("Placeholder");
}

// advance the game to the next turn, 
// assuming that the dice has just been rolled and produced diceScore
// the game starts in turn -1 (we call this state "Terra Nullis") and 
// moves to turn 0 as soon as the first dice is thrown. 
void throwDice(Game g, int diceScore) {
    printf("Placeholder");
}

/* **** Functions which GET data about the game aka GETTERS **** */

// what type of students are produced by the specified region?
// regionID is the index of the region in the newGame arrays (above) 
// see discipline codes above
int getDiscipline(Game g, int regionID) {
    int discipline = STUDENT_THD;
    return discipline;
}

// what dice value produces students in the specified region?
// 2..12
int getDiceValue(Game g, int regionID) {
    int diceValue = 0;
    if (regionID == 2) {
        diceValue = 2;
    }
    return diceValue;
}

// which university currently has the prestige award for the most ARCs?
// this is NO_ONE until the first arc is purchased after the game 
// has started.  
int getMostARCs(Game g) {
    int mostARCs = NO_ONE;
    return mostARCs;
}

// which university currently has the prestige award for the most pubs?
// this is NO_ONE until the first publication is made.
int getMostPublications(Game g) {
    int mostPublications = NO_ONE;
    if (g) {
        mostPublications = 1;
    }
    return mostPublications;
}

// return the current turn number of the game -1,0,1, ..
int getTurnNumber(Game g) {
    int turnNumber = 0;
    return turnNumber;
}

// return the player id of the player whose turn it is 
// the result of this function is NO_ONE during Terra Nullis
int getWhoseTurn(Game g) {
    int whoseTurn = NO_ONE;
    return whoseTurn;
}

// return the contents of the given vertex (ie campus code or 
// VACANT_VERTEX)
int getCampus(Game g, path pathToVertex) {
    int vertexContents = VACANT_VERTEX;
    return vertexContents;
}

// the contents of the given edge (ie ARC code or vacent ARC)
int getARC(Game g, path pathToEdge) {
    int edgeContents = VACANT_ARC;
    return edgeContents;
}

// returns TRUE if it is legal for the current
// player to make the specified action, FALSE otherwise.
//
// "legal" means everything is legal: 
//   * that the action code is a valid action code which is legal to 
//     be made at this time
//   * that any path is well formed and legal ie consisting only of 
//     the legal direction characters and of a legal length, 
//     and which does not leave the island into the sea at any stage.
//   * that disciplines mentioned in any retraining actions are valid 
//     discipline numbers, and that the university has sufficient
//     students of the correct type to perform the retraining
//
// eg when placing a campus consider such things as: 
//   * is the path a well formed legal path 
//   * does it lead to a vacent vertex?
//   * under the rules of the game are they allowed to place a 
//     campus at that vertex?  (eg is it adjacent to one of their ARCs?)
//   * does the player have the 4 specific students required to pay for 
//     that campus?
// It is not legal to make any action during Terra Nullis ie 
// before the game has started.
// It is not legal for a player to make the moves OBTAIN_PUBLICATION 
// or OBTAIN_IP_PATENT (they can make the move START_SPINOFF)
// you can assume that any pths passed in are NULL terminated strings.
int isLegalAction(Game g, action a) {
    int legality = FALSE;
    return legality;
}

// --- get data about a specified player ---

// return the number of KPI points the specified player currently has
int getKPIpoints(Game g, int player) {
    int KPIpoints = 0;
    return KPIpoints;
}

// return the number of ARC grants the specified player currently has
int getARCs(Game g, int player) {
    int ARCs = 0;
    return ARCs;
}

// return the number of GO8 campuses the specified player currently has
int getGO8s(Game g, int player) {
    int GO8s = 0;
    return GO8s;
}

// return the number of normal Campuses the specified player currently has
int getCampuses(Game g, int player) {
    int campii = 0;
    return campii;
}

// return the number of IP Patents the specified player currently has
int getIPs(Game g, int player) {
    int IPs = 0;
    return IPs;
}

// return the number of Publications the specified player currently has
int getPublications(Game g, int player) {
    int publications = 0;
    return publications;
}

// return the number of students of the specified discipline type 
// the specified player currently has
int getStudents(Game g, int player, int discipline) {
    int students = 0;
    return students;
}

// return how many students of discipline type disciplineFrom
// the specified player would need to retrain in order to get one 
// student of discipline type disciplineTo.  This will depend 
// on what retraining centers, if any, they have a campus at.
int getExchangeRate(Game g, int player,
    int disciplineFrom, int disciplineTo) {
    int exchangesNeeded = 0;
    if (disciplineFrom == 2) {
        exchangesNeeded = 2;
    }
    return exchangesNeeded;
}

int main() {
    printf("This compiles!");
    return EXIT_SUCCESS;
}