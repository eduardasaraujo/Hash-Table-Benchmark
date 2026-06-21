#ifndef ITEM_H //bloqueia que seja, criados dois itens sem necessidade
#define ITEM_H

typedef struct item Item;
Item * item_create(int key, char value);
void item_destroy(Item * item);
int item_getKey(Item * item); //pegar chave
char item_getValue(Item * item); //pegar valor
void setValue(Item * item, char value); //altera valor

#endif
