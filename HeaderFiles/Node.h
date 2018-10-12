#include <stdio.h>
#include "LinkedList.h"

struct node {
    char *_id;
    item *HeadEdges; // head of the linked list of edges
    struct node *next; // connect list of nodes
};
typedef struct node node;
