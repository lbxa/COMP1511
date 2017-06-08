/*
**  Multi-Lists
**  
**  Once the normal linked-lists are understood, bi-directional 
**  linked-lists are the best viable option for GPS mapping. 
**  We’ll dwell more into it and actually develop a mapping system. 
**  Linked lists make it easier to change the order of things much 
**  easier, also running through a list seems a little more 
**  intuitively pure then processing an array through a loop. *This
**  code is being written through a prototype approach, as a working
**  crapy solution is currently more important than correctly 
**  documented code. 
**
**  24.05.2017 | Lucas Barbosa | HS1917 | Open Source Software (C)
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Testing interface
#include "test.h"

#define INDEX_AT_0 1

/*
**  Multi-Lists ~ Prototyping Auxilary Functions
**  30.05.2017 | Lucas Barbosa | Open Source Software
*/

int main (void) {
    
    runTests();
    
    return EXIT_SUCCESS;
}

List createList() {
    List newList = malloc(sizeof(struct _list));
    assert(newList != NULL);
    newList->head = NULL;
    return newList;
}

Link createNode() {
    return malloc(sizeof(struct _node));
}

Link push(List list, int paramCode, char *address) {
    assert(list != NULL);
    Link newNode = createNode();
    newNode->areaCode = paramCode;
    newNode->addr     = address;
    newNode->next     = NULL;
    Link currNode = list->head;
    if (currNode == NULL) {
       list->head       = newNode;
       list->head->prev = NULL;
    } else {
        currNode = list->head;
        while (currNode->next != NULL) {
            currNode = currNode->next;
        }
        newNode->prev  = currNode;
        currNode->next = newNode;
    }
    return newNode;
}

Link pez(List list) {
    assert(list != NULL);
    Link savedNode = list->head;
    list->head = list->head->next;
    list->head->prev = NULL;
    return savedNode;
}

int len(List list) {
    assert(list != NULL);
    int counter = 0;
    Link currNode = list->head;
    while (currNode != NULL) {
        currNode = currNode->next;
        counter++;
    }
    return counter;
}

Link get(List list, int index) {
    assert(list != NULL);
    assert(index < len(list));
    int counter = 0;
    Link indexedNode;
    Link currNode = list->head;
    while (currNode != NULL) {
        if (counter == index) {
            indexedNode = currNode;
        }
        currNode = currNode->next;
        counter++;
    }
    return indexedNode;
}

int median(List list) {
    assert(list != NULL);

    return 1;
}

void del(List list, int valToDelete) {
    assert(list != NULL);
    
}

void destroy(List list) {
    assert(list != NULL);
    Link currNode = list->head;
    Link tmpBin;
    while (currNode != NULL) {
        tmpBin = currNode;
        currNode = currNode->next;
        free(tmpBin);
    }
}

void printls(List list, int printAddress) {
    assert(list != NULL);
    printf("(X)<->");
    Link currNode = list->head;
    if (printAddress == TRUE) {
        while (currNode != NULL) {
            printf("[%s]<->", currNode->addr);
            currNode = currNode->next;
        }
    } else {
        while (currNode != NULL) {
            printf("[%d]<->", currNode->areaCode);
            currNode = currNode->next;
        }
    }
    printf("{X}\n");
}

void pop(List list) {
    assert(list != NULL);
    list->head = list->head->next;
    list->head->prev = NULL;
}

void append(List list, int paramCode, char *address){
    assert(list != NULL);
    Link newNode = createNode();
    newNode->areaCode = paramCode;
    newNode->addr     = address;
    newNode->prev     = NULL;
    newNode->next     = NULL;
    Link currNode = list->head;
    if (currNode == NULL) {
       list->head = newNode;
    } else {
        currNode = list->head;
        while (currNode->next != NULL) {
            currNode = currNode->next;
        }
        currNode->next = newNode;
        newNode->prev  = currNode;
    }
}

void cut(List list, int n) {
    assert(list != NULL);
    
}