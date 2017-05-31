/*
 *  Linked Lists Practice
 *  
 *  General purpose functions which interact with linked lists.
 *
 *  24.05.2017 | Lucas Barbosa | HS1917
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Testing interface
#include "test.h"

#define TRUE 1
#define FALSE 0

/*
**  Linked Lists - Prototyping Auxilary Functions
**  30.05.2017 | Lucas Barbosa | Open Source Software
*/

int main (void) {
    
    runTests();
    
    List linkedList = create();
    push(linkedList, 5);
    printls(linkedList);
    append(linkedList, 10);
    printls(linkedList);
    push(linkedList, 55);
    printls(linkedList);
    pez(linkedList);
    printls(linkedList);
    
    return EXIT_SUCCESS;
}

List create() {
    List newList = malloc(sizeof(struct _list));
    assert(newList != NULL);
    newList->head = NULL;
    return newList;
}

Link createNode() {
    return malloc(sizeof(struct _node));
}

Link append(List list, int value) {
    assert(list != NULL);
    Link newNode = createNode();
    newNode->value = value;
    newNode->next  = NULL;
    Link currNode = list->head;
    
    if (currNode == NULL) {
       list->head = newNode;
    } else {
        currNode = list->head;
        while (currNode->next != NULL) {
            currNode = currNode->next;
        }
        currNode->next = newNode;
    }
    return currNode;
}

Link pez(List list) {
    assert(list != NULL);
    Link topNode = list->head;
    list->head = list->head->next;
    return topNode;
}

int len(List list) {
    assert(list != NULL);
    Link currNode = list->head;
    int index = 0;
    while (currNode != NULL) {
        index++;
        currNode = currNode->next;
    }
    return index;
}

void destroy(List list) {
    assert(list != NULL);
    Link currNode = list->head;
    Link prevNode = NULL;
    while (currNode != NULL) {
        prevNode = currNode;
        currNode = prevNode->next;
        free(prevNode);
    }
}

void printls(List list) {
    assert(list != NULL);
    Link currNode = list->head;
    while (currNode != NULL) {
        printf("[%d]->", currNode->value);
        currNode = currNode->next;
    }
    printf("X\n");
}

void pop(List list) {
    assert(list != NULL);
    list->head = list->head->next;
}

void push(List list, int value) {
    assert(list != NULL);
    Link newNode = createNode();
    newNode->value = value;
    newNode->next = list->head;
    list->head = newNode; 
}