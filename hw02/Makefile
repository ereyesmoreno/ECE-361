# Makefile: ECE 361, Fall 2026, HW2
#
#   make         builds readings
#   make test    builds and runs the tests
#   make clean   removes everything the build produced
#
# A rule is    target: prerequisites
#              <TAB>recipe
# make rebuilds a target when any prerequisite is newer than it.
# Recipe lines MUST start with a Tab, not spaces.
#
# This file grows with you. As you create each module, uncomment its lines
# (remove the leading "# "), then run make and make test again.

CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

# ---- the object files that make up the program ----------------------------
# Step 1 (stats):     add stats.o
# Step 2 (histogram): add histogram.o
# Step 3 (reading):   add reading.o
# OBJS = main.o
OBJS = main.o stats.o
# OBJS = main.o stats.o histogram.o
# OBJS = main.o stats.o histogram.o reading.o

# link the program from its object files   ($@ = the target, readings)
readings: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# ---- dependencies: each .o on its .c and EVERY header that .c includes ----
# No recipe needed: make's built-in rule compiles X.c into X.o using
# $(CC) $(CFLAGS). When main.c starts to #include a header, add it here.
main.o: main.c stats.h
stats.o: stats.c stats.h
# histogram.o: histogram.c histogram.h
# reading.o: reading.c reading.h

# ---- unit tests (Step 5): uncomment once tests/test_stats.c exists --------
# tests/test_stats: tests/test_stats.o stats.o
# 	$(CC) $(CFLAGS) -o $@ tests/test_stats.o stats.o
#
# # the test is in tests/ but includes stats.h from here: -I. adds this folder
# tests/test_stats.o: tests/test_stats.c stats.h
# 	$(CC) $(CFLAGS) -I. -c -o $@ tests/test_stats.c

# ---- make test ---------------------------------------------------------------
# Step 5: change the first line to   test: readings tests/test_stats
#         and add the line           ./tests/test_stats   above sh regress.sh
test: readings
	sh regress.sh

clean:
	rm -f readings *.o tests/test_stats tests/*.o

.PHONY: test clean