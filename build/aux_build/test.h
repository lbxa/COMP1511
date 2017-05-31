#ifndef TEST_C_INCLUDED
#define TEST_C_INCLUDED

/*
**  Testing Header Interface | DO NOT ALTER THIS FILE!!!
**
**  Basic file for linking tess source code with main program
**  executable code. 
**  
**  30.05.2017 | Lucas Barbosa | Open Source Software
*/

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

List create();
Link createNode();
Link append(List list, int value);
Link pez(List list);
int  len(List list);
void destroy(List list);
void printls(List list);
void pop(List list);
void push(List list, int value);

void runTests(void);

#endif // TEST_C_INCLUDED