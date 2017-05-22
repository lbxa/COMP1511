#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Game.h"

#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \
STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, \
STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}

#define LEFT 'L'
#define RIGHT 'R'
#define PATH_END '\0'
#define TERRA_NULLIS -1

#define PASS 0
#define BUILD_CAMPUS 1
#define BUILD_GO8 2
#define OBTAIN_ARC 3
#define START_SPINOFF 4
#define OBTAIN_PUBLICATION 5
#define OBTAIN_IP_lPATENT 6
#define RETRAIN_STUDENTS 7

#define DICE_MAX 12
#define INIT_DICE_VAL 2
#define START_KPI_POINTS 20
#define START_CAMPUSES 2

#define START_STUDENTS_BPS 3
#define START_STUDENTS_BQN 3
#define START_STUDENTS_MTV 1
#define START_STUDENTS_MJ 1
#define START_STUDENTS_MMONEY 1
#define START_STUDENTS_THD 0

void testTurnNumber          (void);  // Alex T

void testInitialCampoxen     (void);  // AlexH
void testPlayerTurning       (void);  // lexHA
void testArcBuilding         (void);  // exHAl
void testStudentAmounts      (void);  // xHAle
void testArcGetting          (void);  // HAlex

//void testBuildSiteIsEmpty    (void);  // Lucas
//void testAdjacentVertex      (void);  // ucasL
void testAllDiceValues       (void);  // casLu
void testAllDisciplineValues (void);  // asLuc
//void testGetKPIpoints        (void);
void testRetraining          (void);  //no work?
/*
 *  Alex Tan, we are testing that the retraining goes accordingly,
 *  so when players do want to retrain we know for a fact that they have
 *  2 of the same student type. It's a test, all functions need to be tested.
 */

void testGameSimulation(void);  // Lucas & Sebastien 

//Add function to

//void copyPath(path from, path to);    //xlea g

/*void copyPath(path from, path to) {
    int i = 0;
    while(from[i] != PATH_END) {
        to[i] = from[i]; 
        i++;    
    }
    to[i] = PATH_END;
}*/

int main(int argc, char *argv[]) {
    
    printf("Testing the game\n");


    /* 
     * ------------------------------- 
     * Tests to be tested on their own
     * -------------------------------
     */
    
    testInitialCampoxen(); //success
    testPlayerTurning();  // success
    testArcBuilding();  // pass with bugs????
    testStudentAmounts();  // pass
    testArcGetting(); // pass with bugs???
    //... Xlea G

    //testRetraining(); //no work??

    //Alex T ...
    
    testTurnNumber(); //success
    
    //... Alex T
    
    //Sebastien ...
//    testNoStudents();
    //..Sebastien
    
    //... Lucas
    //testBuildSiteIsEmpty(); //success BUT it should fail because no ARC
   // testAdjacentVertex(); //FAIL
    testAllDiceValues(); //SUCCESS

    testAllDisciplineValues(); //SUCCESS
    //testGetKPIpoints(); // NOT IMPLEMENTED
    
    testRetraining();
    
    printf("All tests passed. You are awesome!\n");
    
    return EXIT_SUCCESS;
}

// Alex Tan

void testTurnNumber(void) {
    printf("\n\n1\n\n");
    printf("Testing turn number...\n");
    
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    
    Game game = newGame(disciplines, dice);
    
    // testing that the game starts off with a turn number of -1 (TERRA_NULLIS)
    // each time the dice is thrown, the turn number increments
    assert(getTurnNumber(game) == TERRA_NULLIS);
    throwDice(game, 9);
    assert(getTurnNumber(game) == 0);
    throwDice(game, 2);
    assert(getTurnNumber(game) == 1);
    throwDice(game, 11);
    assert(getTurnNumber(game) == 2);

    
    // testing that doing non-dice-rolling activities do not increment the
    // turn number
    
    // pretty much testing every function (except throwDice and disposeGame)
    // to make sure the turnNumber doesn't increase
    
    //this takes an action struct
    action newAction = { PASS };
    makeAction(game, newAction);

    assert(getTurnNumber(game) == 3);

    getDiscipline(game, 0);
    assert(getTurnNumber(game) == 3);
    getDiscipline(game, 10);
    assert(getTurnNumber(game) == 3);
    getDiceValue(game, 1);
    assert(getTurnNumber(game) == 3);
    getMostARCs(game);
    assert(getTurnNumber(game) == 3);
    getMostPublications(game);
    assert(getTurnNumber(game) == 3);
    getWhoseTurn(game);        
    assert(getTurnNumber(game) == 3);
    //to do
    
    disposeGame(game);
    
    printf("Passed!\n");
}


