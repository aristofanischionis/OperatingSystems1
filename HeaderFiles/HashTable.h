#include "Node.h"

struct ht_hash_table {
    int size;
    int count;
    int base_size;
    struct node** nodes;
};

typedef struct ht_hash_table ht_hash_table;

ht_hash_table* ht_new();
void ht_insert(ht_hash_table* ht, char* _id);
node* ht_search(ht_hash_table* ht, char* _id);
void ht_delete(ht_hash_table* ht, char* _id);