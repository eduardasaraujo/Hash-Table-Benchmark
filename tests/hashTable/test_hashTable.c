#include <stdbool.h>
#include <stdlib.h>
#include "../minunit.h"
#include "../../src/hashTable/hashTable.h"
#include "../../src/items/item.h"

static HashTable* ht;
static Item* item;

void test_HT_setup(void) {
    ht = hashTable_create(10);
    item = item_create(10, 'A');
}

void test_HT_teardown(void) {
    hashTable_destroy(ht);
    item_destroy(item);
}

MU_TEST(test_HT_create_nao_nulo) {
    mu_check(ht != NULL);
}

MU_TEST(test_HT_insert) {
    hashTable_insert(ht, item);
    Item* resultado = hashTable_search(ht, 10);
    mu_check(resultado != NULL);
}

MU_TEST(test_HT_search_notfound) {
    Item* resultado = hashTable_search(ht, 99);
    mu_check(resultado == NULL);
}

MU_TEST(test_HT_delete) {
    hashTable_insert(ht, item);
    hashTable_delete(ht, 10);
    Item* resultado = hashTable_search(ht, 10);
    mu_check(resultado == NULL);
}

MU_TEST(test_HT_colisao) {
    Item* item2 = item_create(20, 'B');
    hashTable_insert(ht, item);
    hashTable_insert(ht, item2);
    mu_check(hashTable_search(ht, 10) != NULL);
    mu_check(hashTable_search(ht, 20) != NULL);
    item_destroy(item2);
}

MU_TEST_SUITE(test_suite_ht) {
    MU_SUITE_CONFIGURE(&test_HT_setup, &test_HT_teardown);
    MU_RUN_TEST(test_HT_create_nao_nulo);
    MU_RUN_TEST(test_HT_insert);
    MU_RUN_TEST(test_HT_search_notfound);
    MU_RUN_TEST(test_HT_delete);
    MU_RUN_TEST(test_HT_colisao);
}
