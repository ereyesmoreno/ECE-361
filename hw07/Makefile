CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

# make: build balance (the default target)
all: balance

balance: balance.c istack.c istack.h
	$(CC) $(CFLAGS) -o balance balance.c istack.c

tests/test_istack: tests/test_istack.c istack.c istack.h
	$(CC) $(CFLAGS) -I. -o tests/test_istack tests/test_istack.c istack.c

# make test: unit tests, then the regression test
test: balance tests/test_istack
	./tests/test_istack
	sh regress.sh

# make memcheck: rebuild everything with the sanitizers, then run make test
memcheck: clean
	$(MAKE) CFLAGS="$(CFLAGS) -fsanitize=address,undefined" test

# make clean: remove the built programs
clean:
	rm -f balance tests/test_istack istack.o

.PHONY: all test memcheck clean