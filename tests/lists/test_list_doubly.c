#include <stdbool.h>
#include <stdlib.h>
#include "../../src/lists/doublyLinkedList.h"
#include "../../src/items/item.h"

static DoublyLinkedList* list;
static Item* item;

void test_DLL_setup(void) {
	list = doublyLinkedList_create();
	item = item_create(10, 'A');
}

void test_DLL_teardown(void) {
	doublyLinkedList_destroy(list);
	item_destroy(item);
}

MU_TEST(test_DLL_create_nao_nulo) {
	mu_check(list != NULL);

}

MU_TEST(test_item_getKey) {
    mu_assert_int_eq(10, item_getKey(item));
}

MU_TEST(test_item_setValue) {
    setValue(item, 'Z');
    mu_assert_int_eq('Z', item_getValue(item));
}

MU_TEST(test_item_getValue) {
    mu_assert_int_eq('A', item_getValue(item));
}

MU_TEST(test_DLL_insert) {
	doublyLinkedList_insert(list, item);
	Item* resultado = doublyLinkedList_search(list, 10);
	mu_check(resultado != NULL);
}

MU_TEST(test_DLL_search_notfound) {
    Item* resultado = doublyLinkedList_search(list, 99);
    mu_check(resultado == NULL);
}

MU_TEST(test_DLL_delete) {
	doublyLinkedList_insert(list, item);
    doublyLinkedList_delete(list, 10);
    Item* resultado = doublyLinkedList_search(list, 10);
    mu_check(resultado == NULL);
}

MU_TEST_SUITE(test_suite_dll) {
    MU_SUITE_CONFIGURE(&test_DLL_setup, &test_DLL_teardown);
    MU_RUN_TEST(test_DLL_create_nao_nulo);
    MU_RUN_TEST(test_item_getKey);
    MU_RUN_TEST(test_item_getValue);
    MU_RUN_TEST(test_item_setValue);
    MU_RUN_TEST(test_DLL_insert);
    MU_RUN_TEST(test_DLL_search_notfound);
    MU_RUN_TEST(test_DLL_delete);
}
