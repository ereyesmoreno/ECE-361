CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

all: ptr.o tests/test_ptr

ptr.o: ptr.c ptr.h
	$(CC) $(CFLAGS) -c ptr.c -o ptr.o

tests/test_ptr.o: tests/test_ptr.c ptr.h
	$(CC) $(CFLAGS) -I. -c tests/test_ptr.c -o tests/test_ptr.o

tests/test_ptr: tests/test_ptr.o ptr.o
	$(CC) $(CFLAGS) -o tests/test_ptr tests/test_ptr.o ptr.o

test: tests/test_ptr
	./tests/test_ptr

clean:
	rm -f ptr.o tests/test_ptr.o tests/test_ptr

.PHONY: all test clean