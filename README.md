# trios-prime

Implementação de duas abordagens de **Hash Table** em C, desenvolvida para a disciplina de Estrutura de Dados:

- **Encadeamento fechado** — colisões resolvidas via lista duplamente encadeada
- **Endereçamento aberto** — 

## Estrutura

```
src/
├── hashTable/       # Hash Table (encadeamento fechado)
├── hashTableOA/     # Hash Table (endereçamento aberto)
├── lists/           # Lista duplamente encadeada
└── items/           # TAD Item composto por key e value

tests/
├── hashTable/
└── lists/
```

## Como usar

```bash
# Build
make

# Testes
make test
```

> Requer Docker ou Dev Container configurado.

## Integrantes

- Caio Maia — [@caiopmaia](https://github.com/caiopmaia)
- Eduarda Araújo — [@eduardasaraujo1](https://github.com/eduardasaraujo1)
- Maria Júlia S. Carvalho — [@majulisc](https://github.com/majulisc)
- Heitor Campos de Souza Cavalcanti — [@heitorcsc](https://github.com/heitorcsc)
