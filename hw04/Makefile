# Makefile: ECE 361, Fall 2026, Homework 4
#
#   make         builds events
#   make test    builds and runs the unit tests
#   make clean   removes everything the build produced

CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

# build rule for the program
events: events.o tally.o
	$(CC) $(CFLAGS) -o $@ events.o tally.o

# build rule for the tests
tests/test_tally: tests/test_tally.o tally.o
	$(CC) $(CFLAGS) -o $@ tests/test_tally.o tally.o

# dependencies: each .o on its .c and every header it includes
# (make's built-in rule compiles X.c into X.o with $(CC) $(CFLAGS))
events.o: events.c tally.h
tally.o: tally.c tally.h
tests/test_tally.o: tests/test_tally.c tally.h

test: tests/test_tally
	./tests/test_tally

clean:
	rm -f events events.o tally.o tests/test_tally tests/test_tally.o

.PHONY: test clean