//xlea guanh

void testInitialCampoxen(void) {
    printf("\n\n2\n\n");
    printf("Testing initial campuses...\n");
    
    //tests that all initial campusen are where they should be
    //additionally tests that paths work as intended
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;

    Game g = newGame(disciplines, dice);
    
    path nullPath = { PATH_END };
    assert(getCampus(g, nullPath) == CAMPUS_A); //top campus A
    printf("Top success\n");
    
    path pathToBottom = { RIGHT, LEFT, RIGHT, LEFT, RIGHT, LEFT,
        RIGHT, LEFT, RIGHT, LEFT, LEFT, PATH_END };
    assert(getCampus(g, pathToBottom) == CAMPUS_A); //bottom campus A
    printf("Bottom success\n");
    
    path pathToTopLeft = { RIGHT, RIGHT, LEFT, RIGHT, LEFT, PATH_END };
    assert(getCampus(g, pathToTopLeft) == CAMPUS_B); //top campus B
    printf("Top-left success\n");
    
    path pathToBottomRight = { LEFT, RIGHT, LEFT, RIGHT, LEFT, RIGHT,
        RIGHT, LEFT, RIGHT, LEFT, PATH_END };
    assert(getCampus(g, pathToBottomRight) == CAMPUS_B); //bottom campus B
    printf("Bototm-right success\n");
    
    path pathToTopRight = { LEFT, RIGHT, LEFT, RIGHT, LEFT, PATH_END };
    assert(getCampus(g, pathToTopRight) == CAMPUS_C); //top campus C
    printf("Top-right success\n");
    
    path pathToBottomLeft = { RIGHT, RIGHT, LEFT, RIGHT, LEFT, LEFT,
        RIGHT, LEFT, RIGHT, LEFT, PATH_END };
    assert(getCampus(g, pathToBottomLeft) == CAMPUS_C); //bottom campus C
    printf("Bottom-left success\n");

    printf("All initial campii are in proper place and paths work fine!\n");
    
    disposeGame(g);
    
    printf("Passed!\n");
}

void testPlayerTurning(void) {
    printf("\n\n3\n\n");
    printf("Testing player turning...\n");
    
    // incrementation of player turns should be from A to B to C
    // PASS should be theo nly actioon that switches turns
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;

    Game g = newGame(disciplines, dice);
    
    throwDice(g, 10); //not TERRA_NULLIS please
    
    action nextPlayerPlease = {PASS};
    
    int i = UNI_A;
    while(i <= UNI_C) {
        printf("i=%d gCT(g)=%d\n", i, getWhoseTurn(g));
        
        assert( getWhoseTurn(g) == i );
        makeAction( g, nextPlayerPlease );
        // whoever made this (Alex Huang?), you need to actually 
        // ROLL THE DICE to 
        // increment the turn number
        // MAKE ACTION DOES NOT INCREMENT THE TURN NUMBER
        // ~ Alex Tan
        
        // 
        //
        throwDice(g, 10);
        //
        // 
        
        i++;
    }
    
    i = UNI_A;

    // it SHOULD increment the round as well, once all 3 players have
    // taken their turn
    
    while(i <= UNI_C) {
        printf("i=%d gCT(g)=%d\n", i, getWhoseTurn(g));
        assert( getWhoseTurn(g) == i );
        //same thing here ~ alex tan
        makeAction( g, nextPlayerPlease );
     throwDice(g, 10);
        i++;
    }
    
    disposeGame(g);
    
    printf("Passed!\n");


}

