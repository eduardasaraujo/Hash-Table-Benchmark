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

TIMING_SRC = tests/test_suite_timed.c
TIMING_BIN = test_suite_timed
TIMING_CSV = tests_timing.csv

.PHONY: all test timing clean

# 'make' apenas compila a suite de testes
all: $(TEST_BIN)

$(TEST_BIN): $(TEST_SRC) $(SRC)
	$(CC) $(CFLAGS) $(TEST_SRC) $(SRC) -o $(TEST_BIN)

# 'make test' compila e executa os testes
test: $(TEST_BIN)
	./$(TEST_BIN)

# 'make timing' compila e executa a comparação de tempo
$(TIMING_BIN): $(TIMING_SRC) $(SRC)
	$(CC) $(CFLAGS) $(TIMING_SRC) $(SRC) -o $(TIMING_BIN)

timing: $(TIMING_BIN)
	./$(TIMING_BIN)

clean:
	rm -f $(TEST_BIN) $(TIMING_BIN) $(TIMING_CSV)