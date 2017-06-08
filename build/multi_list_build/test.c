/*
**  Testing Source Code
**
**  Basic file containing source code for unit tests correspondng
**  to main program code, make sure all tests are very EXTENSIVE
**  
**  30.05.2017 | Lucas Barbosa | HS1917 | Open Source Software (C)
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// Testing interface.
#include "test.h"

void runTests(void) {
    
    /*
    **  Test: Pushing Items
    **    > Inserting from end 
    **    > Returning correct link
    */
    
    List pushTestList = createList();
    Link currPushNode;
    assert(pushTestList != NULL);
    currPushNode = push(pushTestList, 2155, "Kellyville");
    assert(currPushNode->areaCode == 2155);
    currPushNode = push(pushTestList, 3166, "Rouse Hill");
    assert(currPushNode->areaCode == 3166);
    currPushNode = push(pushTestList, 2154, "Castle Hill");
    assert(currPushNode->areaCode == 2154);
    currPushNode = push(pushTestList, 2174, "Baulkham Hills");
    assert(currPushNode->areaCode == 2174);
    currPushNode = push(pushTestList, 1323, "Strathfiled");
    assert(currPushNode->areaCode == 1323);
    currPushNode = push(pushTestList, 3563, "Redfern");
    assert(currPushNode->areaCode == 3563);
    currPushNode = push(pushTestList, 2313, "Scofields");
    assert(currPushNode->areaCode == 2313);
    currPushNode = push(pushTestList, 1453, "Central");
    assert(currPushNode->areaCode == 1453);
    currPushNode = push(pushTestList, 1753, "Westmead");
    assert(currPushNode->areaCode == 1753);
    
    assert(pushTestList->head->areaCode == 2155);
    assert(pushTestList->head->next->areaCode == 3166);
    assert(pushTestList->head->next->next->prev->areaCode == 3166);
    assert(pushTestList->head->next->next->areaCode == 2154);
    assert(pushTestList->head->next->next->next->prev->areaCode == 2154);
    assert(pushTestList->head->next->next->next->areaCode == 2174);
    assert(pushTestList->head->next->next->next->next->prev->areaCode == 2174);
    assert(pushTestList->head->next->next->next->next->areaCode == 1323);
    assert(pushTestList->head->next->next->next->next->next->prev->areaCode == 1323);
    assert(pushTestList->head->next->next->next->next->next->areaCode == 3563);
    assert(pushTestList->head->next->next->next->next->next->next->prev->areaCode == 3563);
    assert(pushTestList->head->next->next->next->next->next->next->areaCode == 2313);
    assert(pushTestList->head->next->next->next->next->next->next->next->prev->areaCode == 2313);
    assert(pushTestList->head->next->next->next->next->next->next->next->areaCode == 1453);
    assert(pushTestList->head->next->next->next->next->next->next->next->next->prev->areaCode == 1453);
    assert(pushTestList->head->next->next->next->next->next->next->next->next->areaCode == 1753);
    assert(pushTestList->head->next->next->next->next->next->next->next->next->next == NULL);
    
    destroy(pushTestList);
    
    /*
    **  Test: Popping Items (Deleting from top)
    */
    
    
    /*
    **  Test: Pusing Items (Inserting from top)
    */
  
 
    /*
    **  Test: Length of List 
    */
  
    
    /*
    **  Test: Pez Dispenser (Removing and Returning top node)
    */
    
    
    /*
    **  Test: Getter (Retrieving values from indexes in list)
    */
    
    
    /*
    **  Test: Median (First prac test)
    */
    
    printf("All tests passed.\n");
    
}
