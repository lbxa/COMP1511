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
    **  Make sure that there are no stupid seg-faults
    */
    
    List pushTestList = newList();
    Link currPushNode;
    int addrArr[9] = {2155, 3166, 2154, 2174, 1323, 3563, 2313, 1453, 1753};
    assert(pushTestList != NULL);
    currPushNode = push(pushTestList, addrArr[0], "Kellyville");
    assert(currPushNode->areaCode == addrArr[0]);
    currPushNode = push(pushTestList, addrArr[1], "Rouse Hill");
    assert(currPushNode->areaCode == addrArr[1]);
    currPushNode = push(pushTestList, addrArr[2], "Castle Hill");
    assert(currPushNode->areaCode == addrArr[2]);
    currPushNode = push(pushTestList, addrArr[3], "Baulkham Hills");
    assert(currPushNode->areaCode == addrArr[3]);
    currPushNode = push(pushTestList, addrArr[4], "Strathfiled");
    assert(currPushNode->areaCode == addrArr[4]);
    currPushNode = push(pushTestList, addrArr[5], "Redfern");
    assert(currPushNode->areaCode == addrArr[5]);
    currPushNode = push(pushTestList, addrArr[6], "Scofields");
    assert(currPushNode->areaCode == addrArr[6]);
    currPushNode = push(pushTestList, addrArr[7], "Central");
    assert(currPushNode->areaCode == addrArr[7]);
    currPushNode = push(pushTestList, addrArr[8], "Westmead");
    assert(currPushNode->areaCode == addrArr[8]);
    
    assert(pushTestList->head->prev == NULL);
    assert(pushTestList->head->areaCode == addrArr[0]);
    assert(pushTestList->head->next->areaCode == addrArr[1]);
    assert(pushTestList->head->next->next->prev->areaCode == addrArr[1]);
    assert(pushTestList->head->next->next->areaCode == addrArr[2]);
    assert(pushTestList->head->next->next->next->prev->areaCode == addrArr[2]);
    assert(pushTestList->head->next->next->next->areaCode == addrArr[3]);
    assert(pushTestList->head->next->next->next->next->prev->areaCode == addrArr[3]);
    assert(pushTestList->head->next->next->next->next->areaCode == addrArr[4]);
    assert(pushTestList->head->next->next->next->next->next->prev->areaCode == addrArr[4]);
    assert(pushTestList->head->next->next->next->next->next->areaCode == addrArr[5]);
    assert(pushTestList->head->next->next->next->next->next->next->prev->areaCode == addrArr[5]);
    assert(pushTestList->head->next->next->next->next->next->next->areaCode == addrArr[6]);
    assert(pushTestList->head->next->next->next->next->next->next->next->prev->areaCode == addrArr[6]);
    assert(pushTestList->head->next->next->next->next->next->next->next->areaCode == addrArr[7]);
    assert(pushTestList->head->next->next->next->next->next->next->next->next->prev->areaCode == addrArr[7]);
    assert(pushTestList->head->next->next->next->next->next->next->next->next->areaCode == addrArr[8]);
    assert(pushTestList->head->next->next->next->next->next->next->next->next->next == NULL);
    
    destroy(pushTestList);
    
    /*
    **  Test: Popping & Pezzing Items (uses array from above test)
    **    > Pop out from top 
    **    > Make sure correct link is returned from pez()
    **  Make sure that there are no stupid seg-faults
    */
    
    List popTestList = newList();
    Link currPopNode;
    assert(pushTestList != NULL);
    currPopNode = push(popTestList, addrArr[0], "Kellyville");
    assert(currPopNode->areaCode == addrArr[0]);
    currPopNode = push(popTestList, addrArr[1], "Rouse Hill");
    assert(currPopNode->areaCode == addrArr[1]);
    currPopNode = push(popTestList, addrArr[2], "Castle Hill");
    assert(currPopNode->areaCode == addrArr[2]);
    currPopNode = push(popTestList, addrArr[3], "Baulkham Hills");
    assert(currPopNode->areaCode == addrArr[3]);
    currPopNode = push(popTestList, addrArr[4], "Strathfiled");
    assert(currPopNode->areaCode == addrArr[4]);
    currPopNode = push(popTestList, addrArr[5], "Redfern");
    assert(currPopNode->areaCode == addrArr[5]);
    currPopNode = push(popTestList, addrArr[6], "Scofields");
    assert(currPopNode->areaCode == addrArr[6]);
    currPopNode = push(popTestList, addrArr[7], "Central");
    assert(currPopNode->areaCode == addrArr[7]);
    currPopNode = push(popTestList, addrArr[8], "Westmead");
    assert(currPopNode->areaCode == addrArr[8]);
    
    currPopNode = pez(popTestList);
    assert(currPopNode->areaCode == addrArr[0]);
    assert(popTestList->head->areaCode == addrArr[1]);
    currPopNode = pez(popTestList);
    assert(currPopNode->areaCode == addrArr[1]);
    assert(popTestList->head->areaCode == addrArr[2]);
    currPopNode = pez(popTestList);
    assert(currPopNode->areaCode == addrArr[2]);
    assert(popTestList->head->areaCode == addrArr[3]);
    currPopNode = pez(popTestList);
    assert(currPopNode->areaCode == addrArr[3]);
    assert(popTestList->head->areaCode == addrArr[4]);
    currPopNode = pez(popTestList);
    assert(currPopNode->areaCode == addrArr[4]);
    assert(popTestList->head->areaCode == addrArr[5]);
    currPopNode = pez(popTestList);
    assert(currPopNode->areaCode == addrArr[5]);
    assert(popTestList->head->areaCode == addrArr[6]);
    currPopNode = pez(popTestList);
    assert(currPopNode->areaCode == addrArr[6]);
    assert(popTestList->head->areaCode == addrArr[7]);
    currPopNode = pez(popTestList);
    assert(currPopNode->areaCode == addrArr[7]);
    assert(popTestList->head->areaCode == addrArr[8]);
 
    /*
    **  Test: Length of Lists
    **    > Returning the exact length of a list
    **    > Make sure that boundary values work accordingly
    **  No stupid seg-faults...
    */
  
    List lenTestList = newList();
    //Link currLenNode;
    assert(lenTestList != NULL);
    
    /*
    **  Test: Pez Dispenser (Removing and Returning top node)
    */
    
    
    /*
    **  Test: Getter (Retrieving values from indexes in list)
    */
    
    /*
    **  Test: Median
    **    > Returning the exact median
    **    > If not median return the value previous to halfway
    **  No stupid seg-faults...
    */
    
    /*
    **  Test: Delete
    **    > Deleting values at beginning
    **    > Deleting values in middle
    **    > Deleting values at end
    **    > Deleting multiple values (all equal)
    **  No stupid seg-faults...
    */
    
    List delTestList = newList();
    Link currDelLink;
    int delTestArr[12] = {2155, 2153, 2155, 2156, 2154, 2155, 2157, 2155, 2155, 2514, 2155, 2155};
    assert(delTestList != NULL);
    
    currDelLink = push(delTestList, delTestArr[0], "Kellyville");
    assert(currDelLink->areaCode == delTestArr[0]);
    currDelLink = push(delTestList, delTestArr[1], "Parramatta");
    assert(currDelLink->areaCode == delTestArr[1]);
    currDelLink = push(delTestList, delTestArr[2], "Kellyville");
    assert(currDelLink->areaCode == delTestArr[2]);
    currDelLink = push(delTestList, delTestArr[3], "Rouse Hill");
    assert(currDelLink->areaCode == delTestArr[3]);
    currDelLink = push(delTestList, delTestArr[4], "Castle Hill");
    assert(currDelLink->areaCode == delTestArr[4]);
    currDelLink = push(delTestList, delTestArr[5], "Kellyville");
    assert(currDelLink->areaCode == delTestArr[5]);
    currDelLink = push(delTestList, delTestArr[6], "Baulkham Hills");
    assert(currDelLink->areaCode == delTestArr[6]);
    currDelLink = push(delTestList, delTestArr[7], "Kellyville");
    assert(currDelLink->areaCode == delTestArr[7]);
    currDelLink = push(delTestList, delTestArr[8], "Kellyville");
    assert(currDelLink->areaCode == delTestArr[8]);
    currDelLink = push(delTestList, delTestArr[9], "Castle Hill");
    assert(currDelLink->areaCode == delTestArr[9]);
    currDelLink = push(delTestList, delTestArr[10], "Kellyville");
    assert(currDelLink->areaCode == delTestArr[10]);
    currDelLink = push(delTestList, delTestArr[11], "Kellyville");
    assert(currDelLink->areaCode == delTestArr[11]);
    
    del(delTestList, delTestArr[0]);
    assert(len(delTestList) == 5);
    del(delTestList, delTestArr[1]);
    assert(len(delTestList) == 4);
    del(delTestList, delTestArr[3]);
    assert(len(delTestList) == 3);
    del(delTestList, delTestArr[6]);
    assert(len(delTestList) == 2);
    
    destroy(delTestList);
    
    printf("All tests were passed.\n");   
}
