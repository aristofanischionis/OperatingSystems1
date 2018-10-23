#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "../HeaderFiles/API.h"

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
    //first delete all edges going to _id
    node *temp;
    for (int i = 0; i < ht->size; i++) {
        temp = ht->nodes[i];
        if (temp != NULL) {
            DeleteEdgesFrom(temp , n);
        }
    }
    ht_delete(ht, _id); // this will also delete all of the outgoing edges
    // not only delete node but the associated edges as well
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
        printf("\t- |%s| does not exist - abort-l;\n",_id1);
        return 1;
    }
    if(n2 == NULL){
        printf("\t- |%s| does not exist - abort-l;\n",_id2);
        return 1;
    }
    edge *del = SearchEdge(n1, n2, w);
    if( del == NULL){
        printf("\t- |%s|->%d->|%s| does not exist - abort-l;\n",n1->_id, w, n2->_id);
        return 1;    
    }

    DeleteEdge(&(n1->HeadEdges), del);
    printf("\t- Del-vertex |%s|->%d->|%s|\n",n1->_id, w, n2->_id);
    return 0;
}

int UpdateWeight(ht_hash_table* ht, char* _id1, char *_id2, int w, int nw){
    char *pos;
    if ((pos=strchr(_id1, '\n')) != NULL) *pos = '\0';
    if ((pos=strchr(_id2, '\n')) != NULL) *pos = '\0';
    node *n1 = ht_search(ht, _id1);
    node *n2 = ht_search(ht, _id2);
    if(n1 == NULL){
        printf("\t- |%s| does not exist - abort-m;\n",_id1);
        return 1;
    }
    if(n2 == NULL){
        printf("\t- |%s| does not exist - abort-m;\n",_id2);
        return 1;
    }
    edge *e = UpdateEdge(n1, n2, w, nw);
    if(e == NULL){
        printf("\t- |%s|->%d->|%s| does not exist - abort-m;\n",n1->_id, w, n2->_id);
        return 1;
    }
    printf("\t- Mod-vertex |%s|->%d->|%s|\n",n1->_id, nw, n2->_id);
    return 0;
}

int DeleteAllNodesEdge(ht_hash_table* ht, char* _id1, char *_id2){
    char *pos;
    if ((pos=strchr(_id1, '\n')) != NULL) *pos = '\0';
    if ((pos=strchr(_id2, '\n')) != NULL) *pos = '\0';
    node *n1 = ht_search(ht, _id1);
    node *n2 = ht_search(ht, _id2);
    if(n1 == NULL){
        printf("\t- |%s| does not exist - abort-l;\n",_id1);
        return 1;
    }
    if(n2 == NULL){
        printf("\t- |%s| does not exist - abort-l;\n",_id2);
        return 1;
    }
    DeleteEdgesFrom(n1, n2);
    // DeleteEdgesFrom(n2, n1); 
    // apparently we don't need to delete all edges from n2->n1 as I just read from piazza
    printf("\t- Del All Vertices between |%s| and |%s|\n", _id1, _id2);
    return 0;
}

int Receiving(ht_hash_table* ht, char* _id){
    char *pos;
    if ((pos=strchr(_id, '\n')) != NULL) *pos = '\0';
    node *n = ht_search(ht, _id);
    if( n == NULL ){
        // couldn't find Node
        printf("\t- |%s| does not exist - abort-r;\n",_id);
        return 1;
    }
    int counter =0;
    node *temp;
    edge *e;
    for (int i = 0; i < ht->size; i++) {
        temp = ht->nodes[i];
        if (temp != NULL) {
            e = SearchEdgeNoWeight(temp , n);
            // find the first edge from temp -> n it may have more
            if(e != NULL){
                if(counter == 0){
                    counter++;
                    printf("\t- Rec-edges |%s|->%d->|%s|\n", temp->_id, e->weight, n->_id);
                }
                else printf("\t            |%s|->%d->|%s|\n", temp->_id, e->weight, n->_id);
            }
        }
    }
    if(counter == 0) printf("\t- No-rec-edges %s\n", n->_id);
    return 0;
}

void ExitProgram(ht_hash_table* ht,  char *output){
    // free up all space
    if(strcmp(output, "") != 0) OutputManager(ht, output);
    // else printf("\t- No Output File Name is given\n");
    printf("\t- exit program\n");
    ht_del_hash_table(ht);
    return;
}