void testArcBuilding(void) {
    printf("\n\n4\n\n");
    printf("Testing ARC building...\n");
    
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;

    Game g = newGame(disciplines, dice);
    
    throwDice(g, 10);

    //make the game initialize first because we can't do shit in terra
    //nullis unlike british invaders!!!! har harh har
    
    //player 1 will build an ARC with a null path, and fail

    action buildARC;
    buildARC.actionCode = OBTAIN_ARC;
    buildARC.destination[0] = PATH_END;// oh this is how u should do it.. yeah

    //plyr 1 will then build an ARC with no adjacent arc/campus = fail
    
    path wrongPath = { LEFT, RIGHT, RIGHT, PATH_END };
    //copyPath(buildARC.destination, wrightPath);
    buildARC.destination[0] = wrongPath[0];
    buildARC.destination[1] = wrongPath[1];
    buildARC.destination[2] = wrongPath[2];

    //going to refactor into a function to copy paths
    
    assert(isLegalAction(g, buildARC) == FALSE);

    //player 1 will build an ARC next to their top campode
    
    path wrightPath = { LEFT, PATH_END };
    //copyPath(buildARC.destination, wrightPath);
    buildARC.destination[0] = wrightPath[0];
    buildARC.destination[1] = wrightPath[1];

    assert(isLegalAction(g, buildARC) == TRUE);

    //player 2 will try to build an ARC next to plyr1's campus but fail
    action nextPlayerPlease = {PASS};
    makeAction( g, nextPlayerPlease );

    assert(isLegalAction(g, buildARC) == FALSE);

    disposeGame(g);
    
    printf("Passed!\n");
}

void testArcGetting(void) {
    printf("\n\n5\n\n");
    printf("Testing ARC getting...\n");
    
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;

    Game g = newGame(disciplines, dice);
    
    throwDice(g, 10);
    //make the game initialize first because we can't do shit in terra
    //nullis unlike british invaders!!!! har harh har
    
    
    action buildARC;
    buildARC.actionCode = OBTAIN_ARC;

    path wrightPath = { LEFT, PATH_END };
    //copyPath(buildARC.destination, wrightPath);
    buildARC.destination[0] = wrightPath[0];
    buildARC.destination[1] = wrightPath[1];
    
    assert(isLegalAction(g, buildARC) == TRUE);

    //now actually build the ARC
    makeAction( g, buildARC );
    assert( getARC(g, wrightPath) == ARC_A );
    

    disposeGame(g);
    
    printf("Passed!\n");
}
/*           Tried to fix but this probs belongs in testGameSimulation
void testGetKPIpoints (void) {
    
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[]        = DEFAULT_DICE;
    
    Game g = newGame(disciplines, dice);
    
    action KPIConsumingAction;
    
    int playerX = getWhoseTurn(g);  // player 1 
    KPIConsumingAction.actionCode = OBTAIN_IP_PATENT;
    makeAction(g, KPIConsumingAction);
    assert(getKPIpoints(g, playerX) >= );
    
    assert(getKPIpoints (Game g, 1) == 20);
    assert(getKPIpoints (Game g, 2) == 30);
    assert(getKPIpoints (Game g, 3) == 50);
    
    disposeGame(g);
    
}
*/  

