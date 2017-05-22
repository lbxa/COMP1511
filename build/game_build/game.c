#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "Game.h"

#define VERTICAL_GRID_SIZE 11
#define HORIZONTAL_GRID_SIZE 12

#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, \
STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, \
STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, \
STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, \
STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5} 

#define LEFT 'L'
#define RIGHT 'R'
#define BACK 'B'
#define PATH_END '\0'
#define TERRA_NULLIUS -1
#define DOUBLE 1 

//for the vertex grid, outside of the board use this
#define UNDEFINED -1

#define NUM_DISCIPLINES 6

// isort 
#define START_ITEM 1

//i think
#define MAX_ARCS 72

//hardcoded hexagons

//direction codes
#define GO_RIGHT 0
#define GO_DOWN_RIGHT 1
#define GO_DOWN_LEFT 2
#define GO_LEFT 3
#define GO_UP_LEFT 4
#define GO_UP_RIGHT 5


//trade port locations
// i'm storing the vertex adjacent to the port according to Alex Huang's diagram  in his blog post


//actually tjeres two places for each port
//TODO ADD THEM IN 
#define TRADEPORT_MTV_XA 4
#define TRADEPORT_MTV_YA 1
#define TRADEPORT_MTV_XB 3
#define TRADEPORT_MTV_YB 1

#define TRADEPORT_MONEY_XA 7
#define TRADEPORT_MONEY_YA 1
#define TRADEPORT_MONEY_XB 8
#define TRADEPORT_MONEY_YB 1

#define TRADEPORT_QUESTION_XA 10
#define TRADEPORT_QUESTION_YA 6
#define TRADEPORT_QUESTION_XB 11
#define TRADEPORT_QUESTION_YB 5

#define TRADEPORT_JOBS_XA 9
#define TRADEPORT_JOBS_YA 8
#define TRADEPORT_JOBS_XB 8
#define TRADEPORT_JOBS_YB 9

#define TRADEPORT_PROBLEM_SOLVING_XA 2
#define TRADEPORT_PROBLEM_SOLVING_YA 8
#define TRADEPORT_PROBLEM_SOLVING_XB 3
#define TRADEPORT_PROBLEM_SOLVING_YB 9

typedef struct _arc {
    int player;
    int *vertexA;
    int *vertexB;
} arc;

//stores information about each player
typedef struct _player {
    
    // stores how many students/resources the player has
    // students[STUDENT_THD] would store how many ThD students the player has
    // students[STUDENT_BPS] would store how many BPS studnets the player has
    // etc.
    int students[NUM_DISCIPLINES];
    

    int numPublications;
    int numIpPatents;
    
    int kpiPoints;
    
} player;

typedef struct _hexagon {
    int regionID;
    // the dice value you have to roll to get on this hexagon
    int diceValue;
    // the students' discipline (e.g. THD, Bachelor of Money, etc.)
    // i.e. the colour
    int discipline;
    // pointers to the vertex grid
    int *vertexTopLeft;
    int *vertexTopRight;
    int *vertexRight;
    int *vertexBottomRight;
    int *vertexBottomLeft;
    int *vertexLeft;

} hexagon;

