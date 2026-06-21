#include <stdbool.h>
#include "../items/item.h"

typedef struct HashTable HashTable;

HashTable* hashTable_create(int size);

void hashTable_destroy(
    HashTable* minhaHash
);

void hashTable_insert(
    HashTable* minhaHash,
    Item * item
);

void hashTable_delete(
    HashTable* minhaHash,
    int chave
    
);

Item* hashTable_search(
    HashTable* minhaHash,
    int chave
);