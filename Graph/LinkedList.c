#include	<stdio.h>
#include	"LinkedList.h"
#include "Node.h"

int ID; // giving ID in Edges

edge *CreateEdge(edge *e)
{	
	e=NULL;
	e->_id = (int) malloc(sizeof(ID)+1);
	e->_id = ID;
	ID = 0; // first edge
	return(e);
}

edge *InsertEdge(
	edge *e,
    int weight,
    node *source,
    node *target
	)
{
	if ( e==NULL ) {
		e = (edge *) malloc (sizeof(edge)+1);
		e->_id = (int) malloc(sizeof(ID)+1);
		e->_id = ID;
		e->weight = (int) malloc(sizeof(weight)+1);
		e->weight = weight;
		e->source = (node *) malloc(sizeof(source)+1);
		e->source = source;
		e->target = (node *) malloc(sizeof(target)+1);
		e->target = target;
		e->next = NULL;
		}
	else 	{
		ID ++;
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
			ID --;
			return(aux);
			}
		else {
			aux->next=DeleteEdge(aux->next, _id);
			return(aux);
		}
	}
}


int GetFirstEdge(edge *e)
{	edge *aux=NULL;
	int id;

	aux=e;
	if (aux==NULL)
		return(NULL);
	else	{
		// id = (int)malloc(sizeof(aux->_id)+1);	
		id = aux->_id;
		printf("first id is %d \n",id);
		return(id);
		}
}
	
int GetLastEdge(edge *e)
{	edge *aux=NULL;
	int id;
	
	aux=e;
	if (aux==NULL)
		return(NULL);
	else{
		while (aux->next!=NULL)
			aux=aux->next;
			id = aux->_id;
			printf("last id is %d \n",id);
            return(id);
        }            
}

int	IsMemberOfList(edge *e, int id)
{	edge *aux=NULL;
	aux = e;
	while (aux!=NULL){
		if ( aux->_id == id )
			return(YES);
		aux=aux->next;
		}
	return(NO);
}

void PrintEdge(edge *e)
{ 
	edge *aux=NULL;
	
	if ( e == NULL ){
		printf("List is Empty of Edges\n");
		return;
	}
	aux = e;
	while (aux!= NULL){
		printf("Element id is %d\n",aux->_id);
		aux=aux->next;
	}
}
