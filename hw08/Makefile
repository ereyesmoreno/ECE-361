CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g -I.
SAN    = -fsanitize=address,undefined -fno-omit-frame-pointer

all: test_bst

test_bst: tests/test_bst.c bst.c bst.h
	$(CC) $(CFLAGS) -o $@ tests/test_bst.c bst.c

test: test_bst
	./test_bst

memcheck: tests/test_bst.c bst.c bst.h
	$(CC) $(CFLAGS) $(SAN) -o test_bst_san tests/test_bst.c bst.c
	./test_bst_san

clean:
	rm -f test_bst test_bst_san treestats

.PHONY: all test memcheck clean
