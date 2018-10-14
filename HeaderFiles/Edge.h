#include <stdio.h>
#include "Node.h"

typedef struct edge {
    int _id;
    int weight;
    node *source;
    node *target;
    struct edge *next;
};

typedef struct edge edge;
