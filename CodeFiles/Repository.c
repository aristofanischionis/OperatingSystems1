#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../HeaderFiles/HashTable.h"

int InsertNode(ht_hash_table* ht, char* _id){
    //this function calls backend functions to insert a new Node to the Hash Table
    //search if there is another node named _id
    char *pos;
    node *n = ht_search(ht, _id);
    if(n != NULL){
        // node with _id found
        if ((pos=strchr(n->_id, '\n')) != NULL) *pos = '\0';
        printf("\t- Node |%s| Exists;", n->_id);
        return 1;
    }
    ht_insert(ht,_id);
    if ((pos=strchr(_id, '\n')) != NULL) *pos = '\0';
    printf("\t- Inserted |%s|",_id);
    return 0;
}

int InsertNodesEdge(ht_hash_table* ht, char* _id1, char *_id2, int w){
    //this function inserts a new edge if the _id1 and 2 exist else it creates them first
    char *pos;
    InsertNode(ht, _id1);
    InsertNode(ht, _id2);
    printf("-----------------%d",ht->count);
    // now that we have both nodes ready let's make the edge
    node *n1 = ht_search(ht, _id1);
    node *n2 = ht_search(ht, _id2);
    edge * e= InsertEdge(n1, n2, n1->HeadEdges, w); // put it in the n1's linked List
    if(e == NULL) printf("ajajaajajajaja");
    printf("----weight%d", n1->HeadEdges->weight);
    if ((pos=strchr(n1->_id, '\n')) != NULL) *pos = '\0';
    if ((pos=strchr(n2->_id, '\n')) != NULL) *pos = '\0';
    printf("\t- Inserted |%s|->%d->|%s|",n1->_id,w , n2->_id);
    return 0;
}

int DeleteNodesEdge(ht_hash_table* ht, char* _id1, char *_id2, int w){
    node *n1 = ht_search(ht, _id1);
    node *n2 = ht_search(ht, _id2);
    DeleteEdge(n1,n2,w);
    return 0;
}