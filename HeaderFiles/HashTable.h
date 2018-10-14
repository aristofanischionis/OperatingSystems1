#include "Node.h"

typedef struct {
    char* key;
    node* MyNode;
} ht_item;

typedef struct {
    int size;
    int count;
    int base_size;
    ht_item** items;
} ht_hash_table;

void ht_insert(ht_hash_table* ht, const char* key, const node* node);
node* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);