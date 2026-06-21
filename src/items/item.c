// O Item agrupa key + value juntos, como um par
#include "item.h"
#include <stdlib.h>

struct item
{
    int chave;
    char valor;
};

Item *item_create(int key, char value)
{
    Item *item = (Item *)malloc(sizeof(Item));
    if (item == NULL)
    {
        return NULL;
    }
    item->chave = key;
    item->valor = value;
    return item;
}
// se o item for == 0 é null se não eu pego i tem da chave tal, com o valor tal e retorno o item pra colocar  na memoria com o malloc
void item_destroy(Item *item)
{
    free(item);
}
// corrigido
int item_getKey(Item *item)
{
    return item->chave;
}

char item_getValue(Item *item)
{
    return item->valor;
}

void setValue(Item *item, char value)
{
    item->valor = value;
}