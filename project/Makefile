# Makefile: ECE 361, Fall 2026, Project 23: Grain dryer
#
#   make         builds dryer
#   make clean   removes everything the build produced

CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

OBJS = main.o sensor.o fsm.o store.o aux.o report.o iom361_r4.o

# build rule
dryer: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

# dependencies: each .o on its .c and every header it includes
# (make's built-in rule compiles X.c into X.o with $(CC) $(CFLAGS))
main.o: main.c iom361_r4.h sensor.h fsm.h store.h aux.h report.h
sensor.o: sensor.c sensor.h
fsm.o: fsm.c fsm.h
store.o: store.c store.h
aux.o: aux.c aux.h
report.o: report.c report.h
iom361_r4.o: iom361_r4.c iom361_r4.h

clean:
	rm -f dryer $(OBJS)

.PHONY: clean