void testStudentAmounts(void) {
    printf("\n\n6\n\n");
    int currentPlayer = 3;
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[]        = DEFAULT_DICE;
    
    Game g = newGame(disciplines, dice);
    printf("Testing that student counts are correct\n");
    while (currentPlayer > 0) {
        assert(getStudents(g, currentPlayer, STUDENT_THD) == 0);
        assert(getStudents(g, currentPlayer, STUDENT_BPS) == 3);
        assert(getStudents(g, currentPlayer, STUDENT_BQN) == 3);
        assert(getStudents(g, currentPlayer, STUDENT_MJ) == 1);
        assert(getStudents(g, currentPlayer, STUDENT_MTV) == 1);
        assert(getStudents(g, currentPlayer, STUDENT_MMONEY) == 1);
        currentPlayer--;        
    }
    disposeGame(g);
    printf("Student counts correct\n");
}
/*
void testBuildSiteIsEmpty(void) {
    
    printf("Testing campuses are only built on free land...\n");
    
    //
     /  Make sure that campii are built only on free land, this test 
     /  should go tandem with the testAdjacentVertex() test
     //
    
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[]        = DEFAULT_DICE;
    
    Game g = newGame(disciplines, dice);
    
    //int player = getWhoseTurn(g);
    
    //Testing A Basic Path is empty
    
    path newPath = { LEFT, RIGHT, PATH_END };
    action newAction;
    newAction.actionCode = BUILD_CAMPUS;
    newAction.destination[0] = LEFT;
    newAction.destination[1] = RIGHT;
    newAction.destination[2] = END;
    
    makeAction(g, newAction);
   // assert(getCampus(g,newPath) == getWhoseTurn(g));
    
}

void testAdjacentVertex(void) {
    
    printf("Testing campuses are campuses can only be built in valid locations...\n");
    
    //
     //  Make sure that campii are built only on vertexes which are not 
     ..  adjacent to already existing campii, this test should go in  
     ..  tandem with testBuildSiteIsEmpty
     //
     
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[]        = DEFAULT_DICE;
    
    Game g = newGame(disciplines, dice);
    
    action newAction = {BUILD_CAMPUS};
    makeAction(g, newAction);
    assert( isLegalAction(g, newAction) == TRUE );
    
    printf("Passed!\n");
    
}
*/
void testAllDiceValues(void){
    printf("\n\n7\n\n");
    printf("Testing dice values are corresponding to the region values...\n");

    /*
     *  Make sure that the dice values are corresponding to the region 
     *  values.
     */
     
    int disciplines[NUM_REGIONS] = {STUDENT_THD, STUDENT_BPS, 
                                    STUDENT_BQN, STUDENT_MJ, 
                                    STUDENT_MJ, STUDENT_MJ,
                                    STUDENT_MTV, STUDENT_MTV, 
                                    STUDENT_MTV, STUDENT_MMONEY, 
                                    STUDENT_BPS, STUDENT_BQN,
                                    STUDENT_MJ, STUDENT_MJ, STUDENT_MJ,
                                    STUDENT_THD, STUDENT_BPS, 
                                    STUDENT_BQN, STUDENT_THD};

    int dice[NUM_REGIONS] = {0, 1, 2, 3, 3, 3, 4, 4, 4, 5, 1, 2, 3, 3, 
                            3, 0, 1, 2, 0};
                             
    Game g = newGame(disciplines, dice);
    
    int regionID = 0;
    while (regionID < NUM_REGIONS) {
        int regionDiceValue = dice[regionID];
        assert(getDiceValue(g, regionID) == regionDiceValue);
        regionID++;
    }
    
    
    disposeGame(g);
    printf("Passed!\n");
    
}

void testAllDisciplineValues(void) {
    printf("\n\n8\n\n");
    printf("Testing discipline values...\n");
    
        
    /*
     *  Make sure that the discipline values are corresponding to the
     *  region values. This is done on game start up
     */
     
    int disciplines[NUM_REGIONS] = {STUDENT_THD, STUDENT_BPS, STUDENT_BQN,
                                    STUDENT_MJ, STUDENT_MJ, STUDENT_MJ,
                                    STUDENT_MTV, STUDENT_MTV, STUDENT_MTV,
                                    STUDENT_MMONEY, STUDENT_BPS, STUDENT_BQN,
                                    STUDENT_MJ, STUDENT_MJ, STUDENT_MJ,
                                    STUDENT_THD, STUDENT_BPS, STUDENT_BQN,
                                    STUDENT_THD};

    int dice[NUM_REGIONS] = {0, 1, 2, 3, 3, 3, 4, 4, 4, 5, 1, 2, 3, 3, 
                             3, 0, 1, 2, 0};
                             
    Game g = newGame(disciplines, dice);
    
    // Make sure all is well:
    assert(getWhoseTurn(g)  == NO_ONE);
    assert(getTurnNumber(g) == TERRA_NULLIS);
    
    int regionID = 0;
    while (regionID < NUM_REGIONS) {
        int regionDisciplineValue = disciplines[regionID];
        assert(getDiscipline(g, regionID) == regionDisciplineValue);
        regionID++;
    }
    
    disposeGame(g);
    printf("Passed!\n");
}

/*
 *  Game Simulation 
 * 
 *  Basic simulation of a Knowledge Island game.
 *
 *  17.05.2017 | Lucas & Sebastien
 *
 *  How the "game" is going (feel free to add/change)
 *  - Everything starts as should be, test that it is
 *  - Test that it's UNI_A's turn and make UNI_A Pass
 *  - Do the same for the other UNIs
 *  - Roll a 7 and test it works
 *  - End game?
 */
 
 
 //THIS DOES NOT COMPILE
 
 