//the game ADT
typedef struct _game { 
    int currentTurn;
   
    //hex grid array
    hexagon gameBoard[NUM_REGIONS];
 
    //vertex grid array
    //12 x 11 vertex grid for a settlers of catan map
    int vertexGrid[HORIZONTAL_GRID_SIZE][VERTICAL_GRID_SIZE];
    
    
    
    arc arcs[MAX_ARCS];
    //ARC dynamic array hack
    int currentARCIndex;
    
    player playerA;
    player playerB;
    player playerC;
    
    int playerMostArcs;
    int mostARCs;
    
    int playerMostPublications;
    int mostPublications;
    
    // fun statistics
    // also need this to test when there are no ARCs or publications
    // in getMostARCs() and getMostPublications()
    int totalARCs;
    int totalPublications;
    int totalIpPatents;
   
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

static void addStudents(Game g, hexagon h, int vertex);
static int *pathToVertex(Game g, path p);
static void setStudentAmounts(player *playa);
static int pathLength(path p);
static int findARCtoVertex(Game g, int player, int *vertex);

//What this does is check if there is an ARC on a specific 
static int findARCtoVertex(Game g, int player, int *vertex) {
    
    int isARC = FALSE;
    int i = 0;
   // printf("New game");
    while (i < g->currentARCIndex) {
        if ((g->arcs[i].vertexA == vertex || g->arcs[i].vertexB) &&
            (g->arcs[i].player == player)) {
            isARC = TRUE;
           // printf("findARC i %d vB %p vA %p\n", 
                 //  i, g->arcs[i].vertexA, g->arcs[i].vertexB);
        }
    }
    
    return isARC;
}

static int pathLength(path p) {
    int i = 0;
    while (p[i] != PATH_END) {
        i++;
    }
    return i;
}

// ALEX HUANG PLEASE IMPLEMENT THESE
static int *pathToVertex(Game g, path p) {
    int xCoordinate = 5;
    int yCoordinate = 0;
    int lastXCoord = -1;
    int lastYCoord = -1;
    int direction = GO_DOWN_RIGHT;
    int i = 0;
  //  printf("New path being calculated\n");
    while (p[i] != PATH_END) {
        char dir = p[i];
       // printf("%s\n", &dir);
        if (dir == LEFT) {
            direction--;
            if (direction < GO_RIGHT) {
                direction = GO_UP_RIGHT;
            }
        } else if (dir == RIGHT) {
            direction++;
            if (direction > GO_UP_RIGHT) {
                direction = GO_RIGHT;
            }
        } else if (dir == BACK) {
            //turns around the direction
            direction += 3;
            
            //make sure we dont have invalid directions
            if (direction > GO_UP_RIGHT) {
                direction -= 5;
            }
            //wait dont we just add 3 to direction
            
            xCoordinate = lastXCoord;
            yCoordinate = lastYCoord; //pwned, also helps with arcs
        } else {
            assert(FALSE); //SOMETHING WENT WRONG
        }
        // make sure the path does not go into the sea
        
        lastXCoord = xCoordinate;
        lastYCoord = yCoordinate;
        
        if(p[i] != BACK) {
            if(direction == GO_UP_RIGHT) {
                xCoordinate += 1;
                yCoordinate -= 1;
            }
            else if(direction == GO_UP_LEFT) {
                xCoordinate -= 1;
                yCoordinate -= 1;
            }
            else if(direction == GO_LEFT) {
                xCoordinate -= 1;
            }
            else if(direction == GO_DOWN_RIGHT) {
                xCoordinate += 1;
                yCoordinate += 1;
            }
            else if(direction == GO_DOWN_LEFT) {
                xCoordinate -= 1;
                yCoordinate += 1;
            }
            else if(direction == GO_RIGHT) {
                xCoordinate += 1;
            }
            else {
                assert(FALSE); //wtf????
            }
        }
        assert((g->vertexGrid[xCoordinate][yCoordinate]) != UNDEFINED);
      //  printf("X %d Y %d DIR %d \n",
              //  xCoordinate, yCoordinate, direction);
        i++;
    }

    return &(g->vertexGrid[xCoordinate][yCoordinate]);
}

static void setStudentAmounts (player *playa) {
    playa->students[STUDENT_THD] = 0;
    playa->students[STUDENT_BPS] = 3;
    playa->students[STUDENT_BQN] = 3;
    playa->students[STUDENT_MJ]  = 1;
    playa->students[STUDENT_MTV] = 1;
    playa->students[STUDENT_MMONEY] = 1;
}

static void makeHexLine (hexagon hexes[], 
    int vertexes[][VERTICAL_GRID_SIZE], int yTop, 
    int xFarLeft, int rows, int start);

static void initializeHexArray (hexagon hexes[], 
    int vertexes[][VERTICAL_GRID_SIZE]);

//make these functions static

static void makeHexLine (hexagon hexes[], 
    int vertexes[][VERTICAL_GRID_SIZE], int yTop, 
    int xFarLeft, int rows, int start) {
    rows = rows + start;
    int xLeft = xFarLeft + 1;     //aka labor
    int xRight = xLeft + 1;      //aka liberals
    int xFarRight = xRight + 1; //aka one nation
    int yMid = yTop + 1;
    int yBottom = yMid + 1;
    while(start < rows) {
        hexes[start].vertexTopLeft     = &(vertexes[xLeft][yTop]);
        hexes[start].vertexTopRight    = &(vertexes[xRight][yTop]);
        hexes[start].vertexRight       = &(vertexes[xFarRight][yMid]);
        hexes[start].vertexBottomRight = &(vertexes[xRight][yBottom]);
        hexes[start].vertexBottomLeft  = &(vertexes[xLeft][yBottom]);
        hexes[start].vertexLeft        = &(vertexes[xFarLeft][yMid]);
        yTop = yTop + 2;
        yMid = yMid + 2;
        yBottom = yBottom + 2;
        start++;
    }
}

static void initializeHexArray (hexagon hexes[], 
    int vertexes[][VERTICAL_GRID_SIZE]) {
    makeHexLine(hexes, vertexes, 2, 0, 3, 0);
    makeHexLine(hexes, vertexes, 1, 2, 4, 3);
    makeHexLine(hexes, vertexes, 0, 4, 5, 7);
    makeHexLine(hexes, vertexes, 1, 6, 4, 12);
    makeHexLine(hexes, vertexes, 2, 8, 3, 16);
}


Game newGame(int discipline[], int dice[]) {
    // note that game in sizeof refers to
    // the struct game - do not write something like
    // malloc(sizeof(Game)) !!!!!
    Game new = malloc(sizeof(game)); 
    new->currentTurn = TERRA_NULLIUS;
    new->totalARCs = 0;
    new->totalPublications = 0;
    new->currentARCIndex = 0;
    
    initializeHexArray(new->gameBoard, new->vertexGrid);
    //needs to include the hexes and shit yo

    int i = 0;
    // why can't we use for loops again?
    // style guide :(
    //initialize gameboard disciplii and diic
    while(i < NUM_REGIONS) {
        new->gameBoard[i].diceValue = dice[i];
        new->gameBoard[i].discipline = discipline[i];
        new->gameBoard[i].regionID = i;
        //we need to put in pointers to the vertex grid
        i++;
    }
    //beginning campoids
    //double loop to initialize the vertices to zeros
    i = 0;
    int j = 0;
    int odd = 0;

    while(j < HORIZONTAL_GRID_SIZE) {
        while(i < VERTICAL_GRID_SIZE) {
            if(odd == 1 && i % 2 == 1) {
                new->vertexGrid[j][i] = UNDEFINED;
            } else if (odd == 0 && i % 2 == 0) {
                new->vertexGrid[j][i] = UNDEFINED;
            } else {
                new->vertexGrid[j][i] = VACANT_VERTEX;
            }
            i++;
        }
        if(j % 2 == 0) {
            if(odd == 1) {
                odd = 0;
            } else {
                odd = 1;
            }
        }
        j++;
        i = 0;
    } //zero out initial vertexes
      //make areas that aren't there UNDEFINED
    
    //now manually UNDEFINE'd a few 
    
    while(i <= 4) {
        if( i == 0 ) {
            new->vertexGrid[i][2] = UNDEFINED;
            new->vertexGrid[i][8] = UNDEFINED;
        }
        if( i <= 2 ) {
            new->vertexGrid[i][1] = UNDEFINED;
            new->vertexGrid[i][9] = UNDEFINED;
        }
        new->vertexGrid[i][0] = UNDEFINED;
        new->vertexGrid[i][10] = UNDEFINED;
        i++;
    }
    
    i = 7;
    
    while(i <= 11) {
        if ( i == 7 ) {
            new->vertexGrid[i][2] = UNDEFINED;
            new->vertexGrid[i][8] = UNDEFINED;
        }
        if( i >= 9 ) {
            new->vertexGrid[i][1] = UNDEFINED;
            new->vertexGrid[i][9] = UNDEFINED;
        }
        new->vertexGrid[i][0] = UNDEFINED;
        new->vertexGrid[i][10] = UNDEFINED;
        i++;
    }

    new->vertexGrid[5][0]  = CAMPUS_A;
    new->vertexGrid[6][10] = CAMPUS_A;
    new->vertexGrid[0][3]  = CAMPUS_B;
    new->vertexGrid[11][7] = CAMPUS_B;
    new->vertexGrid[10][2] = CAMPUS_C;
    new->vertexGrid[1][8]  = CAMPUS_C;
    //campoxen done, tradeports
    
    // give each player the default number of students
    setStudentAmounts(&(new->playerA));
    setStudentAmounts(&(new->playerB));
    setStudentAmounts(&(new->playerC));
    
    
    
    // initialise KPI Points of all pllayers to the default of 20
    new->playerA.kpiPoints = 20;
    new->playerB.kpiPoints = 20;
    new->playerC.kpiPoints = 20;
    
    return new;
}

// free all the memory malloced for the game
void disposeGame(Game gamePointer) {
    //free(&(gamePointer->playerA));
    //free(&(gamePointer->playerB));
    //free(&(gamePointer->playerC));
    
    free(gamePointer);
} //ezpz

// make the specified action for the current player and update the 
// game state accordingly.  
// The function may assume that the action requested is legal.
// START_SPINOFF is not a legal action here
void makeAction(Game g, action a) {
 //   assert(isLegalAction(g, a));
    
    
    
    //use the legal function thing
    //legal must test that plot of land is vacant for campus or edge
    // is empty for ARC
    //legal must check that is not retraining THDs
    //legal must check that there is 3 or more students of a student
    // that is wanting to be exchanged
    //legal has to make sure that discipleFrom and disciplineTo
    if (a.actionCode == PASS) {
        // this is wrong!!!!!!!!!!!
        // pass means you don't do anyting
        // throwDice gets called outside of this function
        
        //~alex tan
        
     //  throwDice(g, 2);
       
    } else if (a.actionCode == BUILD_CAMPUS) {
        
        int *vertex = pathToVertex(g, a.destination);
        int player = getWhoseTurn(g);

        if (player == UNI_A) {
            *vertex = CAMPUS_A;
            g->playerA.kpiPoints += 10;
        } else if (player == UNI_B) {
            *vertex = CAMPUS_B;
            g->playerB.kpiPoints += 10;
        } else if (player == UNI_C) {
            *vertex = CAMPUS_C;
            g->playerC.kpiPoints += 10;
        } 
        
    } else if (a.actionCode == BUILD_GO8) {
        // gets 10 points for upgrading to GO8
        // actually it's 20 points for upgrading, 
        // then you lose 10 for not having campus
        int *vertex = pathToVertex(g, a.destination);
        int player = getWhoseTurn(g);
        
        if ((player == UNI_A) && (*vertex == CAMPUS_A)) {
            *vertex = GO8_A;
            g->playerA.kpiPoints += 10;
        } else if ((player == UNI_B) && (*vertex == CAMPUS_B)) {
            *vertex = GO8_B;
            g->playerB.kpiPoints += 10;
        } else if ((player == UNI_C) && (*vertex == CAMPUS_C)) {
            *vertex = GO8_C;
            g->playerC.kpiPoints += 10;
        }
        
    } else if (a.actionCode == OBTAIN_ARC) {
        int *vertexA = pathToVertex(g, a.destination);
        // index of last non-path-end character
        int index = pathLength(a.destination) - 1;
        a.destination[index] = PATH_END;
        
        int *vertexB = pathToVertex(g, a.destination);

       // printf("Checking the vertexes aren't the same!");
       // printf("vA %p vB %p\n", vertexA, vertexB);
        assert(vertexB != vertexA);

        
        int player = getWhoseTurn(g);
       // printf("player %d\n", player);
       // assert(player != NO_ONE);
        
        if (player == UNI_A) {
            g->playerA.kpiPoints += 2;
        } else if (player == UNI_B) {
            g->playerB.kpiPoints += 2;
        } else if (player == UNI_C) {
            g->playerC.kpiPoints += 2;
        } 

        arc newArc = {player, vertexA, vertexB};
        g->arcs[g->currentARCIndex] = newArc;
       // printf("arc player %d\n", g->arcs[g->currentARCIndex].player);
        g->currentARCIndex++;
        
    } else if (a.actionCode == START_SPINOFF) {
        //srand(time(NULL));
		//this causes compilation error
        int dice = (rand() % 3)+1;
        if (dice > 2) {
            
            // publications
            // increases the player's number of publications and the 
            // total game publications if the new increased number of 
            // publications is greater than the highst amount stored in 
            // the game, then that playeris noted down for having the 
            // most publications, and the highest number of publications 
            // is updated.
            
            if (getWhoseTurn(g) == UNI_A) {
                g->playerA.numPublications++;
                g->totalPublications++;
                
                if (g->playerA.numPublications > g->mostPublications) {
                    g->playerMostPublications = UNI_A;
                    g->mostPublications = g->playerA.numPublications;
                }
            } else if (getWhoseTurn(g) == UNI_B) {
                g->playerB.numPublications++;
                g->totalPublications++;

                if (g->playerB.numPublications > g->mostPublications) {
                    g->playerMostPublications = UNI_B;
                    g->mostPublications = g->playerB.numPublications;
                }
            } else if (getWhoseTurn(g) == UNI_C) {
                g->playerC.numPublications++;
                g->totalPublications++;

                if (g->playerC.numPublications > g->mostPublications) {
                    g->playerMostPublications = UNI_C;
                    g->mostPublications = g->playerC.numPublications;
                }
            }
        } else if (dice <= 2) {
            // player gets 10 kpiPoints for each IP patent
            if (getWhoseTurn(g) == UNI_A) {
                g->playerA.numIpPatents++;
                g->playerA.kpiPoints += 10;
            } else if (getWhoseTurn(g) == UNI_B) {
                g->playerB.numIpPatents++;
                g->playerB.kpiPoints += 10;
            } else if (getWhoseTurn(g) == UNI_C) {
                g->playerC.numIpPatents++;
                g->playerC.kpiPoints += 10;
            }
        }
    } else if (a.actionCode == RETRAIN_STUDENTS) {
        int player = getWhoseTurn(g);
        if (player == UNI_A) {
            g->playerA.students[a.disciplineFrom] -= 
                getExchangeRate(g, UNI_A, 
                                a.disciplineFrom, a.disciplineTo);
            g->playerA.students[a.disciplineTo] += 1;
        } else if (player == UNI_B) {
            g->playerB.students[a.disciplineFrom] -= 
                getExchangeRate(g, UNI_B, 
                                a.disciplineFrom, a.disciplineTo);
            g->playerB.students[a.disciplineTo] += 1;
        } else if (player == UNI_C) {
            g->playerC.students[a.disciplineFrom] -= 
                getExchangeRate(g, UNI_C, 
                                a.disciplineFrom, a.disciplineTo);
            g->playerC.students[a.disciplineTo] += 1;
        }
    }
}

// advance the game to the next turn, 
// assuming that the dice has just been rolled and produced diceScore
// the game starts in turn -1 (we call this state "Terra Nullis") and 
// moves to turn 0 as soon as the first dice is thrown. 



// Whenever a 7 is thrown, immediately after any new students are produced, 
// all MTV and M$ students of all universities decide to switch to ThD's.
static void convertToTHD(player *p) {
    p->students[STUDENT_THD] += p->students[STUDENT_MTV];
    p->students[STUDENT_THD] += p->students[STUDENT_MMONEY];
    
    p->students[STUDENT_MTV] = 0;
    p->students[STUDENT_MMONEY] = 0;
}

static void addStudents(Game g, hexagon h, int vertex) {
    if (vertex == CAMPUS_A) {
        g->playerA.students[h.discipline] += 1;
    } else if (vertex == GO8_A) {
        g->playerA.students[h.discipline] += DOUBLE;
    } else if (vertex == CAMPUS_B) {
        g->playerB.students[h.discipline] += 1;
    } else if (vertex == GO8_B) {
        g->playerB.students[h.discipline] += DOUBLE;
    } else if (vertex == CAMPUS_C) {
        g->playerC.students[h.discipline] += 1;
    } else if (vertex == GO8_C) {
        g->playerC.students[h.discipline] += DOUBLE;
    }
}

// done - Alex Tan
void throwDice(Game g, int diceScore) {
    assert(diceScore >= 2);
    
    // Universities take turns in throwing a pair of dice. The result determines
    // which areas produce students. Campuses adjacent to areas which produce 
    // students get one student of the type the region produces (except GO8 campuses get 2). 
    // This applies to all campuses of all universities which are adjacent, 
    // not just campuses of the university whose turn it is.
    
    
    int i = 0;
    while (i < NUM_REGIONS) {

        hexagon h = g->gameBoard[i];
        
        if (diceScore == h.diceValue) {
            addStudents(g, h, *(h.vertexTopLeft));
            addStudents(g, h, *(h.vertexTopRight));
            addStudents(g, h, *(h.vertexRight));
            addStudents(g, h, *(h.vertexBottomRight));
            addStudents(g, h, *(h.vertexBottomLeft));
            addStudents(g, h, *(h.vertexLeft));
        }
       
        i++;
    }

    if (diceScore == 7) {
        // Whenever a 7 is thrown, immediately after any new students are produced, 
        // all MTV and M$ students of all universities decide to switch to ThD's.
        
        convertToTHD(&(g->playerA));
        convertToTHD(&(g->playerB));
        convertToTHD(&(g->playerC));
        
    } 
    g->currentTurn++;
  
   printf("Dice thrown! Current turn updated: %d\n", g->currentTurn);
}

/* **** Functions which GET data about the game aka GETTERS **** */

// what type of students are produced by the specified region?
// regionID is the index of the region in the newGame arrays (above) 
// see discipline codes above
// done - ALex Tan
int getDiscipline(Game g, int regionID) {
    assert(g != NULL);
    hexagon hex = (g->gameBoard)[regionID];
    return hex.discipline;
}

// what dice value produces students in the specified region?
// 2..12
// done - Alex Tan
int getDiceValue(Game g, int regionID) {
    assert(g != NULL);
    hexagon hex = (g->gameBoard)[regionID];
    return hex.diceValue;
}

// which university currently has the prestige award for the most ARCs?
// this is NO_ONE until the first arc is purchased after the game 
// has started.  
// Alex Tan
int getMostARCs(Game g) {
    assert(g != NULL);
    int mostARCs = NO_ONE;
    if (g->totalARCs > 0) {
        mostARCs = g->playerMostArcs;
    }
    return mostARCs;
}

// which university currently has the prestige award for the most pubs?
// this is NO_ONE until the first publication is made.
// Alex Tan
int getMostPublications(Game g) {
    assert(g != NULL);
    int mostPublications = NO_ONE;
    if (g->totalPublications > 0) {
        mostPublications = g->playerMostPublications;
    }
    return mostPublications;
}

// return the current turn number of the game -1,0,1, ..
// done
int getTurnNumber(Game g) {
    int turnNumber = g->currentTurn;
    return turnNumber;
}

// return the player id of the player whose turn it is 
// the result of this function is NO_ONE during Terra Nullis
int getWhoseTurn(Game g) {
    int turn = NO_ONE; //defualt value
   // printf("%d\n", g->currentTurn);
    if (g->currentTurn != TERRA_NULLIUS) {
        //do some logic here i guess
        turn = (g->currentTurn % 3) + 1;
    }
    return turn;
}

// return the contents of the given vertex (ie campus code or 
// VACANT_VERTEX)
// DONE
int getCampus(Game g, path p) {
    int *vertex = pathToVertex(g, p);
    return *vertex;
}

// the contents of the given edge (ie ARC code or vacent ARC)
// DONE
int getARC(Game g, path pathToEdge) {
    int arcOwner = VACANT_ARC;

    // last vertex in path

    int *vertexA = pathToVertex(g, pathToEdge);
    
    // find second last vertex in path
    int index = pathLength(pathToEdge) - 1;
    pathToEdge[index] = PATH_END;

    // second last vertex in path
    int *vertexB = pathToVertex(g, pathToEdge);
    
  //  printf("vA %p vB %p\n", vertexA, vertexB);
  //  assert(vertexB != vertexA);
    // have the 2 vertex values
    // now we loop through the ARC array, and find
    // the corresponding ARC

    int i = 0;
    
    int flag = TRUE;

    while (i < g->currentARCIndex && flag == TRUE) {
        
       // printf("i %d cAI %d g.cAI[i].player %d g.[i].player %d\n", 
        //        i, g->currentARCIndex, 
      //          g->arcs[g->currentARCIndex].player,
       //
     //  g->arcs[i].player);
                
        arc a = g->arcs[i];
        
       // printf("a.vA %p a.vB %p vA %p vB %p\n",
         //       a.vertexA, a.vertexB, vertexA, vertexB);
        
        if ((a.vertexA == vertexA && a.vertexB == vertexB) 
            || (a.vertexB == vertexA && a.vertexA == vertexB)) {
            arcOwner = g->arcs[i].player;
            flag = FALSE;
        }
        i++;
    }
    printf("%d\n", arcOwner);
    return arcOwner;
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
    //player playerPointer;
    int player = getWhoseTurn(g);
    
    /*if (playerValue == UNI_A) {
        playerPointer = g->playerA;
    } else if (playerValue == UNI_B) {
        playerPointer = g->playerB;
    } else if (playerValue == UNI_C) {
        playerPointer = g->playerC;
    } else {
        printf("No player!");
        assert(FALSE);
    }*/
    
    // makeAction section
    
    //legal must test that plot of land is vacant for campus or edge
    // is empty for ARC - done
    //legal must check that ARCS are next to a campus
    //legal must check that is not retraining THDs
    //legal must check that there is 3 or more students of a student
    // that is wanting to be exchanged
    //legal has to make sure that discipleFrom and disciplineTo
    
    
    
    if (getTurnNumber(g) == TERRA_NULLIUS ) {
        // no action are valid during terra nullius

        legality = FALSE;
    } else if (a.actionCode == PASS) {
        legality = TRUE;
    } else if (a.actionCode == BUILD_CAMPUS) {
        
        // when building campuses, you can only
        // build it on an empty vertex
        //AND YOU NEED AN ARC!!!!
        
        //someone finish this
        
        // 1. we can only build a campus on an empty vertex.
        // 2. it must have an arc connecting to it
        // 3. also check we are not building a campus adjacent
        // to a preexisting campus (later down)
        int *vertex = pathToVertex(g, a.destination);
        if ((*vertex == VACANT_VERTEX) && 
        (findARCtoVertex(g, player, vertex))) {
            legality = TRUE;
        } else {
            legality = FALSE;
        }
    
    
         // make sure we have enoough resources to build a campus
        // requires 1 problemsolving, 1 ?, 1 Jobs, 1 TV
        
        if (player == UNI_A) {
            if (g->playerA.students[STUDENT_BPS] < 1 || 
                  g->playerA.students[STUDENT_BQN] < 1 || 
                  g->playerA.students[STUDENT_MJ] < 1 || 
                  g->playerA.students[STUDENT_MTV] < 1) {
                legality = FALSE;
            } 
        } else if (player == UNI_B) {
             if (g->playerB.students[STUDENT_BPS] < 1 || 
                   g->playerB.students[STUDENT_BQN] < 1 || 
                   g->playerB.students[STUDENT_MJ] < 1 ||
                   g->playerB.students[STUDENT_MTV] < 1) {
                legality = FALSE;
            } 
        } else if (player == UNI_C) {
            if (g->playerC.students[STUDENT_BPS] < 1 || 
                  g->playerC.students[STUDENT_BQN] < 1 || 
                  g->playerC.students[STUDENT_MJ] < 1 ||
                  g->playerC.students[STUDENT_MTV] < 1) {
                legality = FALSE;
            } 
        } else {
            assert(FALSE);
        }
        
        //test for a LEFT, a BACK, and a RIGHT to ensure 100% that
        //there is no neighbouring camplud
    
        int index = pathLength(a.destination);
        a.destination[index + 1] = PATH_END;
        a.destination[index] = RIGHT;
        if (pathToVertex(g, a.destination) != VACANT_VERTEX) {
            legality = FALSE;
        }
        
        a.destination[index] = LEFT;
        if (pathToVertex(g, a.destination) != VACANT_VERTEX) {
            legality = FALSE;
        }
        
        a.destination[index] = BACK;
        if (pathToVertex(g, a.destination) != VACANT_VERTEX) {
            legality = FALSE;
        }
        
    
    } else if (a.actionCode == BUILD_GO8) {
        //test that we're building it ontop of a pre-existing campus owned by the same player
        //todo
        
        if((*(pathToVertex(g, a.destination)) == CAMPUS_A &&
            player == UNI_A) ||
            (*(pathToVertex(g, a.destination)) == CAMPUS_B &&
            player == UNI_B) ||
            (*(pathToVertex(g, a.destination)) == CAMPUS_C &&
            player == UNI_C)) {
                legality = TRUE;
            }
          
        
         // make sure we have enoough resources to build an ARC
        // requires 2 Jobs, 3 Money
        
        if (player == UNI_A) {
            if (!(g->playerA.students[STUDENT_MJ] >= 2 &&
                  g->playerA.students[STUDENT_MMONEY] >= 3)) {
                legality = FALSE;
            } 
        } else if (player == UNI_B) {
             if (!(g->playerB.students[STUDENT_MJ] >= 2 &&
                   g->playerB.students[STUDENT_MMONEY] >= 3)) {
                legality = FALSE;
            } 
        } else if (player == UNI_C) {
             if (!(g->playerC.students[STUDENT_MJ] >= 2 &&
                   g->playerC.students[STUDENT_MMONEY] >= 3)) {
                legality = FALSE;
            } 
        } else {
            assert(FALSE);
        }
        
    } else if (a.actionCode == OBTAIN_ARC) {
        // making sure that the ARC does not belong to anyone else
        int edge = getARC(g, a.destination);
        if (edge == VACANT_ARC) {

            int *vertexA = pathToVertex(g, a.destination);
            int index = pathLength(a.destination) - 1;
            a.destination[index] = PATH_END;
            int *vertexB = pathToVertex(g, a.destination);

            printf("ARC build legality vA %p %d vB %p %d\n", 
            vertexA, *vertexA, vertexB, *vertexB);

            if((findARCtoVertex(g, player, vertexA)) || 
               (findARCtoVertex(g, player, vertexB))) {
                legality = TRUE;
            } else if ((player == UNI_A) && 
            ((*vertexB == CAMPUS_A) || (*vertexA == GO8_A) || 
            (*vertexA == CAMPUS_A) || (*vertexB == GO8_A))) {
                legality = TRUE;
            } else if ((player == UNI_B) && 
            ((*vertexB == CAMPUS_B) || (*vertexA == GO8_B) || 
            (*vertexA == CAMPUS_B) || (*vertexB == GO8_B))) {
                legality = TRUE;
            } else if ((player == UNI_C) && 
            ((*vertexB == CAMPUS_C) || (*vertexA == GO8_C) ||
            (*vertexA == CAMPUS_C) || (*vertexB == GO8_C))) {
                legality = TRUE;
            }
        }
        
        // make sure we have enoough resources to build an ARC
        // requires one ? and one Problemsolving
        
    
        if (player == UNI_A) {
            if (!(g->playerA.students[STUDENT_BQN] >= 1 && 
                  g->playerA.students[STUDENT_BPS] >= 1)) {
                legality = FALSE;
            } 
        } else if (player == UNI_B) {
            if (!(g->playerB.students[STUDENT_BQN] >= 1 && 
                  g->playerB.students[STUDENT_BPS] >= 1)) {
                legality = FALSE;
            } 
        } else if (player == UNI_C) {
            if (!(g->playerC.students[STUDENT_BQN] >= 1 && 
                  g->playerC.students[STUDENT_BPS] >= 1)) {
                legality = FALSE;
            } 
        } else {
            assert(FALSE);
        }
        
    } else if (a.actionCode == START_SPINOFF) {
        
         // make sure we have enoough resources to build an ARC
        // requires one Jobs and one TV and one Money
        
        if (player == UNI_A) {
            if (!(g->playerA.students[STUDENT_MJ] >= 1 
                  && 
                  g->playerA.students[STUDENT_MTV] >= 1 
                  && 
                  g->playerA.students[STUDENT_MMONEY])) {
                legality = FALSE;
            } else {
                legality = TRUE;
            }
        } else if (player == UNI_B) {
            if (!(g->playerB.students[STUDENT_MJ] >= 1 
                  && 
                  g->playerB.students[STUDENT_MTV] >= 1 
                  && 
                  g->playerB.students[STUDENT_MMONEY])) {
                legality = FALSE;
            } else {
                legality = TRUE;
            }
        } else if (player == UNI_C) {
            if (!(g->playerC.students[STUDENT_MJ] >= 1 
                  &&
                  g->playerC.students[STUDENT_MTV] >= 1
                  && 
                  g->playerC.students[STUDENT_MMONEY])) {
                legality = FALSE;
            } else {
                legality = TRUE;
            }
        } else {
            
            assert(FALSE);
        }
        // make sure we have required resources
    } else if (a.actionCode == RETRAIN_STUDENTS) {
        
        //done
        
        if (a.disciplineFrom == STUDENT_THD) {
            legality = FALSE;
        } else {
            int studentRatio = getExchangeRate(g, player, a.disciplineFrom,
                                               a.disciplineTo);
            
            if (player == UNI_A) {
                legality = g->playerA.students[a.disciplineFrom] 
                            >= 
                            studentRatio;
            } else if (player == UNI_B) {
                legality = g->playerB.students[a.disciplineFrom]
                            >= 
                            studentRatio;
            } else if (player == UNI_C) {
                legality = g->playerC.students[a.disciplineFrom] 
                            >= 
                            studentRatio;
            } else {
                assert(FALSE);
            }
        }
        
       
        
    
    } else if (a.actionCode == OBTAIN_PUBLICATION) {
        //done (not a valid action code)
        
        legality = FALSE;
        
    }  else if (a.actionCode == OBTAIN_IP_PATENT) {
        //done (not a valid action code)
        
        legality = FALSE;
        
    } else {
        
        // not even a valid action code
        // what kind of dodgy stuff is going on here
        legality = FALSE;
    }

    return legality;
}

// --- get data about a specified player ---

// return the number of KPI points the specified player currently has
// done - Alex Tan
int getKPIpoints(Game g, int player) {
    assert(player >= UNI_A && player <= UNI_C);
    
    // regular player points
    int KPIpoints = 0;
    if (player == UNI_A) {
        KPIpoints += g->playerA.kpiPoints;
    } else if (player == UNI_B) {
        KPIpoints += g->playerB.kpiPoints;
    } else {
        KPIpoints += g->playerC.kpiPoints;
    }
    
    // bouns 10 points for having the most ARCs
    if (g->playerMostArcs == player) {
        KPIpoints += 10;
    }
    
    // bonus 10 points for having most publications
    if (g->playerMostPublications == player) {
        KPIpoints += 10;
    }
    
    return KPIpoints;
}

// return the number of ARC grants the specified player currently has
// done - Alex Tan
int getARCs(Game g, int player) {
    int ARCs = 0;
    int i = 0;
    // loops through all the ARCs and increments i
    // if it is owned by the specified player
    while (i < g->currentARCIndex) {
        arc a = g->arcs[i];
        if (a.player == player) {
            ARCs++;
        }
        i++;
    }
    return ARCs;
}

// return the number of GO8 campuses the specified player currently has
// done - Alex Tan
int getGO8s(Game g, int player) {
    int GO8s = 0;
    
    int i = 0;
    while (i < HORIZONTAL_GRID_SIZE) {
        int j = 0;
        while (j < VERTICAL_GRID_SIZE) {
            int vertex = g->vertexGrid[i][j];
            if (vertex == GO8_A && player == UNI_A) {
                GO8s++;
            } else if (vertex == GO8_B && player == UNI_B) {
                GO8s++;
            } else if (vertex == GO8_C && player == UNI_C) {
                GO8s++;
            }
            j++;
        }
        i++;
    }
    
    return GO8s;
}

// return the number of normal Campuses the specified player currently has
// done - Alex Tan
int getCampuses(Game g, int player) {
    int campuses = 0;
    
    int i = 0;
    while (i < HORIZONTAL_GRID_SIZE) {
        int j = 0;
        while (j < VERTICAL_GRID_SIZE) {
            int vertex = g->vertexGrid[i][j];
            if (vertex == CAMPUS_A && player == UNI_A) {
                campuses++;
            } else if (vertex == CAMPUS_B && player == UNI_B) {
                campuses++;
            } else if (vertex == CAMPUS_C && player == UNI_C) {
                campuses++;
            }
            j++;
        }
        i++;
    }
    
    return campuses;
}

// return the number of IP Patents the specified player currently has
// done - Alex Tan
int getIPs(Game g, int player) {
    assert(g != NULL);
    assert(player >= UNI_A && player <= UNI_C);
    
    int patents = 0;
    if (player == UNI_A) {
        patents = (g->playerA).numIpPatents;
    } else if (player == UNI_B) {
        patents = (g->playerB).numIpPatents;
    } else {
        patents = (g->playerC).numIpPatents;
    }
    return patents;
}

// return the number of Publications the specified player currently has
// done - Alex Tan
int getPublications(Game g, int player) {
    assert(g != NULL);
    assert(player >= UNI_A && player <= UNI_C);
    
    int publications = 0;
    if (player == UNI_A) {
        publications = (g->playerA).numPublications;
    } else if (player == UNI_B) {
        publications = (g->playerB).numPublications;
    } else {
        publications = (g->playerC).numPublications;
    }
    return publications;
}

// return the number of students of the specified discipline type 
// the specified player currently has
// done - Alex Tan
int getStudents(Game g, int player, int discipline) {
    assert(g != NULL);
    
    assert((discipline >= STUDENT_THD) && 
           (discipline <= STUDENT_MMONEY));
           
    assert(player >= UNI_A && player <= UNI_C);
    
    int students = 0;
    if (player == UNI_A) {
        students = (g->playerA).students[discipline];
    } else if (player == UNI_B) {
        students = (g->playerB).students[discipline];
    } else if (player == UNI_C) {
        students = (g->playerC).students[discipline];
    } else {
        assert(FALSE); // terra nullius
    }
    return students;
}

// return how many students of discipline type disciplineFrom
// the specified player would need to retrain in order to get one 
// student of discipline type disciplineTo.  This will depend 
// on what retraining centers, if any, they have a campus at.
//TO DO 
int getExchangeRate(Game g, int player,
    int disciplineFrom, int disciplineTo) {
    
    assert((disciplineFrom > STUDENT_THD) &&
           (disciplineFrom <= STUDENT_MMONEY));
           
    assert((disciplineTo >= STUDENT_THD) && 
           (disciplineTo <= STUDENT_MMONEY));
           
    assert(player >= UNI_A && player <= UNI_C);
    
    int *vertexMtvA = &(g->vertexGrid
    [TRADEPORT_MTV_XA][TRADEPORT_MTV_YA]);
    int *vertexMoneyA = &(g->vertexGrid
    [TRADEPORT_MONEY_XA][TRADEPORT_MONEY_YA]);
    int *vertexQuestionA = &(g->vertexGrid
    [TRADEPORT_QUESTION_XA][TRADEPORT_QUESTION_YA]);
    int *vertexJobsA = &(g->vertexGrid
    [TRADEPORT_JOBS_XA][TRADEPORT_JOBS_YA]);
    int *vertexProblemSolvingA = &(g->vertexGrid
    [TRADEPORT_PROBLEM_SOLVING_XA][TRADEPORT_PROBLEM_SOLVING_YA]);
    
    int *vertexMtvB = &(g->vertexGrid
    [TRADEPORT_MTV_XB][TRADEPORT_MTV_YB]);
    int *vertexMoneyB = &(g->vertexGrid
    [TRADEPORT_MONEY_XB][TRADEPORT_MONEY_YB]);
    int *vertexQuestionB = &(g->vertexGrid
    [TRADEPORT_QUESTION_XB][TRADEPORT_QUESTION_YB]);
    int *vertexJobsB = &(g->vertexGrid
    [TRADEPORT_JOBS_XB][TRADEPORT_JOBS_YB]);
    int *vertexProblemSolvingB = &(g->vertexGrid
    [TRADEPORT_PROBLEM_SOLVING_XB][TRADEPORT_PROBLEM_SOLVING_YB]);


    int exchangesNeeded = 3;
    int i = 0;
    
    while (i < g->currentARCIndex) {
        arc a = g->arcs[i];
        
        int *vertexA = a.vertexA;
        int *vertexB = a.vertexB;
        
        
        if(a.player == player) {
            if (disciplineFrom == STUDENT_MTV && (
                (vertexA == vertexMtvA || vertexB == vertexMtvA)
                ||
                (vertexA == vertexMtvB || vertexB == vertexMtvB) )
               ) {
                   exchangesNeeded = 2;
               } else if (disciplineFrom == STUDENT_MMONEY && (
                (vertexA == vertexMoneyA || vertexB == vertexMoneyA)
                ||
                (vertexA == vertexMoneyB || vertexB == vertexMoneyB) )
               ) {
                   exchangesNeeded = 2;
               } else if (disciplineFrom == STUDENT_MJ && (
                (vertexA == vertexJobsA || vertexB == vertexJobsA)
                ||
                (vertexA == vertexJobsB || vertexB == vertexJobsB) )
               ) {
                   exchangesNeeded = 2;
               } else if (disciplineFrom == STUDENT_BQN && (
                (vertexA == vertexQuestionA || 
                 vertexB == vertexQuestionA)
                ||
                (vertexA == vertexQuestionB || 
                 vertexB == vertexQuestionB) )
               ) {
                   exchangesNeeded = 2;
               } else if (disciplineFrom == STUDENT_BPS && (
                (vertexA == vertexProblemSolvingA || 
                 vertexB == vertexProblemSolvingA)
                ||
                (vertexA == vertexProblemSolvingB ||
                 vertexB == vertexProblemSolvingB) )
               ) {
                   exchangesNeeded = 2;
               }
        }
    }
    return exchangesNeeded;
}
