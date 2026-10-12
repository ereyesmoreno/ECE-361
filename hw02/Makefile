# Makefile: ECE 361, Fall 2026, HW2
#
#   make         builds readings
#   make test    builds and runs the unit tests, then the regression test
#   make clean   removes everything the build produced

CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

OBJS       = main.o reading.o stats.o histogram.o
TEST_OBJS  = tests/test_stats.o stats.o

# build rules
readings: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

tests/test_stats: $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS)

# dependencies: each .o on its .c and every header it includes
# (make's built-in rule compiles X.c into X.o with $(CC) $(CFLAGS))
main.o: main.c reading.h stats.h histogram.h
reading.o: reading.c reading.h
stats.o: stats.c stats.h
histogram.o: histogram.c histogram.h
tests/test_stats.o: tests/test_stats.c stats.h
	$(CC) $(CFLAGS) -I. -c -o $@ tests/test_stats.c

test: readings tests/test_stats
	./tests/test_stats
	sh regress.sh

clean:
	rm -f readings $(OBJS) tests/test_stats tests/test_stats.o

.PHONY: test clean