void testGameSimulation(void) {
    printf("\n\n19\n\n");
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    
    Game g = newGame(disciplines, dice);
    action currAction;
    
    void testNoStudents(void);
    
    // 1) Test that everything is what it should be at the start
    //KPI points
    assert(getKPIpoints(g,UNI_A) == START_KPI_POINTS);
    assert(getKPIpoints(g,UNI_B) == START_KPI_POINTS);
    assert(getKPIpoints(g,UNI_C) == START_KPI_POINTS);
    
    //ARCs
    assert(getARCs(g,UNI_A) == 0);
    assert(getARCs(g,UNI_B) == 0);
    assert(getARCs(g,UNI_C) == 0);
    
    //G08s
    assert(getGO8s(g,UNI_A) == 0);
    assert(getGO8s(g,UNI_B) == 0);
    assert(getGO8s(g,UNI_C) == 0);
    
    //Campuses
    assert(getCampuses(g,UNI_A) == START_CAMPUSES);
    assert(getCampuses(g,UNI_B) == START_CAMPUSES);
    assert(getCampuses(g,UNI_C) == START_CAMPUSES);
    
    //Patents
    assert(getIPs(g,UNI_A) == 0);
    assert(getIPs(g,UNI_B) == 0);
    assert(getIPs(g,UNI_C) == 0);
    
    //Publications
    assert(getPublications(g,UNI_A) == 0);
    assert(getPublications(g,UNI_A) == 0);
    assert(getPublications(g,UNI_A) == 0);
    
    // 2) Make action (PASS):
    
    
    //  FIRST CYCLE
    
    
    // First players turn
    assert(getWhoseTurn(g) == UNI_A);
    throwDice(g, 2);
    assert(getTurnNumber(g) == 0);   
    currAction.actionCode = PASS;
    makeAction(g, currAction);
    
    int counter = 0;
    int currentRegionID = 0;
    while (counter < NUM_REGIONS) {
        currentRegionID = counter;
        
        if ((getDiceValue (g, currentRegionID) == 2) && 
            (getDiscipline(g, currentRegionID) == disciplines[counter])) {
            // increment the players STUDENT_MMONEY 
            // stopped here 
        }
        
    }

    // second players turn 
    assert(getWhoseTurn(g) == UNI_B);
    throwDice(g, 5);
    assert(getTurnNumber(g) == 1);   
    currAction.actionCode = PASS;
    makeAction(g, currAction);
    
    
    // third players turn
    assert(getWhoseTurn(g) == UNI_C);
    throwDice(g, 10);
    assert(getTurnNumber(g) == 2);   
    currAction.actionCode = PASS;
    makeAction(g, currAction);
    
      //  SECOND CYCLE
     
    
    //assert(getWhoseTurn(g) == UNI_A);
    //currAction.actionCode =       //Unfinished code or saving bug?
    //currAction.destination = 
    
    // 3) Roll a 7 and check all MTVs and M$s have turned into ThDs
    
    int UniAMStdts = getStudents(g,UNI_A,STUDENT_MMONEY) +
                            getStudents(g,UNI_A,STUDENT_MTV);
    
    int UniBMStdts = getStudents(g,UNI_B,STUDENT_MMONEY) +
                            getStudents(g,UNI_A,STUDENT_MTV);
                            
    int UniCMStdts = getStudents(g,UNI_C,STUDENT_MMONEY) +
                            getStudents(g,UNI_A,STUDENT_MTV);
    
    int UniAThDs = getStudents(g,UNI_A,STUDENT_THD);
    
    int UniBThDs = getStudents(g,UNI_B,STUDENT_THD);
    
    int UniCThDs = getStudents(g,UNI_C,STUDENT_THD);
    
    throwDice(g, 7);
    assert(getTurnNumber(g) == 3);
    
    assert(getStudents(g,UNI_A, STUDENT_THD) == UniAMStdts + UniAThDs);
    assert(getStudents(g,UNI_B, STUDENT_THD) == UniBMStdts + UniBThDs);
    assert(getStudents(g,UNI_C, STUDENT_THD) == UniCMStdts + UniCThDs);
    
    
    disposeGame(g);
}

