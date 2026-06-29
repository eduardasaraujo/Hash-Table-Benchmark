CC      = gcc
CFLAGS  = -std=c11 -Wall -Wextra -g -Itests

SRC = \
	src/items/item.c \
	src/lists/doublyLinkedList.c \
	src/hashTable/hashTable.c \
	src/hashTableOA/hashTableAberto.c \
	src/hashTableOADH/hashTableDoubleHashing.c

TEST_SRC = tests/test_suite.c
TEST_BIN = test_suite

.PHONY: all test clean

# 'make' apenas compila a suite de testes (nao ha um executavel principal unico)
all: $(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) $(SRC) -o $(TEST_BIN)

# 'make test' compila e executa os testes
test: $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -f $(TEST_BIN)
