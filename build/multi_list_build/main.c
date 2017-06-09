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

/*
**  Multi-Lists ~ Prototyping Auxilary Functions
**  30.05.2017 | Lucas Barbosa | Open Source Software
*/

int main (void) {
    printf("\n"); /* | */ runTests(); /* | */ printf("\n");
    
    
    List listA = newList();
    push(listA, 2155, "Kellyville");
    
    List listB = newList();
    push(listB, 2154, "Castle Hill");
    
    List listC = newList();
    push(listC, 2153, "Rouse Hill");
    
    List listD = newList();
    
    join3(listA, listB, listC, listD);
    
    printls(listD, ADDR_CODE);
    
    return EXIT_SUCCESS;
}

List newList() {
    List newList = malloc(sizeof(struct _list));
    assert(newList != NULL);
    newList->head = NULL;
    return newList;
}

Link newNode() {
    return malloc(sizeof(struct _node));
}

Link push(List list, int paramCode, char *address) {
    assert(list != NULL);
    Link anointedNode = newNode();
    anointedNode->areaCode = paramCode;
    anointedNode->addr     = address;
    anointedNode->next     = NULL;
    Link currNode = list->head;
    if (currNode == NULL) {
       list->head       = anointedNode;
       list->head->prev = NULL;
    } else {
        currNode = list->head;
        while (currNode->next != NULL) {
            currNode = currNode->next;
        }
        anointedNode->prev  = currNode;
        currNode->next      = anointedNode;
    }
    return anointedNode;
}

Link pez(List list) {
    assert(list != NULL);
    assert(len(list) > 1);
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

Link median(List list) {
    assert(list != NULL);
    int index = 0;
    Link median;
    int listLen = len(list);
    if (listLen % 2 == EVEN) {
        index = listLen / 2;
        index -= INDEX_AT_ZERO;
        median = get(list, index);
    } else {
        index = (listLen + 1) / 2;
        index -= INDEX_AT_ZERO;
        median = get(list, index);
    }
    return median;
}

void del(List list, int areaCodetoDelete) {
    assert(list != NULL);
    assert(len(list) >= 1);
    Link linkBin;
    if ((list->head->next == NULL) && (list->head->areaCode == areaCodetoDelete)) {
        list->head = NULL;
    } else {
        Link currNode = list->head;
        while (currNode->next != NULL) {
            if ((currNode->prev == NULL) && (currNode->areaCode == areaCodetoDelete)) {
                // edge case: 1st item
                pop(list);
            } else if (currNode->areaCode == areaCodetoDelete) {
                linkBin = currNode;
                currNode->prev->next = currNode->next;     // operations include previous node
                currNode->next->prev = currNode->prev;
                free(linkBin);
            }
            currNode = currNode->next;
        }
        if ((currNode->next == NULL) && (currNode->areaCode == areaCodetoDelete)) {
            // edge case: last item
            currNode->prev->next = NULL;
            currNode->prev = NULL;
        }
    }
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
    if (printAddress == ADDR_CODE) {
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
    assert(len(list) > 1);
    list->head = list->head->next;
    list->head->prev = NULL;
}

void append(List list, int paramCode, char *address){
    assert(list != NULL);
    Link anointedNode = newNode();
    anointedNode->areaCode = paramCode;
    anointedNode->addr     = address;
    anointedNode->prev     = NULL;
    anointedNode->next     = NULL;
    Link currNode = list->head;
    if (currNode == NULL) {
       list->head = anointedNode;
    } else {
        currNode = list->head;
        while (currNode->next != NULL) {
            currNode = currNode->next;
        }
        currNode->next      = anointedNode;
        anointedNode->prev  = currNode;
    }
}

void join(List listA, List listB, List joinedList) {
    assert((listA != NULL) && (listB != NULL) && (joinedList != NULL));
    assert(joinedList->head == NULL);
    joinedList->head = listA->head;
    listA->head = NULL;  
    Link currNode = joinedList->head;
    while(currNode->next != NULL) {
        currNode = currNode->next;
    }
    currNode->next = listB->head;
    listB->head->prev = currNode;
}

void join3(List listA, List listB, List listC, List joinedList) {
    assert((listA != NULL) && (listB != NULL) && (listC != NULL));
    assert(joinedList->head == NULL);
    joinedList->head = listA->head;
    listA->head = NULL;  
    Link currNode = joinedList->head;
    while(currNode->next != NULL) {
        currNode = currNode->next;
    }
    currNode->next = listB->head;
    listB->head->prev = currNode;
    currNode = joinedList->head;
    while(currNode->next != NULL) {
        currNode = currNode->next;
    }
    currNode->next = listC->head;
    listC->head->prev = currNode;
}

void cut(List list, int n) {
    assert(list != NULL);
    // Write driver ...
}