void testNoStudents(void) {
    printf("\n\n10\n\n");
    //testing they only have the default students at the start
    //"They have 3 x BPS, 3 x B?, 1 x MTV, 1 x MJ, 1 x M$, and no ThDs."
    
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    
    Game g = newGame(disciplines, dice);
    
    assert(getStudents(g,UNI_A,STUDENT_THD) == START_STUDENTS_THD);
    assert(getStudents(g,UNI_A,STUDENT_BPS) == START_STUDENTS_BPS);
    assert(getStudents(g,UNI_A,STUDENT_BQN) == START_STUDENTS_BQN);
    assert(getStudents(g,UNI_A,STUDENT_MJ) == START_STUDENTS_MJ);
    assert(getStudents(g,UNI_A,STUDENT_MTV) == START_STUDENTS_MTV);
    assert(getStudents(g,UNI_A,STUDENT_MMONEY) == START_STUDENTS_MMONEY);
    
    assert(getStudents(g,UNI_B,STUDENT_THD) == START_STUDENTS_THD);
    assert(getStudents(g,UNI_B,STUDENT_BPS) == START_STUDENTS_BPS);
    assert(getStudents(g,UNI_B,STUDENT_BQN) == START_STUDENTS_BQN);
    assert(getStudents(g,UNI_B,STUDENT_MJ) == START_STUDENTS_MJ);
    assert(getStudents(g,UNI_B,STUDENT_MTV) == START_STUDENTS_MTV);
    assert(getStudents(g,UNI_B,STUDENT_MMONEY) == START_STUDENTS_MMONEY);
    
    assert(getStudents(g,UNI_C,STUDENT_THD) == START_STUDENTS_THD);
    assert(getStudents(g,UNI_C,STUDENT_BPS) == START_STUDENTS_BPS);
    assert(getStudents(g,UNI_C,STUDENT_BQN) == START_STUDENTS_BQN);
    assert(getStudents(g,UNI_C,STUDENT_MJ) == START_STUDENTS_MJ);
    assert(getStudents(g,UNI_C,STUDENT_MTV) == START_STUDENTS_MTV);
    assert(getStudents(g,UNI_C,STUDENT_MMONEY) == START_STUDENTS_MMONEY);
    
    disposeGame(g);
    
}

void testRetraining(void) {
   printf("\n\n11\n\n");
    //Game g = newGame(DEFAULT_DISCIPLINES, DEFAULT_DICE); 
    //that ^^ didn't work so I replace it with vv (should be the same?)
    
    int disciplines[] = DEFAULT_DISCIPLINES;
    int dice[] = DEFAULT_DICE;
    
    Game g = newGame(disciplines, dice);
    
    //throwDice(g, 0);

    int currentPlayer = getWhoseTurn(g);
    action currAction;
    
    // First 

    currAction.actionCode = RETRAIN_STUDENTS;
    currAction.disciplineFrom = STUDENT_THD;
    currAction.disciplineTo = STUDENT_BPS;
                        

    assert(isLegalAction(g, currAction) == FALSE);


    
    // Second
    currAction.disciplineFrom = STUDENT_BPS;
    currAction.disciplineTo = STUDENT_MTV;
    assert(getStudents(g, currentPlayer, STUDENT_BPS) == 
                START_STUDENTS_BPS); 
    assert(getStudents(g, currentPlayer, STUDENT_MTV) == 
                START_STUDENTS_MTV);
    assert(isLegalAction(g, currAction) == TRUE);
    makeAction(g, currAction);
    // should have lost 3 BPS and gained 1 MTV
    assert(getStudents(g, currentPlayer, STUDENT_BPS) == 
                START_STUDENTS_BPS - 3);
    assert(getStudents(g, currentPlayer, STUDENT_MTV) == 
                START_STUDENTS_MTV + 1);

    currAction.disciplineFrom = STUDENT_MJ;
    assert(getStudents(g, currentPlayer, STUDENT_BPS) == 
                START_STUDENTS_BPS); 
                
    // we don't have enough MJ studnets to retrain
    currAction.disciplineTo = STUDENT_BPS;
    assert(isLegalAction(g, currAction) == FALSE);

    disposeGame(g);
}
