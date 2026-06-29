#ifndef HASHTABLEABERTO_DH_H
#define HASHTABLEABERTO_DH_H
#include "../items/item.h"

struct HashTableAbertoDH
{ // struct básico
    Item **table;
    int size;
};

typedef struct HashTableAbertoDH HashTableAbertoDH;
HashTableAbertoDH *hashTableAbertoDH_create(int size);
void hashTableAbertoDH_destroy(HashTableAbertoDH *minhahash);
void hashTableAbertoDH_insert(HashTableAbertoDH *minhahash, Item *item);
void hashTableAbertoDH_delete(HashTableAbertoDH *minhahash, int chave);
Item *hashTableAbertoDH_search(HashTableAbertoDH *minhahash, int chave);

#endif