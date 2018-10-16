#include "Node.h"

struct ht_item {
    char* key;
    node* MyNode;
};

struct ht_hash_table {
    int size;
    int count;
    int base_size;
    struct ht_item** items;
};

typedef struct ht_item ht_item;
typedef struct ht_hash_table ht_hash_table;

ht_hash_table* ht_new();
void ht_insert(ht_hash_table* ht, const char* key, node* node);
node* ht_search(ht_hash_table* ht, const char* key);
void ht_delete(ht_hash_table* h, const char* key);