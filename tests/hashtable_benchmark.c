//enchmark "de carga real" comparando as 3 implementacoes de hash table encadeamento fechado, enderecamento aberto, double hashing) em insercao, busca (hit e miss) e remocao de N chaves, variando o fator de carga (alpha = N / tamanho_da_tabela). Gera benchmark_results.csv.//

#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../src/items/item.h"
#include "../src/hashTable/hashTable.h"
#include "../src/hashTableOA/hashTableAberto.h"
#include "../src/hashTableOADH/hashTableDoubleHashing.h"

#define N 20000
#define REPS 3

static const double ALPHAS[] = {0.5, 0.7, 0.9, 0.95};
#define N_ALPHAS (int)(sizeof(ALPHAS) / sizeof(ALPHAS[0]))

typedef struct {
    double insert, search_hit, search_miss, del;
} Times;

static int is_prime(long n) {
    if (n < 2) return 0;
    if (n % 2 == 0) return n == 2;
    for (long i = 3; i * i <= n; i += 2)
        if (n % i == 0) return 0;
    return 1;
}

static long next_prime(long n) {
    long c = (n % 2 == 0) ? n + 1 : n;
    if (c < 3) c = 3;
    while (!is_prime(c)) c += 2;
    return c;
}

static void shuffle(int *arr, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
    }
}

static double elapsed(struct timespec a, struct timespec b) {
    return (b.tv_sec - a.tv_sec) + (b.tv_nsec - a.tv_nsec) / 1e9;
}

//benchmarks por implementacao//

static Times bench_chaining(const int *order, int table_size) {
    Times t = {0, 0, 0, 0};
    HashTable *ht = hashTable_create(table_size);
    Item **items = malloc(sizeof(Item *) * N);
    for (int i = 0; i < N; i++) items[i] = item_create(i, 'A');

    struct timespec s, e;
    clock_gettime(CLOCK_MONOTONIC, &s);
    for (int i = 0; i < N; i++) hashTable_insert(ht, items[order[i]]);
    clock_gettime(CLOCK_MONOTONIC, &e);
    t.insert = elapsed(s, e);

    clock_gettime(CLOCK_MONOTONIC, &s);
    for (int i = 0; i < N; i++) hashTable_search(ht, order[i]);
    clock_gettime(CLOCK_MONOTONIC, &e);
    t.search_hit = elapsed(s, e);

    clock_gettime(CLOCK_MONOTONIC, &s);
    for (int i = 0; i < N; i++) hashTable_search(ht, N + order[i]);
    clock_gettime(CLOCK_MONOTONIC, &e);
    t.search_miss = elapsed(s, e);

    clock_gettime(CLOCK_MONOTONIC, &s);
    for (int i = 0; i < N; i++) hashTable_delete(ht, order[i]);
    clock_gettime(CLOCK_MONOTONIC, &e);
    t.del = elapsed(s, e);

    hashTable_destroy(ht);
    for (int i = 0; i < N; i++) item_destroy(items[i]);
    free(items);
    return t;
}

static Times bench_open_addressing(const int *order, int table_size) {
    Times t = {0, 0, 0, 0};
    HashTableAberto *ht = hashTableAberto_create(table_size);
    Item **items = malloc(sizeof(Item *) * N);
    for (int i = 0; i < N; i++) items[i] = item_create(i, 'A');

    struct timespec s, e;
    clock_gettime(CLOCK_MONOTONIC, &s);
    for (int i = 0; i < N; i++) hashTableAberto_insert(ht, items[order[i]]);
    clock_gettime(CLOCK_MONOTONIC, &e);
    t.insert = elapsed(s, e);

    clock_gettime(CLOCK_MONOTONIC, &s);
    for (int i = 0; i < N; i++) hashTableAberto_search(ht, order[i]);
    clock_gettime(CLOCK_MONOTONIC, &e);
    t.search_hit = elapsed(s, e);

    clock_gettime(CLOCK_MONOTONIC, &s);
    for (int i = 0; i < N; i++) hashTableAberto_search(ht, N + order[i]);
    clock_gettime(CLOCK_MONOTONIC, &e);
    t.search_miss = elapsed(s, e);

    clock_gettime(CLOCK_MONOTONIC, &s);
    for (int i = 0; i < N; i++) hashTableAberto_delete(ht, order[i]);
    clock_gettime(CLOCK_MONOTONIC, &e);
    t.del = elapsed(s, e);

    hashTableAberto_destroy(ht);
    for (int i = 0; i < N; i++) item_destroy(items[i]);
    free(items);
    return t;
}

