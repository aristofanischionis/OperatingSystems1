#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "Node.h"
#include "Edge.h"

int ID = 0; // giving ID in Edges

edge *CreateEdge(edge *e)
{	
	e=NULL;
	e->_id = (int) malloc(sizeof(ID)+1);
	e->_id = ID;
	ID ++; 
	return(e);
}

edge *InsertEdge(
	edge *e,
	int _id,
    int weight,
    node *source,
    node *target
	)
{
	if ( e==NULL ) {
		e = (edge *) malloc (sizeof(edge)+1);
		e->weight = (int) malloc(sizeof(weight)+1);
		e->weight = weight;
		e->source = (node *) malloc(sizeof(source)+1);
		e->source = source;
		e->target = (node *) malloc(sizeof(target)+1);
		e->target = target;
		e->next = NULL;
		}
	else 	{
		e->next = InsertEdge(e->next, _id, weight, source, target);
		}
	return(e);
}

edge *DeleteEdge(edge *e, int _id)
{	edge *aux=NULL, *throwaway=NULL;
	aux=e;
	if (aux==NULL) 
		return (NULL);
	else {
		if ( strcmp(aux->_id, _id) == 0 ){
			throwaway=aux;
			aux = aux->next;
			free (throwaway) ;
			throwaway = NULL;
			return(aux);
			}
		else {
			aux->next=DeleteEdge(aux->next, _id);
			return(aux);
		}
	}
}









