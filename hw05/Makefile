# ECE 361, HW 5 - Makefile
#   make        builds lock
#   make test   builds and runs the tests
#   make clean  removes everything that was built

CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra

all: lock

lock: main.o lock.o
	$(CC) $(CFLAGS) -o $@ $^

test_lock: tests/test_lock.o lock.o
	$(CC) $(CFLAGS) -o $@ $^

# each object lists the headers it includes
main.o: main.c lock.h
	$(CC) $(CFLAGS) -c -o $@ main.c

lock.o: lock.c lock.h
	$(CC) $(CFLAGS) -c -o $@ lock.c

tests/test_lock.o: tests/test_lock.c lock.h
	$(CC) $(CFLAGS) -c -o $@ tests/test_lock.c

test: test_lock
	./test_lock

clean:
	rm -f lock test_lock *.o tests/*.o

.PHONY: all test clean