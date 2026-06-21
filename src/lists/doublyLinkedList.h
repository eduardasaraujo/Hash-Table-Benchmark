//as variaveis vao ser item(juntar o index com o value),chave-> a busca vai ser com a chave pq tem varios itens e com a chave vc compara o item, hashTable, index, doublylInkedList;
// a busca retorna o item;
#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <stdbool.h>
#include "../items/item.h"

typedef struct node Node;
typedef struct doublyLinkedList DoublyLinkedList;

DoublyLinkedList* doublyLinkedList_create();

void doublyLinkedList_destroy(
    DoublyLinkedList* list
);

void doublyLinkedList_insert( 
    DoublyLinkedList* list,
    Item* item
);       

void doublyLinkedList_delete(
    DoublyLinkedList* list,
    int chave
);

Item* doublyLinkedList_search(
    DoublyLinkedList* list,
    int chave
);
#endif