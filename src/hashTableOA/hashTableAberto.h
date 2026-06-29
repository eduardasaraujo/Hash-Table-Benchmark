#ifndef HASHTABLEABERTO_H
#define HASHTABLEABERTO_H
#include "../items/item.h"

struct HashTableAberto
{ // struct básico
    Item **table;
    int size;
};
typedef struct HashTableAberto HashTableAberto;
HashTableAberto *hashTableAberto_create(int size);
void hashTableAberto_destroy(HashTableAberto *minhahash);
void hashTableAberto_insert(HashTableAberto *minhahash, Item *item);
void hashTableAberto_delete(HashTableAberto *minhahash, int chave);
Item *hashTableAberto_search(HashTableAberto *minhahash, int chave);

#endif
