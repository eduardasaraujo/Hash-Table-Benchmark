#include <stdlib.h>
#include "../minunit.h"
#include "../../src/hashTableOA/hashTableAberto.h"
#include "../../src/items/item.h"

static HashTableAberto* htOA;
static Item* item;

void test_HTOA_setup(void) {
    htOA = hashTableAberto_create(10);
    item = item_create(10, 'A');
}

void test_HTOA_teardown(void) {
    hashTableAberto_destroy(htOA);
    item_destroy(item);
}

MU_TEST(test_HTOA_create_nao_nulo) {
    mu_check(htOA != NULL);
}

MU_TEST(test_HTOA_insert) {
    hashTableAberto_insert(htOA, item);
    Item* resultado = hashTableAberto_search(htOA, 10);
    mu_check(resultado != NULL);
}

MU_TEST(test_HTOA_search_notfound) {
    Item* resultado = hashTableAberto_search(htOA, 99);
    mu_check(resultado == NULL);
}

MU_TEST(test_HTOA_delete) {
    hashTableAberto_insert(htOA, item);
    hashTableAberto_delete(htOA, 10);
    Item* resultado = hashTableAberto_search(htOA, 10);
    mu_check(resultado == NULL);
}

MU_TEST(test_HTOA_colisao) {
    Item* item2 = item_create(20, 'B');
    hashTableAberto_insert(htOA, item);
    hashTableAberto_insert(htOA, item2);
    mu_check(hashTableAberto_search(htOA, 10) != NULL);
    mu_check(hashTableAberto_search(htOA, 20) != NULL);
    item_destroy(item2);
}

MU_TEST(test_HTOA_tabela_cheia) {
    for (int i = 0; i < 10; i++) {
        hashTableAberto_insert(htOA, item_create(i, 'A'));
    }
    Item* resultado = hashTableAberto_search(htOA, 0);
    mu_check(resultado != NULL);
}

MU_TEST(test_HTOA_insert_duplicado) {
    hashTableAberto_insert(htOA, item);
    hashTableAberto_insert(htOA, item_create(10, 'Z'));
    Item* resultado = hashTableAberto_search(htOA, 10);
    mu_check(resultado != NULL);
}

MU_TEST(test_HTOA_delete_notfound) {
    hashTableAberto_delete(htOA, 99);
    mu_check(htOA != NULL);
}

MU_TEST(test_HTOA_insert_apos_delete) {
    hashTableAberto_insert(htOA, item);
    hashTableAberto_delete(htOA, 10);
    hashTableAberto_insert(htOA, item_create(10, 'B'));
    Item* resultado = hashTableAberto_search(htOA, 10);
    mu_check(resultado != NULL);
}

MU_TEST_SUITE(test_suite_htoa) {
    MU_SUITE_CONFIGURE(&test_HTOA_setup, &test_HTOA_teardown);
    MU_RUN_TEST(test_HTOA_create_nao_nulo);
    MU_RUN_TEST(test_HTOA_insert);
    MU_RUN_TEST(test_HTOA_search_notfound);
    MU_RUN_TEST(test_HTOA_delete);
    MU_RUN_TEST(test_HTOA_colisao);
    MU_RUN_TEST(test_HTOA_tabela_cheia);
    MU_RUN_TEST(test_HTOA_insert_duplicado);
    MU_RUN_TEST(test_HTOA_delete_notfound);
    MU_RUN_TEST(test_HTOA_insert_apos_delete);
}
