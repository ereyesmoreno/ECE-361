CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -g
OBJS = bits.o status.o

all: $(OBJS)

%.o: %.c bits.h status.h
	$(CC) $(CFLAGS) -c $< -o $@

tests/test_bits: tests/test_bits.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

test: tests/test_bits
	./tests/test_bits

clean:
	rm -f *.o tests/*.o tests/test_bits
.PHONY: all test clean
