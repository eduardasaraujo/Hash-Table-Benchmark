#include "doublyLinkedList.h"
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    Item *item;
    Node *prev;
    Node *next;
};

struct doublyLinkedList
{
    Node *head;
};

static Node *node_create(Item *item, Node *prev, Node *next)
{
    Node *node = (Node *)malloc(sizeof(Node));

    node->item = item;
    node->prev = prev;
    node->next = next;

    return node;
}

static void node_destroy(Node *node)
{
    free(node);
}

DoublyLinkedList *doublyLinkedList_create()
{
    DoublyLinkedList *list = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));

    list->head = NULL;

    return list;
}

void doublyLinkedList_destroy(DoublyLinkedList *list)
{
    Node *temp = list->head;

    while (temp != NULL)
    {
        Node *next = temp->next;

        node_destroy(temp);

        temp = next;
    }

    free(list);
}

void doublyLinkedList_insert(DoublyLinkedList *list, Item *item)
{
    Node *temp = list->head;

    while (temp != NULL)
    {
        if (item_getKey(temp->item) == item_getKey(item))
        {
            setValue(temp->item, item_getValue(item));
            return;
        }

        temp = temp->next;
    }

    Node *node = node_create(item, NULL, list->head);

    if (list->head != NULL)
    {
        list->head->prev = node;
    }

    list->head = node;
}

void doublyLinkedList_delete(DoublyLinkedList *list, int chave)
{
    Node *temp = list->head;

    while (temp != NULL)
    {
        if (item_getKey(temp->item) == chave)
        {
            if (temp->prev != NULL)
            {
                temp->prev->next = temp->next;
            }
            else
            {
                list->head = temp->next;
            }

            if (temp->next != NULL)
            {
                temp->next->prev = temp->prev;
            }

            node_destroy(temp);

            return;
        }

        temp = temp->next;
    }
}

Item *doublyLinkedList_search(DoublyLinkedList *list, int chave)
{
    Node *temp = list->head;

    while (temp != NULL)
    {
        if (item_getKey(temp->item) == chave)
        {
            return temp->item;
        }

        temp = temp->next;
    }

    return NULL;
}