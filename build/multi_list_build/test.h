#ifndef TEST_C_INCLUDED
#define TEST_C_INCLUDED

/*
**  Testing Header Interface | DO NOT ALTER THIS FILE!!!
**
**  Basic file for linking tess source code with main program
**  executable code. 
**  
**  30.05.2017 | Lucas Barbosa | HS1917 | Open Source Software (C)
*/

#define TRUE 1
#define FALSE 0
#define UNKNOWN_NODE 0 

typedef struct _node * Link;
typedef struct _list * List;

struct _list {
    Link head;
};

typedef struct _node {
    int areaCode;
    char *addr;
    Link next;
    Link prev;
} *Node;

/*
**  Linked Lists: Auxilary Functions
*/

List createList();
Link createNode();
Link push(List list, int paramCode, char *address);
Link pez(List list);
Link get(List list, int index);

int len(List list);


void destroy(List list);
void printls(List list, int printAddress);
void pop(List list);
void append(List list, int paramCode, char *address);

/*
**  Prac Tests: Linked Lists Problems
*/

int  median(List list);

void runTests(void);

#endif // TEST_C_INCLUDED