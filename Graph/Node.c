#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../HeaderFiles/Node.h"

//before calling this one be sure there is no other node with the same name in Graph
node *NewNode(char *id){
    node *n = (node *) malloc (sizeof(node)+1);
	n->_id = (char *) malloc(40 * sizeof(char)+1);
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
	// new_edge->target = (node*)malloc(sizeof(node));
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

int DeleteEdges(edge** head_ref){
    // Delete all edges
    edge* ptr = *head_ref; 
    edge* next; 
  
    while (ptr != NULL) { 
        next = ptr->next;
        DeleteEdge(head_ref, ptr); 
        ptr = next; 
    }
    return 0;
} 

edge *SearchEdge(node *s, node *t, int w){
    edge *temp = s->HeadEdges;
    while(temp != NULL){
        if(temp->target == t && temp->weight == w){
            // found
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

edge *SearchEdgeNoWeight(node *s, node *t){
    if(s == NULL) return NULL;
    if(t == NULL) return NULL;
    edge *temp = s->HeadEdges;
    while(temp != NULL){
        if(temp->target == t){
            // found
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

int DeleteEdgesFrom(node *n1, node *n2){
    edge * temp;
    temp = SearchEdgeNoWeight(n1, n2);
    while(temp != NULL){
        // search for more edges from n1 -> n2
        DeleteEdge(&(n1->HeadEdges), temp);
        temp = SearchEdgeNoWeight(n1, n2);
    }
    return 0;
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