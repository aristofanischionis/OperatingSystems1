#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../HeaderFiles/HashTable.h"
#include "../HeaderFiles/Prime.h"

const int HT_PRIME_1 = 13; // random prime
const int HT_PRIME_2 = 43; // random prime

const int HT_INITIAL_BASE_SIZE = 53; // prime number
static node HT_DELETED_NODE = {NULL, NULL};

static void ht_resize_up(ht_hash_table* );
static void ht_resize_down(ht_hash_table* );

static ht_hash_table* ht_new_sized(const int base_size) {
    ht_hash_table* ht = malloc(sizeof(ht_hash_table));
    ht->base_size = base_size;
    ht->size = next_prime(ht->base_size);
    ht->count = 0;
    ht->nodes = calloc((size_t)ht->size, sizeof(node*));
    return ht;
}

ht_hash_table* ht_new() {
    return ht_new_sized(HT_INITIAL_BASE_SIZE);
}

static void ht_del_node(node* i) {
    free(i->_id);
    DeleteEdge(i->HeadEdges,0); 
    // 0 to delete all edges in the linked list
    free(i);
}

void ht_del_hash_table(ht_hash_table* ht) {
    for (int i = 0; i < ht->size; i++) {
        node* item = ht->nodes[i];
        if (item != NULL) {
            ht_del_node(item);
        }
    }
    free(ht->nodes);
    free(ht);
}
// hash function 
static int ht_hash(const char* s, const int a, const int m) {
    long hash = 0;
    const int len_s = strlen(s);
    for (int i = 0; i < len_s; i++) {
        hash += (long)pow(a, len_s - (i+1)) * s[i];
        hash = hash % m;
    }
    return (int)hash;
}
//avoiding collisions double hashing
static int ht_get_hash(
    const char* s, const int num_buckets, const int attempt
) {
    const int hash_a = ht_hash(s, HT_PRIME_1, num_buckets);
    const int hash_b = ht_hash(s, HT_PRIME_2, num_buckets);
    return (hash_a + (attempt * (hash_b + 1))) % num_buckets;
}

void ht_insert(ht_hash_table* ht, char* _id) {
    const int load = ht->count * 100 / ht->size;
    if (load > 70) {
        ht_resize_up(ht);
    }
    node *item = NewNode(_id, NULL); // New Node without edges
    int index = ht_get_hash(item->_id, ht->size, 0);
    node* cur_item = ht->nodes[index];
    int i = 1;
    while (cur_item != NULL) {
        if (cur_item != &HT_DELETED_NODE) {
            if (strcmp(cur_item->_id, _id) == 0) {
                ht_del_node(cur_item);
                ht->nodes[index] = item;
                return;
            }
        }
        index = ht_get_hash(item->_id, ht->size, i);
        cur_item = ht->nodes[index];
        i++;
    } // avoid collisions, trying to find the suitable index to place the node
    ht->nodes[index] = item;
    ht->count++; // node inserted
}

node* ht_search(ht_hash_table* ht, char* _id) {
    int index = ht_get_hash(_id, ht->size, 0);
    node* item = ht->nodes[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HT_DELETED_NODE) { 
            if (strcmp(item->_id, _id) == 0) {
                return item;
            }
        }
        index = ht_get_hash(_id, ht->size, i);
        item = ht->nodes[index];
        i++;
    } 
    return NULL;
}
// delete an item with HashTable resize if needed

void ht_delete(ht_hash_table* ht, char* _id) {
    const int load = ht->count * 100 / ht->size;
    if (load < 10) {
        ht_resize_down(ht);
    }
    int index = ht_get_hash(_id, ht->size, 0);
    node* item = ht->nodes[index];
    int i = 1;
    while (item != NULL) {
        if (item != &HT_DELETED_NODE) {
            if (strcmp(item->_id, _id) == 0) {
                ht_del_node(item);
                ht->nodes[index] = &HT_DELETED_NODE;
            }
        }
        index = ht_get_hash(_id, ht->size, i);
        item = ht->nodes[index];
        i++;
    } 
    ht->count--;
}

static void ht_resize(ht_hash_table* ht, const int base_size) {
    if (base_size < HT_INITIAL_BASE_SIZE) {
        return;
    }
    ht_hash_table* new_ht = ht_new_sized(base_size);
    for (int i = 0; i < ht->size; i++) {
        node* item = ht->nodes[i];
        if (item != NULL && item != &HT_DELETED_NODE) {
            ht_insert(new_ht, item->_id);
        }
    }

    ht->base_size = new_ht->base_size;
    ht->count = new_ht->count;

    // To delete new_ht, we give it ht's size and nodes 
    const int tmp_size = ht->size;
    ht->size = new_ht->size;
    new_ht->size = tmp_size;

    node** tmp_items = ht->nodes;
    ht->nodes = new_ht->nodes;
    new_ht->nodes = tmp_items;

    ht_del_hash_table(new_ht);
}

static void ht_resize_up(ht_hash_table* ht) {
    const int new_size = ht->base_size * 2;
    ht_resize(ht, new_size);
}


static void ht_resize_down(ht_hash_table* ht) {
    const int new_size = ht->base_size / 2;
    ht_resize(ht, new_size);
}