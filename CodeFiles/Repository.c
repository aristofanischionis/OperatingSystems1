#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../HeaderFiles/HashTable.h"

int InsertNode(ht_hash_table* ht, char* _id){
    //this function calls backend functions to insert a new Node to the Hash Table
    //search if there is another node named _id
    char *pos;
    if ((pos=strchr(_id, '\n')) != NULL) *pos = '\0';
    node *n = ht_search(ht, _id);
    if(n != NULL){
        // node with _id found
        if ((pos=strchr(n->_id, '\n')) != NULL) *pos = '\0';
        printf("\t- Node |%s| Exists;\n", n->_id);
        return 1;
    }
    
    ht_insert(ht,_id);
    
    printf("\t- Inserted |%s|\n",_id);
    return 0;
}

int DeleteNode(ht_hash_table* ht, char* _id){
    char *pos;
    if ((pos=strchr(_id, '\n')) != NULL) *pos = '\0';
    node *n = ht_search(ht, _id);
    if( n == NULL ){
        // couldn't find Node
        printf("\t- Node |%s| does not exist - abort-d;\n",_id);
        return 1;
    }
    ht_delete(ht, _id);
    printf("\t- Deleted |%s|\n", _id);
    return 0;
}

int InsertNodesEdge(ht_hash_table* ht, char* _id1, char *_id2, int w){
    //this function inserts a new edge if the _id1 and 2 exist else it creates them first
    char *pos;
    if ((pos=strchr(_id1, '\n')) != NULL) *pos = '\0';
    if ((pos=strchr(_id2, '\n')) != NULL) *pos = '\0';
    InsertNode(ht, _id1);
    InsertNode(ht, _id2);
    // now that we have both nodes ready let's make the edge
    node *n1 = ht_search(ht, _id1);
    node *n2 = ht_search(ht, _id2);
    InsertEdge(&(n1->HeadEdges), w, n2);// put it in the n1's linked List
    
    printf("\t- Inserted |%s|->%d->|%s|\n",n1->_id, w, n2->_id);
    return 0;
}

int DeleteNodesEdge(ht_hash_table* ht, char* _id1, char *_id2, int w){
    char *pos;
    if ((pos=strchr(_id1, '\n')) != NULL) *pos = '\0';
    if ((pos=strchr(_id2, '\n')) != NULL) *pos = '\0';
    node *n1 = ht_search(ht, _id1);
    node *n2 = ht_search(ht, _id2);
    if(n1 == NULL){
        printf("\t- |%s| does not exist - abort-l;\n",n1->_id);
        return 1;
    }
    if(n2 == NULL){
        printf("\t- |%s| does not exist - abort-l;\n",n2->_id);
        return 1;
    }
    edge *del = SearchEdge(n1, n2, w);
    if( del == NULL){
        printf("\t- |%s|->%d->|%s| does not exist - abort-l;\n",n1->_id, w, n2->_id);
        return 1;    
    }

    DeleteEdge(&(n1->HeadEdges), del);
    return 0;
}