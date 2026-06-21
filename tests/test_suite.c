#include "minunit.h"
#include "lists/test_suite_lists.c"
#include "hashTable/test_suite_hashTable.c"
#include "hashTableOA/test_suite_hashTableOA.c"
#include "hashTableDH/test_suite_hashTableDH.c"

void test_suite() {
    MU_RUN_SUITE(test_suite_lists);
	MU_RUN_SUITE(test_suite_hashTable);
	MU_RUN_SUITE(test_suite_hashTableOA);
	MU_RUN_SUITE(test_suite_hashTableDH);
	
}

int main() {
    test_suite();
    MU_REPORT();
    return MU_EXIT_CODE;
}
