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
    **  Test: Appending Items (Inserting from end)
    */
    
    List appendList = createList();
    append(appendList, 5);
    append(appendList, 10);
    append(appendList, 21);
    append(appendList, 30);
    append(appendList, 50);
    
    assert(appendList->head->value == 5);
    assert(appendList->head->next->value == 10);
    assert(appendList->head->next->next->value == 21);
    assert(appendList->head->next->next->next->value == 30);
    assert(appendList->head->next->next->next->next->value == 50);
    
    destroy(appendList);
    
    /*
    **  Test: Popping Items (Deleting from top)
    */
    
    List popList = createList();
    append(popList, 10);
    append(popList, 21);
    append(popList, 30);
    append(popList, 50);
    append(popList, 75);
    append(popList, 100);
    append(popList, 1200);
    
    pop(popList);
    assert(popList->head->value == 21);
    assert(popList->head->next->value == 30);
    assert(popList->head->next->next->value == 50);
    assert(popList->head->next->next->next->value == 75);
    assert(popList->head->next->next->next->next->value == 100);
    assert(popList->head->next->next->next->next->next->value == 1200);
    pop(popList);
    assert(popList->head->value == 30);
    assert(popList->head->next->value == 50);
    assert(popList->head->next->next->value == 75);
    assert(popList->head->next->next->next->value == 100);
    assert(popList->head->next->next->next->next->value == 1200);
    pop(popList);
    assert(popList->head->value == 50);
    assert(popList->head->next->value == 75);
    assert(popList->head->next->next->value == 100);
    assert(popList->head->next->next->next->value == 1200);
    pop(popList);
    assert(popList->head->value == 75);
    assert(popList->head->next->value == 100);
    assert(popList->head->next->next->value == 1200);
    pop(popList);
    assert(popList->head->value == 100);
    assert(popList->head->next->value == 1200);
    pop(popList);
    assert(popList->head->value == 1200);
    
    destroy(popList);
    
    /*
    **  Test: Pusing Items (Inserting from top)
    */
  
    List pushList = createList();
    append(pushList, 10);
    append(pushList, 60);
    append(pushList, 50);
    append(pushList, 4350);
    append(pushList, 34);
    append(pushList, 234);
    append(pushList, 46);

    push(pushList, 200);
    assert(pushList->head->value == 200);
    assert(pushList->head->next->value == 10);
    assert(pushList->head->next->next->value == 60);
    assert(pushList->head->next->next->next->value == 50);
    assert(pushList->head->next->next->next->next->value == 4350);
    assert(pushList->head->next->next->next->next->next->value == 34);
    assert(pushList->head->next->next->next->next->next->next->value == 234);
    assert(pushList->head->next->next->next->next->next->next->next->value == 46);
    push(pushList, 10);
    assert(pushList->head->value == 10);
    assert(pushList->head->next->value == 200);
    assert(pushList->head->next->next->value == 10);
    assert(pushList->head->next->next->next->value == 60);
    assert(pushList->head->next->next->next->next->value == 50);
    assert(pushList->head->next->next->next->next->next->value == 4350);
    assert(pushList->head->next->next->next->next->next->next->value == 34);
    assert(pushList->head->next->next->next->next->next->next->next->value == 234);
    assert(pushList->head->next->next->next->next->next->next->next->next->value == 46);

    destroy(pushList);
 
    /*
    **  Test: Length of List 
    */
  
    List lenList = createList();
    append(lenList, 10);
    append(lenList, 60);
    append(lenList, 50);
    append(lenList, 34);
    append(lenList, 34);
    append(lenList, 234);
    append(lenList, 46);
    append(lenList, 42);
    append(lenList, 44546);
    
    assert(len(lenList) == 9);
    pop(lenList);
    assert(len(lenList) == 8);
    pop(lenList);
    assert(len(lenList) == 7);
    pop(lenList);
    assert(len(lenList) == 6);
    pop(lenList);
    assert(len(lenList) == 5);
    pop(lenList);
    assert(len(lenList) == 4);
    pop(lenList);
    assert(len(lenList) == 3);
    pop(lenList);
    assert(len(lenList) == 2);
    pop(lenList);
    assert(len(lenList) == 1);
    pop(lenList);
    assert(len(lenList) == 0);

    destroy(lenList);
    
    /*
    **  Test: Pez Dispenser (Removing and Returning top node)
    */
    
    List pezList = createList();
    append(pezList, 56);
    append(pezList, 450);
    append(pezList, 12);
    append(pezList, 46);
    append(pezList, 109);
    append(pezList, 54);
    append(pezList, 86);
    append(pezList, 120);
    append(pezList, 456);
    
    Link topNode = UNKNOWN_NODE;
    topNode = pez(pezList); 
    assert(len(pezList) == 8);
    assert(topNode->value == 56);
    topNode = pez(pezList);
    assert(len(pezList) == 7);
    assert(topNode->value == 450);
    topNode = pez(pezList);
    assert(len(pezList) == 6);
    assert(topNode->value == 12);
    topNode = pez(pezList);
    assert(len(pezList) == 5);
    assert(topNode->value == 46);
    topNode = pez(pezList);
    assert(len(pezList) == 4);
    assert(topNode->value == 109);
    topNode = pez(pezList);
    assert(len(pezList) == 3);
    assert(topNode->value == 54);
    topNode = pez(pezList);
    assert(len(pezList) == 2);
    assert(topNode->value == 86);
    topNode = pez(pezList);
    assert(len(pezList) == 1);
    assert(topNode->value == 120);
    topNode = pez(pezList);
    assert(len(pezList) == 0);
    assert(topNode->value == 456);
    
    destroy(pezList);
    
    /*
    **  Test: Getter (Retrieving values from indexes in list)
    */
    
    List getList = createList();
    append(getList, 56);
    append(getList, 45);
    append(getList, 124);
    append(getList, 43);
    append(getList, 19);
    append(getList, 74);
    append(getList, 95);
    
    int index = 0;
    index = get(getList, 0);
    assert(index == 56);
    index = get(getList, 1);
    assert(index == 45);
    index = get(getList, 2);
    assert(index == 124);
    index = get(getList, 3);
    assert(index == 43);
    index = get(getList, 4);
    assert(index == 19);
    index = get(getList, 5);
    assert(index == 74);
    index = get(getList, 6);
    assert(index == 95);
    
    destroy(getList);
    
    /*
    **  Test: Median (First prac test)
    */
    
    List medianList = createList();
    append(medianList, 45);
    append(medianList, 56);
    append(medianList, 56);
    append(medianList, 10);
    append(medianList, 56);
    append(medianList, 40);
    assert(median(medianList) == 33);
    pop(medianList);
    assert(median(medianList) == 10);
    pop(medianList);
    assert(median(medianList) == 33);
    pop(medianList);
    pop(medianList);
    pop(medianList);
    assert(median(medianList) == 40);
    
    destroy(medianList);
    
    printf("All tests passed.\n");
    
}
