#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../HeaderFiles/Node.h"
int counter = 0;
//before calling this one be sure there is no other node with the same name in Graph
node *NewNode(char *id){
    node *n = (node *) malloc (sizeof(node)+1);
    // printf("NEWNODE!!");
	n->_id = (char *) malloc(sizeof(id)+1);
	n->_id = id;
	n->HeadEdges = NULL;
	return(n);
}

edge *InsertEdge(node *source, node *target, edge *e, int weight){
    if(source == NULL) return (NULL);
    if(target == NULL) return (NULL);
	// if(source->HeadEdges == NULL) source->HeadEdges = e;
    if ( e==NULL ) {
		e = (edge *) malloc (sizeof(edge)+1);
		e->weight = weight;
		e->target = (node *) malloc (sizeof(node)+1);
		e->target = target;
		e->next = NULL;
		if(counter == 0){
			source->HeadEdges = e;
			counter++;
        	printf("INSERT head EDGE!!");
		}
		}
	else {
		e->next = InsertEdge(source, target, e->next, weight );
		}
	return(e);
}

int DeleteEdge(node *s, node *t, int w)
{	
	// When edge to be deleted is s->HeadEdges edge 
	edge *temp;

    if(s->HeadEdges->target == t && s->HeadEdges->weight == w) 
    { 
        if(s->HeadEdges->next == NULL) 
        {
            free(s->HeadEdges);
            return 0;
        }

        /* Copy the data of next edge to s->HeadEdges */
        s->HeadEdges->weight = s->HeadEdges->next->weight; 
		s->HeadEdges->target = s->HeadEdges->next->target;
        // store address of next edge 
        temp = s->HeadEdges->next; 
        
        // Remove the link of next edge 
        s->HeadEdges->next = s->HeadEdges->next->next; 
  
        // free memory 
        free(temp); 
  
        return 0; 
    }
    // When not first edge, follow the normal deletion process 
  
    // find the previous edge 
    edge *prev = s->HeadEdges; 
    while(prev->next != NULL && prev->next->target != t && prev->next->weight == w) 
        prev = prev->next; 
  
    // Check if edge really exists in Linked List 
    if(prev->next == NULL) 
    { 
        printf("\n Given edge is not present in Linked List"); 
        return 1; 
    } 
	temp = prev->next;
    // Remove edge from Linked List 
    prev->next = prev->next->next; 
  
    // Free memory 
    free(temp); 
  
    return 0;
}


// int GetFirstEdge(edge *e)
// {	edge *aux=NULL;
// 	int id;

// 	aux=e;
// 	if (aux==NULL)
// 		return(-1);
// 	else	{
// 		// id = (int)malloc(sizeof(aux->_id)+1);	
// 		id = aux->_id;
// 		printf("first id is %d \n",id);
// 		return(id);
// 		}
// }
	
// int GetLastEdge(edge *e)
// {	edge *aux=NULL;
// 	int id;
	
// 	aux=e;
// 	if (aux==NULL)
// 		return(-1);
// 	else{
// 		while (aux->next!=NULL)
// 			aux=aux->next;
// 			id = aux->_id;
// 			printf("last id is %d \n",id);
//             return(id);
//         }            
// }

// int	IsMemberOfList(edge *e, int id)
// {	edge *aux=NULL;
// 	aux = e;
// 	while (aux!=NULL){
// 		if ( aux->_id == id )
// 			return(2);
// 		aux=aux->next;
// 		}
// 	return(1);
// }

// void PrintEdge(edge *e)
// { 
// 	edge *aux=NULL;
	
// 	if ( e == NULL ){
// 		printf("List is Empty of Edges\n");
// 		return;
// 	}
// 	aux = e;
// 	while (aux!= NULL){
// 		printf("Element id is %d\n",aux->_id);
// 		printf("Element weight is %d\n",aux->weight);
// 		printf("Element target's name is %s\n",aux->target->_id);
// 		aux=aux->next;
// 	}
// }
