/*
**  Testing Source Code
**
**  Basic file containing source code for unit tests correspondng
**  to main program code, 
**  
**  30.05.2017 | Lucas Barbosa | Open Source Software
*/

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

// Testing interface.
#include "test.h"

void runTests(void) {
    
    List testList = create();
    
    /*
    **  Test: Appending Items (Inserting from end)
    */
    
    append(testList, 5);
    append(testList, 10);
    append(testList, 21);
    append(testList, 30);
    append(testList, 50);
    
    assert(testList->head->value == 5);
    assert(testList->head->next->value == 10);
    assert(testList->head->next->next->value == 21);
    assert(testList->head->next->next->next->value == 30);
    assert(testList->head->next->next->next->next->value == 50);
    
    /*
    **  Test: Popping Items (Deleting from top)
    */
    
    pop(testList);
    assert(testList->head->value == 10);
    assert(testList->head->next->value == 21);
    assert(testList->head->next->next->value == 30);
    assert(testList->head->next->next->next->value == 50);
    
    /*
    **  Test: Pusing Items (Inserting from top)
    */
    
    push(testList, 200);
    assert(testList->head->value == 200);
    assert(testList->head->next->value == 10);
    assert(testList->head->next->next->value == 21);
    assert(testList->head->next->next->next->value == 30);
    assert(testList->head->next->next->next->next->value == 50);
    
    /*
    **  Test: Length of List 
    */
    
    assert(len(testList) == 5);
    pop(testList);
    assert(len(testList) == 4);
    pop(testList);
    assert(len(testList) == 3);
    pop(testList);
    assert(len(testList) == 2);
    pop(testList);
    assert(len(testList) == 1);
    
    destroy(testList);
    
    /*
    **  Test: Pez Dispenser (Removing and Returning top node)
    */
    
    List testList2 = create();
    append(testList2, 56);
    append(testList2, 450);
    append(testList2, 12);
    append(testList2, 46);
    append(testList2, 109);
    append(testList2, 54);
    append(testList2, 86);
    
    Link topNode = pez(testList2);
    assert(len(testList2) == 6);
    assert(topNode->value == 56);
    topNode = pez(testList2);
    assert(len(testList2) == 5);
    assert(topNode->value == 450);
    topNode = pez(testList2);
    assert(len(testList2) == 4);
    assert(topNode->value == 12);
    topNode = pez(testList2);
    assert(len(testList2) == 3);
    assert(topNode->value == 46);
    topNode = pez(testList2);
    assert(len(testList2) == 2);
    assert(topNode->value == 109);
    topNode = pez(testList2);
    assert(len(testList2) == 1);
    assert(topNode->value == 54);
    topNode = pez(testList2);
    assert(len(testList2) == 0);
    assert(topNode->value == 86);
    
    
    printf("All tests passed.\n");
    
}
