#include	<stdio.h>
#include "Node.h"

#define	 	YES	1
#define		NO	2
#define		FALSE	20
#define		TRUE	30
#define		MAXSIZE	64

// linked lists from edges
// typedef struct ListofEdges{
// 	edge *Edge;
// 	int count; // Count how many Edges this Linked List of Edges has got
// 	struct ListofEdges *next;
// }ListofEdges;

// typedef struct ListofEdges ListofEdges;

typedef struct edge {
    int _id;
    int weight;
    node *source;
    node *target;
    struct edge *next;
};

typedef struct edge edge;

edge *CreateEdge(edge *);
edge *InsertEdge(edge *, int , node *source, node *target);
edge *DeleteEdge(edge *, int);
char *GetFirstEdge(edge *);
char *GetLastEdge(edge *);
int	 IsMemberOfList(edge *, char *);
void PrintEdge(edge *);
