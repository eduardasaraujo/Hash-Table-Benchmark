#include <stdio.h>
#include <stdlib.h>
#include "hashTableDoubleHashing.h"

static int DELETED_SENTINEL;
#define DELETED ((Item *)&DELETED_SENTINEL) // sentinel como DELETE para poder continuar a busca pós deletar um item.

static int hash(int chave, int size)
{ // Hash 1
    return chave % size;
}

static int hash2(int chave)
{ // Hash 2
    return 7 - (chave % 7);
}

static int probe(int index, int i, int size, int chave)
{ // Sondagem da DH
    return (index + i * hash2(chave)) % size;
}

HashTableAbertoDH *hashTableAbertoDH_create(int size)
{
    HashTableAbertoDH *ht = malloc(sizeof(HashTableAbertoDH));
    if (!ht)
    {
        return NULL;
    }
    ht->size = size;
    ht->table = calloc(size, sizeof(Item *)); // transforma todos os ponteiros em NULL e reserva a exata quantidade de bytes de size x sizeof(Item*)

    if (!ht->table)
    { // se o calloc falhar da free na ht e retorna null
        free(ht);
        return NULL;
    }
    return ht;
}
void hashTableAbertoDH_destroy(HashTableAbertoDH *minhahash)
{
    free(minhahash->table);
    free(minhahash);
}
void hashTableAbertoDH_insert(HashTableAbertoDH *minhahash, Item *item)
{
    int chave = item_getKey(item);
    int index = chave % minhahash->size;

    int i = 0;
    while (i < minhahash->size)
    {
        int pos = probe(index, i, minhahash->size, chave); // calcúla a posição na tabela onde  a operação deve agir,chama a função probe[Double Hashing]
        if (minhahash->table[pos] == NULL || minhahash->table[pos] == DELETED)
        {
            minhahash->table[pos] = item;
            return;
        }
        i++; // em caso de slot ocupado passa ao próximo
    }
}
void hashTableAbertoDH_delete(HashTableAbertoDH *minhahash, int chave)
{
    int index = hash(chave, minhahash->size);
    int i = 0;
    while (i < minhahash->size)
    {
        int pos = probe(index, i, minhahash->size, chave); // calcúla a posição na tabela onde  a operação deve agir,chama a função probe[Double Hashing]
        if (minhahash->table[pos] == NULL)
        {
            printf("Chave %d não encontrada!\n", chave);
            return;
        }
        if (minhahash->table[pos] != DELETED)
            if (item_getKey(minhahash->table[pos]) == chave)
            {
                minhahash->table[pos] = DELETED;
                return;
            }
        i++;
    }
    printf("Chave %d não encontrada!\n", chave);
}
Item *hashTableAbertoDH_search(HashTableAbertoDH *minhahash, int chave)
{
    int index = hash(chave, minhahash->size);
    int i = 0;
    while (i < minhahash->size)
    {
        int pos = probe(index, i, minhahash->size, chave); // calcúla a posição na tabela onde  a operação deve agir,chama a função probe[Double Hashing]
        if (minhahash->table[pos] == NULL)
            return NULL;
        if (minhahash->table[pos] != DELETED)
            if (item_getKey(minhahash->table[pos]) == chave)
                return minhahash->table[pos];
        i++;
    }
    return NULL;
}