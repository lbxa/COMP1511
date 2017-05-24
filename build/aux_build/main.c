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

#define TRUE 1
#define FALSE 0

typedef struct _node * Link;
typedef struct _list * List;

struct _list {
    Link head;
};

typedef struct _node {
    int value;
    Link next;
} Node;

List createLX() {
    List newList = malloc(sizeof(struct _list));
    assert(newList != NULL);
    newList->head = NULL;
    return newList;
}

Link newNodeLX() {
    Link newLink = malloc(sizeof(struct _node));
    return newLink;
}

//Link appendLX(int value) {
    
//}

int main (void) {
    
    createLX();
    
    return EXIT_SUCCESS;
}
