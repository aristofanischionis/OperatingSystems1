#include	<stdio.h>
#include "Edge.h"

#define	 	YES	1
#define		NO	2
#define		FALSE	20
#define		TRUE	30
#define		MAXSIZE	64

// linked lists from edges
struct item{
	edge *MyEdge;
	struct item *next;
	};

typedef struct item item;

item *CreateItem(item *);
item *InsertItem(item *, char *);
item *DeleteItem(item *, char *);
char *GetFirstItem(item *);
char *GetLastItem(item *);
int	 IsMemberOfList(item *, char *);
void PrintItem(item *);
