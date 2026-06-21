#include <stdbool.h>
#include <stdlib.h>
#include "../minunit.h"
#include "../../src/hashTableOADH/hashTableDoubleHashing.h"
#include "../../src/items/item.h"

static HashTableAbertoDH* htDH;
static Item* item;

void test_HTDH_setup(void) {
    htDH = hashTableAbertoDH_create(10);
    item = item_create(10, 'A');
}

void test_HTDH_teardown(void) {

    hashTableAbertoDH_destroy(htDH);
    item_destroy(item);
}

MU_TEST(test_HTDH_create_nao_nulo) {
    mu_check(htDH != NULL);
}

MU_TEST(test_HTDH_insert) {
    hashTableAbertoDH_insert(htDH, item);
    Item* resultado = hashTableAbertoDH_search(htDH, 10);
    mu_check(resultado != NULL);
}

MU_TEST(test_HTDH_search_notfound) {
    Item* resultado = hashTableAbertoDH_search(htDH, 99);
    mu_check(resultado == NULL);
}

MU_TEST(test_HTDH_delete) {
    hashTableAbertoDH_insert(htDH, item);
    hashTableAbertoDH_delete(htDH, 10);
    Item* resultado = hashTableAbertoDH_search(htDH, 10);
    mu_check(resultado == NULL);
}

MU_TEST(test_HTDH_colisao) {
    Item* item2 = item_create(20, 'B');
    hashTableAbertoDH_insert(htDH, item);
    hashTableAbertoDH_insert(htDH, item2);
    mu_check(hashTableAbertoDH_search(htDH, 10) != NULL);
    mu_check(hashTableAbertoDH_search(htDH, 20) != NULL);
    item_destroy(item2);
}

MU_TEST(test_HTDH_tabela_cheia) {
    for (int i = 0; i < 10; i++) {
        hashTableAbertoDH_insert(htDH, item_create(i, 'A'));
    }
    Item* resultado = hashTableAbertoDH_search(htDH, 0);
    mu_check(resultado != NULL);
}

MU_TEST(test_HTDH_insert_duplicado) {
    hashTableAbertoDH_insert(htDH, item);
    hashTableAbertoDH_insert(htDH, item_create(10, 'Z'));
    Item* resultado = hashTableAbertoDH_search(htDH, 10);
    mu_check(resultado != NULL);
}

MU_TEST(test_HTDH_delete_notfound) {
    hashTableAbertoDH_delete(htDH, 99);
    mu_check(htDH != NULL);
}

MU_TEST(test_HTDH_insert_apos_delete) {
    hashTableAbertoDH_insert(htDH, item);
    hashTableAbertoDH_delete(htDH, 10);
    hashTableAbertoDH_insert(htDH, item_create(10, 'B'));
    Item* resultado = hashTableAbertoDH_search(htDH, 10);
    mu_check(resultado != NULL);
}

MU_TEST_SUITE(test_suite_htdh) {
    MU_SUITE_CONFIGURE(&test_HTDH_setup, &test_HTDH_teardown);
    MU_RUN_TEST(test_HTDH_create_nao_nulo);
    MU_RUN_TEST(test_HTDH_insert);
    MU_RUN_TEST(test_HTDH_search_notfound);
    MU_RUN_TEST(test_HTDH_delete);
    MU_RUN_TEST(test_HTDH_colisao);
    MU_RUN_TEST(test_HTDH_tabela_cheia);
    MU_RUN_TEST(test_HTDH_insert_duplicado);
    MU_RUN_TEST(test_HTDH_delete_notfound);
    MU_RUN_TEST(test_HTDH_insert_apos_delete);
}
