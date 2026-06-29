#include "hashTableAberto.h"
#include <stdio.h>
#include <stdlib.h>

static int DELETED_SENTINEL;
#define DELETED ((Item *)&DELETED_SENTINEL) // sentinel como DELETE para poder continuar a busca pós deletar um item.

static int hash(int chave, int size)
{ // função hash simples
    return chave % size;
}

HashTableAberto *hashTableAberto_create(int size)
{
    HashTableAberto *ht = malloc(sizeof(HashTableAberto));
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

void hashTableAberto_destroy(HashTableAberto *minhahash)
{
    free(minhahash->table);
    free(minhahash);
}

void hashTableAberto_insert(HashTableAberto *minhahash, Item *item)
{
    int chave = item_getKey(item);
    int index = hash(chave, minhahash->size); // calcula a posição ideal do item na tabela

    int i = 0;
    while (i < minhahash->size)
    {
        int pos = (index + i) % minhahash->size; // sondagem linear em caso de colisão
        if (minhahash->table[pos] == NULL || minhahash->table[pos] == DELETED)
        { // verificação se o slot está vazio para ai sim adicionar
            minhahash->table[pos] = item;
            return;
        }
        i++;
    }
    printf("Tabela cheia!\n");
}

void hashTableAberto_delete(HashTableAberto *minhahash, int chave)
{
    int index = hash(chave, minhahash->size); // calcula a posição inicial de onde a chave deveria estar
    int i = 0;

    while (i < minhahash->size)
    {
        int pos = (index + i) % minhahash->size; // calcula a posição atual de busca [usa sondagem linear]
        if (minhahash->table[pos] == NULL)
        {
            printf("Chave %d não encontrada!\n", chave);
            return;
        }
        if (minhahash->table[pos] != DELETED)
        {
            if (item_getKey(minhahash->table[pos]) == chave)
            {                                    // extrai a chave do item guardado na posição atual e verifica se ela é igual a que queremos deletar
                minhahash->table[pos] = DELETED; // marca o sentinel no lugar do item deletado
                return;
            }
        }
        i++;
    }
    printf("Chave %d não encontrada!\n", chave);
}

Item *hashTableAberto_search(HashTableAberto *minhahash, int chave)
{
    int index = hash(chave, minhahash->size); // cálculo da posição inicial ideal da chave
    int i = 0;

    while (i < minhahash->size)
    {
        int pos = (index + i) % minhahash->size;

        if (minhahash->table[pos] == NULL)
        {
            return NULL; // slot vazio = chave não existe na tabela
        }
        if (minhahash->table[pos] != DELETED)
        {
            if (item_getKey(minhahash->table[pos]) == chave)
            {
                return minhahash->table[pos]; // achou o que estava procurando
            }
        }
        i++;
    }
    return NULL;
}