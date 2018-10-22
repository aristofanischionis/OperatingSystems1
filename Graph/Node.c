#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../HeaderFiles/Node.h"

//before calling this one be sure there is no other node with the same name in Graph
node *NewNode(char *id){
    node *n = (node *) malloc (sizeof(node)+1);
	n->_id = (char *) malloc(sizeof(id)+1);
	strcpy(n->_id, id);
	n->HeadEdges = NULL; // correct
	return(n);
}

int InsertEdge(edge** head_ref, int w, node *t){ 
	//Append as the last element in the edge linked list
    /* 1. allocate node */
    edge* new_edge = (edge*)malloc(sizeof(edge)); 
	edge* last = *head_ref; /* used in step 5*/
    /* 2. put in the data  */
	new_edge->target = (node*)malloc(sizeof(node));
    new_edge->target = t;
	new_edge->weight = w;
	/* 3. This new node is going to be the last node, so 
          make next of it as NULL*/
    new_edge->next = NULL; 
	/* 4. If the Linked List is empty, then make the new 
          node as head */
    if (*head_ref == NULL) { 
        new_edge->prev = NULL; 
        *head_ref = new_edge; 
        return 0; 
    } 
    /* 5. Else traverse till the last node */
    while (last->next != NULL) last = last->next; 
  
    /* 6. Change the next of last node */
    last->next = new_edge; 
  
    /* 7. Make last node as previous of new node */
    new_edge->prev = last; 
  
    return 0; 
}

// This function prints contents of linked list starting from the given node 
void printList(edge* e){ 
    edge* last; 
    printf("\nTraversal in forward direction \n"); 
    while (e != NULL) { 
        printf(" %d ", e->weight); 
        last = e; 
        e = e->next; 
    } 
  
    printf("\nTraversal in reverse direction \n"); 
    while (last != NULL) { 
        printf(" %d ", last->weight); 
        last = last->prev; 
    } 
} 

edge *DeleteEdge(edge **head_ref, edge *del){ 
  
  /* base case */
  if(*head_ref == NULL || del == NULL) 
    return NULL; 
  
  /* If node to be deleted is head node */
  if(*head_ref == del) 
    *head_ref = del->next; 
  
  /* Change next only if node to be deleted is NOT the last node */
  if(del->next != NULL) 
    del->next->prev = del->prev; 
  
  /* Change prev only if node to be deleted is NOT the first node */
  if(del->prev != NULL) 
    del->prev->next = del->next;      
  
  /* Finally, free the memory occupied by del*/
  free(del); 
  return *head_ref; 
}

int DeleteEdges(node *n){
	// delete all edges oso to del next diaforo tou null
	edge *temp;
	if(n == NULL) return 1;
	temp = (edge *)malloc(sizeof(edge));
	temp = n->HeadEdges;
	while(temp != NULL) {
		temp = DeleteEdge(&temp, temp);
	}
	return 0;
}

edge *SearchEdge(node *s, node *t, int w){
    // if(s->HeadEdges->target == t && s->HeadEdges->weight == w) return s->HeadEdges;
    // When not first edge
    // find the previous edge 
    edge *temp = s->HeadEdges;
    while(temp != NULL){
        if(temp->target == t && temp->weight == w){
            // found
            return temp;
        }
        temp = temp->next;
    }
    return NULL;

    // edge *prev = s->HeadEdges; 
    // while(prev->next != NULL){
	// 	if(prev->next->target != t || prev->next->weight != w) prev = prev->next; 
	// }
	// // Check if edge really exists in DLL
    // if(prev->next == NULL) return NULL; 

    // return prev->next;
}

edge *UpdateEdge(node *s, node *t, int w, int nw){
    edge *e = SearchEdge( s, t, w);
    if(e == NULL){
        // printf("Couldn't find this edge\n");
        return NULL;
    }
    e->weight = nw;
    return e;
}