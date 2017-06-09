/*
 *  Linked Lists Practice
 *  
 *  General purpose functions which interact with linked lists.
 *
 *  24.05.2017 | Lucas Barbosa | HS1917 | Open Source Software (C)
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Testing interface
#include "test.h"

#define INDEX_AT_0 1

/*
**  Linked Lists - Prototyping Auxilary Functions
**  30.05.2017 | Lucas Barbosa | Open Source Software
*/

int main (void) {
    
    runTests();
    
    List linkedList = createList();
    append(linkedList, 'B');
    append(linkedList, 'A');
    append(linkedList, 'B');
    append(linkedList, 'B');
    append(linkedList, 'B');
    append(linkedList, 'B');
    append(linkedList, 'B');
    append(linkedList, 'A');
    append(linkedList, 'B');
    append(linkedList, 'B');
    append(linkedList, 'B');
    append(linkedList, 'B');
    append(linkedList, 'B');
    append(linkedList, 'B');
    append(linkedList, 'A');
    append(linkedList, 'B');
    append(linkedList, 'B');  // <----- seg-fault here (test with GDB)
    printls(linkedList);
    del(linkedList, 'B');
    printls(linkedList);
    
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
    int index = UNKNOWN_NODE;
    while (currNode != NULL) {
        index++;
        currNode = currNode->next;
    }
    return index;
}

int get(List list, int index) {
    assert(list != NULL);
    Link currNode = list->head;
    int listLen   = len(list);
    // exit is the index is invalid
    assert(index < listLen);
    
    int counter = 0;
    while (counter < index) {
        currNode = currNode->next;
        counter++;
    }
    return currNode->value;
}

int median(List list) {
    assert(list != NULL);
    // Assuming its ordered
    int index = UNKNOWN_NODE;
    int median;
    int listLen = len(list);
    int isEven = (listLen % 2 == 0);
    if (isEven) {
        // median = (len / 2) + (len + 1 / 2) / 2
        index  = len(list) / 2;
        median = get(list, index - INDEX_AT_0);
        median += get(list, index);
        median /= 2;
    } else {
        //median is (len + 1) /2
        index  = (len(list) + 1) / 2;
        median = get(list, index - INDEX_AT_0);
    }
    
    if (list->head->next == NULL) {
        median = list->head->value;
    }

    return median;
}

void del(List list, int valToDelete) {
    assert(list != NULL);
    Link currNode = list->head;
   // Link lastNode = UNKNOWN_NODE;
    
    if ((currNode->next == NULL) && (currNode->value == valToDelete)) {
        list->head = NULL;
    }
    // if list starts with value to be deleted and is longer then one
    if ((currNode->next != NULL) && (currNode->value == valToDelete)) {
        pop(list);
        printf("pop!\n");
    }
    
    while (currNode->next->next != NULL) {
        
        while (currNode->value == valToDelete) {
            currNode->next = currNode->next->next;
        }
        currNode = currNode->next;
    }
    
    if (currNode->next->value == valToDelete) {
        printf("We are good\n");
        currNode->next = NULL;
    }
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
    if (list->head->next == NULL) {
        list->head = NULL;
    } else {
        list->head = list->head->next;
    }
}

void push(List list, int value) {
    assert(list != NULL);
    Link newNode = createNode();
    newNode->value = value;
    newNode->next = list->head;
    list->head = newNode; 
}

void removeUpperCase(List list) {
    assert(list != NULL);
}
<<<<<<< HEAD

void cut(List list, int n) {
    assert(list != NULL);
    int counter = 0;
    Link currNode;
    
    if (list->head->next == NULL) {
        // cut nothing
    } else {
        while (counter < n) {
            currNode = list->head;
            while (currNode->next != NULL) {
                currNode = currNode->next;
            }
            currNode->next = list->head;
            list->head->next = NULL;
            
            counter++;
        }
    }
}
=======
>>>>>>> e0b4831593eacd05c2aa6db6b280b24164d10f1a