static Times bench_double_hashing(const int *order, int table_size) {
    Times t = {0, 0, 0, 0};
    HashTableAbertoDH *ht = hashTableAbertoDH_create(table_size);
    Item **items = malloc(sizeof(Item *) * N);
    for (int i = 0; i < N; i++) items[i] = item_create(i, 'A');

    struct timespec s, e;
    clock_gettime(CLOCK_MONOTONIC, &s);
    for (int i = 0; i < N; i++) hashTableAbertoDH_insert(ht, items[order[i]]);
    clock_gettime(CLOCK_MONOTONIC, &e);
    t.insert = elapsed(s, e);

    clock_gettime(CLOCK_MONOTONIC, &s);
    for (int i = 0; i < N; i++) hashTableAbertoDH_search(ht, order[i]);
    clock_gettime(CLOCK_MONOTONIC, &e);
    t.search_hit = elapsed(s, e);

    clock_gettime(CLOCK_MONOTONIC, &s);
    for (int i = 0; i < N; i++) hashTableAbertoDH_search(ht, N + order[i]);
    clock_gettime(CLOCK_MONOTONIC, &e);
    t.search_miss = elapsed(s, e);

    clock_gettime(CLOCK_MONOTONIC, &s);
    for (int i = 0; i < N; i++) hashTableAbertoDH_delete(ht, order[i]);
    clock_gettime(CLOCK_MONOTONIC, &e);
    t.del = elapsed(s, e);

    hashTableAbertoDH_destroy(ht);
    for (int i = 0; i < N; i++) item_destroy(items[i]);
    free(items);
    return t;
}

int main(void) {
    srand(42);
    int *order = malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) order[i] = i;
    shuffle(order, N);

    FILE *csv = fopen("benchmark_results.csv", "w");
    if (!csv) { fprintf(stderr, "Erro ao criar benchmark_results.csv\n"); return 1; }
    fprintf(csv, "Implementacao,Alpha,TableSize,N,Insert_ms,SearchHit_ms,SearchMiss_ms,Delete_ms,Total_ms\n");

    printf("N = %d chaves, %d repeticoes por configuracao\n\n", N, REPS);
    printf("%-30s %6s %10s %12s %12s %12s %12s %12s\n",
           "Implementacao", "alpha", "tam.tabela", "insert(ms)", "busca-ok(ms)", "busca-x(ms)", "delete(ms)", "total(ms)");

    //silencia qualquer printf de debug do codigo testado durante as medicoes//
    fflush(stdout);
    int saved_stdout = dup(STDOUT_FILENO);
    FILE *devnull = fopen("/dev/null", "w");

    const char *impl_names[] = {
        "Encadeamento Fechado",
        "Enderecamento Aberto",
        "Enderecamento Aberto (DH)"
    };

    for (int a = 0; a < N_ALPHAS; a++) {
        double alpha = ALPHAS[a];
        long table_size = next_prime((long)(N / alpha) + 1);

        for (int impl = 0; impl < 3; impl++) {
            Times sum = {0, 0, 0, 0};

            for (int r = 0; r < REPS; r++) {
                Times t;
                dup2(fileno(devnull), STDOUT_FILENO);
                if (impl == 0) t = bench_chaining(order, (int)table_size);
                else if (impl == 1) t = bench_open_addressing(order, (int)table_size);
                else t = bench_double_hashing(order, (int)table_size);
                fflush(stdout);
                dup2(saved_stdout, STDOUT_FILENO);

                sum.insert += t.insert;
                sum.search_hit += t.search_hit;
                sum.search_miss += t.search_miss;
                sum.del += t.del;
            }

            double ins_ms = (sum.insert / REPS) * 1000.0;
            double hit_ms = (sum.search_hit / REPS) * 1000.0;
            double miss_ms = (sum.search_miss / REPS) * 1000.0;
            double del_ms = (sum.del / REPS) * 1000.0;
            double total_ms = ins_ms + hit_ms + miss_ms + del_ms;

            printf("%-30s %6.2f %10ld %12.3f %12.3f %12.3f %12.3f %12.3f\n",
                   impl_names[impl], alpha, table_size, ins_ms, hit_ms, miss_ms, del_ms, total_ms);
            fflush(stdout);

            fprintf(csv, "%s,%.2f,%ld,%d,%.6f,%.6f,%.6f,%.6f,%.6f\n",
                    impl_names[impl], alpha, table_size, N, ins_ms, hit_ms, miss_ms, del_ms, total_ms);
        }
        printf("\n");
    }

    fclose(devnull);
    close(saved_stdout);
    fclose(csv);
    free(order);

    printf("Resultados salvos em benchmark_results.csv\n");
    return 0;
}