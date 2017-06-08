/*
**  Multi-Lists
**  
**  Once the normal linked-lists are understood, bi-directional 
**  linked-lists are the best viable option for GPS mapping. 
**  We’ll dwell more into it and actually develop a mapping system. 
**  Linked lists make it easier to change the order of things much 
**  easier, also running through a list seems a little more 
**  intuitively pure then processing an array through a loop.
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
    
    //runTests();
    List australia = createList();
    push(australia, 2155, "Kellyville");
    push(australia, 3166, "Rouse Hill");
    push(australia, 2154, "Castle Hill");
    push(australia, 2174, "Baulkham Hills");
    push(australia, 1323, "Strathfiled");
    push(australia, 3563, "Redfern");
    printls(australia, TRUE);
    printf("\n");
    printls(australia, FALSE);
    Link currNode1 = get(australia, 5);
    printf("%s\n", currNode1->addr);
    
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
    return currNode;
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
    int counter = 0;
    Link currNode = list->head;
    Link indexedNode;
    while (currNode->next != NULL) {
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
    
}

void printls(List list, int printAddress) {
    assert(list != NULL);
    
    if (printAddress == TRUE) {
        Link currNode = list->head;
        printf("(X)<->");
        while (currNode != NULL) {
            printf("[%s]<->", currNode->addr);
            currNode = currNode->next;
        }
        printf("{X}\n");
    } else {
        Link currNode = list->head;
        printf("(X)<->");
        while (currNode != NULL) {
            printf("[%d]<->", currNode->areaCode);
            currNode = currNode->next;
        }
        printf("{X}\n");
    }
    
    
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