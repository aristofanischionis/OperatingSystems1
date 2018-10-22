#include "../HeaderFiles/HashTable.h"

int InsertNode(ht_hash_table* , char* );
int InsertNodesEdge(ht_hash_table* , char* , char *, int );
int UpdateWeight(ht_hash_table* , char* , char*, int , int );
int DeleteNode(ht_hash_table* , char* );
int DeleteNodesEdge(ht_hash_table* , char* , char *, int );
int DeleteAllNodesEdge(ht_hash_table* , char* , char *);
void ExitProgram(ht_hash_table* , char *);