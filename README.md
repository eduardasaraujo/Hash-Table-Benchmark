# Hash Table Benchmark

Implementação e comparação de desempenho entre três abordagens de **Hash Table** em C, desenvolvida para a disciplina de Estrutura de Dados:

- **Encadeamento fechado** — colisões resolvidas com lista duplamente encadeada
- **Endereçamento aberto** — colisões resolvidas com sondagem linear
- **Endereçamento aberto (Double Hashing)** — colisões resolvidas com sondagem por duplo hashing

O projeto inclui testes unitários, um comparativo de tempo de execução das suites de teste e um benchmark de desempenho (inserção, busca e remoção) variando o fator de carga, com geração automática de planilhas Excel a partir dos resultados.

## Estrutura

```
src/
├── hashTable/       # Hash Table (encadeamento fechado)
├── hashTableOA/      # Hash Table (endereçamento aberto - sondagem linear)
├── hashTableOADH/     # Hash Table (endereçamento aberto - double hashing)
├── lists/             # Lista duplamente encadeada (usada no encadeamento fechado)
└── items/             # TAD Item composto por key e value

tests/
├── hashTable/         # Testes da hash table de encadeamento fechado
├── hashTableOA/        # Testes da hash table de endereçamento aberto
├── hashTableDH/         # Testes da hash table de double hashing
├── lists/                # Testes da lista duplamente encadeada
├── test_suite.c           # Suite geral de testes (make test)
├── test_suite_timed.c       # Suite de testes com medição de tempo (make timing)
└── hashtable_benchmark.c     # Benchmark de desempenho (make benchmark)

tools/
├── build_benchmark_excel.py  # Gera benchmark_results.xlsx a partir do CSV
└── build_timing_excel.py     # Gera tests_timing.xlsx a partir do CSV
```

## Como usar

```bash
# Build (compila apenas a suite de testes)
make

# Executa os testes unitários
make test

# Executa a suite de testes medindo o tempo de execução
make timing

# Executa o benchmark de desempenho (insert, search, delete)
make benchmark

# Remove os binários e CSVs gerados
make clean
```

> Requer Docker ou Dev Container configurado (ver `.devcontainer/`).

### Gerando as planilhas de resultados

Após rodar `make timing` e/ou `make benchmark`, é possível gerar as planilhas formatadas em Excel a partir dos CSVs:

```bash
pip install openpyxl

python tools/build_timing_excel.py      # gera tests_timing.xlsx
python tools/build_benchmark_excel.py   # gera benchmark_results.xlsx
```

Resultados

Após rodar o benchmark (make benchmark) e a comparação de tempo (make timing) diversas vezes, com diferentes fatores de carga (alpha), observei:


Para fatores de carga baixos a moderados (α até ~0.70), o endereçamento aberto (sondagem linear) costuma ser a implementação mais rápida no total, superando o encadeamento fechado por uma margem considerável.
O encadeamento fechado tende a manter um desempenho mais estável e previsível conforme α aumenta, já que cada posição da tabela aponta para sua própria lista, mas paga o preço de mais alocações dinâmicas na inserção.
O custo de busca por chave ausente (search miss) cresce de forma acentuada nas estratégias de endereçamento aberto à medida que α se aproxima de 1, especialmente no double hashing, pois mais sondagens são necessárias até encontrar uma posição vazia.
Em fatores de carga muito altos (α perto de 0.95, tabela quase cheia), o encadeamento fechado costuma voltar a ser competitivo e, em algumas execuções, até supera o double hashing no tempo total — evidenciando a degradação do endereçamento aberto sob alta taxa de ocupação.
Os valores absolutos variam de execução para execução (dependem de carga da máquina, hardware e aleatoriedade das chaves geradas), mas essas tendências relativas entre as três implementações se repetiram de forma consistente nos testes que fizemos.


Os dados brutos de cada execução ficam salvos em tests_timing.csv / tests_timing.xlsx e benchmark_results.csv / benchmark_results.xlsx, caso queira inspecionar números específicos.
