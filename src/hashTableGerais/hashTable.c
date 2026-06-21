#include "hashTable.h"
#include "../lists/doublyLinkedList.h"
#include <stdlib.h>
#include <stdbool.h>
#define PRIME 2147483647LL
// mudar a estrutura da formula para garantir um bom alpha = m/m -> quantidade de espaços oculpados e a quantidade de espaços vazio é 1-alpha"
struct HashTable
{
    int size;
    int capacity;
    int a;
    int b;
    DoublyLinkedList **table;
};
HashTable *hashTable_create(int size)
{
    HashTable *minhaHash = (HashTable *)malloc(sizeof(HashTable));
    minhaHash->size = size;
    minhaHash->a = 3;
    minhaHash->b = 7;
    minhaHash->table = (DoublyLinkedList **)malloc(sizeof(DoublyLinkedList *) * size);
    if (minhaHash->table == NULL)
    {
        free(minhaHash);
        return NULL;
    }
    for (int i = 0; i < size; i++)
    {
        minhaHash->table[i] = doublyLinkedList_create();
    }
    return minhaHash;
}

static int funcaoHash(HashTable *minhaHash, int chave){
    long long h = ((long long)minhaHash->a * chave + minhaHash->b) % PRIME;
    int indice = (int)(h % minhaHash->size);
    return indice;
}

void hashTable_insert(HashTable *minhaHash, Item *item)
{
    int chave = item_getKey(item);
    int indice = funcaoHash(minhaHash, chave);
    DoublyLinkedList *list = *(minhaHash->table + indice);
    doublyLinkedList_insert(list, item);
}

Item *hashTable_search(HashTable *minhaHash, int chave)
{
    int indice = funcaoHash(minhaHash, chave);
    return doublyLinkedList_search(
        minhaHash->table[indice], chave);
}
void hashTable_delete(HashTable *minhaHash, int chave)
{
    int indice = funcaoHash(minhaHash, chave);
    return doublyLinkedList_delete(
        minhaHash->table[indice], chave);
}

void hashTable_destroy(HashTable *minhaHash)
{
    if (minhaHash == NULL)
        return;
    for (int i = 0; i < minhaHash->size; i++)
    {
        doublyLinkedList_destroy(minhaHash->table[i]);
    }
    free(minhaHash->table);
    free(minhaHash);
}
