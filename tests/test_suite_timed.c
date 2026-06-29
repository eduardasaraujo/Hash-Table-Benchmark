// Executa cada suite de testes separadamente e mede o tempo gasto, repetindo cada suite várias vezes para obter uma medição estável (testes unitários individuais rodam em microssegundos). Gera tests_timing.csv com o comparativo de tempo entre as suites.//

#include "minunit.h"
#include "lists/test_suite_lists.c"
#include "hashTable/test_suite_hashTable.c"
#include "hashTableOA/test_suite_hashTableOA.c"
#include "hashTableDH/test_suite_hashTableDH.c"

#include <time.h>
#include <stdio.h>
#include <unistd.h>

#define REPEAT 2000

typedef void (*suite_fn)(void);

typedef struct {
    const char *name;
    suite_fn fn;
} SuiteEntry;

static double elapsed_seconds(struct timespec start, struct timespec end) {
    return (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
}

int main(void) {
    SuiteEntry suites[] = {
        {"Lista Duplamente Encadeada", test_suite_lists},
        {"Hash Table - Encadeamento Fechado", test_suite_hashTable},
        {"Hash Table - Enderecamento Aberto", test_suite_hashTableOA},
        {"Hash Table - Enderecamento Aberto (Double Hashing)", test_suite_hashTableDH},
    };
    int n_suites = (int)(sizeof(suites) / sizeof(suites[0]));

    FILE *csv = fopen("tests_timing.csv", "w");
    if (!csv) {
        fprintf(stderr, "Erro ao criar tests_timing.csv\n");
        return 1;
    }
    fprintf(csv, "Suite,Repeticoes,Testes_por_execucao,Assertions_por_execucao,Falhas,Tempo_total_s,Tempo_medio_por_execucao_ms\n");

    printf("Repeticoes por suite: %d\n\n", REPEAT);
    printf("%-52s %12s %14s %10s %10s\n", "Suite", "Tempo total", "Media/exec", "Testes", "Falhas");
    printf("%-52s %12s %14s %10s %10s\n", "", "(s)", "(ms)", "", "");
    fflush(stdout);

    // Redireciona stdout para /dev/null durante as repeticoes, pois o  framework de teste (minunit) e o codigo testado imprimem uma mensagem por assertion/print de debug, o que inundaria o console quando cada suite roda milhares de vezes. //

    fflush(stdout);
    int saved_stdout = dup(STDOUT_FILENO);
    FILE *devnull = fopen("/dev/null", "w");

    for (int i = 0; i < n_suites; i++) {
        int run_before = minunit_run;
        int assert_before = minunit_assert;
        int fail_before = minunit_fail;

        struct timespec start, end;
        dup2(fileno(devnull), STDOUT_FILENO);
        clock_gettime(CLOCK_MONOTONIC, &start);
        for (int r = 0; r < REPEAT; r++) {
            suites[i].fn();
            minunit_setup = NULL;
            minunit_teardown = NULL;
        }
        clock_gettime(CLOCK_MONOTONIC, &end);
        fflush(stdout);
        dup2(saved_stdout, STDOUT_FILENO);

        double total = elapsed_seconds(start, end);
        int tests_total = minunit_run - run_before;
        int asserts_total = minunit_assert - assert_before;
        int fails_total = minunit_fail - fail_before;
        int tests_per_run = tests_total / REPEAT;
        int asserts_per_run = asserts_total / REPEAT;
        double avg_ms = (total / REPEAT) * 1000.0;

        printf("%-52s %12.6f %14.6f %10d %10d\n", suites[i].name, total, avg_ms, tests_per_run, fails_total);
        fflush(stdout);

        fprintf(csv, "%s,%d,%d,%d,%d,%.8f,%.8f\n", suites[i].name, REPEAT, tests_per_run, asserts_per_run, fails_total, total, avg_ms);
    }

    fclose(devnull);
    close(saved_stdout);

    fclose(csv);
    printf("\nResultados salvos em tests_timing.csv\n");
    return 0;
}