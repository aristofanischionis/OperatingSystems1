#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../HeaderFiles/Node.h"
int ID = 0; // giving ID in Edges

//before calling this one be sure there is no other node with the same name in Graph
node *NewNode(char *id, edge *e){
    node *n = (node *) malloc (sizeof(node)+1);
    // printf("NEWNODE!!");
	n->_id = (char *) malloc(sizeof(id)+1);
	n->_id = id;
	n->HeadEdges = (edge *) malloc (sizeof(e)+1);
    n->HeadEdges = e;
	return(n);
}

edge *InsertEdge(node *source, node *target, edge *e, int weight){
    if(source == NULL) return (NULL);
    if(target == NULL) return (NULL);
    if ( e==NULL ) {
		e = (edge *) malloc (sizeof(edge)+1);
		e->_id = ID;
		e->weight = weight;
		e->target = target;
        if(e->_id == 0) {source->HeadEdges = e;} // la8os pote kanw 0 to id
		e->next = NULL;
        printf("INSERT EDGE!! %d", e->_id);
		}
	else {
		ID ++;
		e->next = InsertEdge(source, target, e->next, weight );
		}
	return(e);
}

edge *DeleteEdge(edge *e, int _id)
{	edge *aux=NULL, *throwaway=NULL;
	aux=e;
	if (aux==NULL) 
		return (NULL);
	else {
		if ( aux->_id == _id ){
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
		return(-1);
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
		return(-1);
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
			return(2);
		aux=aux->next;
		}
	return(1);
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
		printf("Element weight is %d\n",aux->weight);
		printf("Element target's name is %s\n",aux->target->_id);
		aux=aux->next;
	}
}
