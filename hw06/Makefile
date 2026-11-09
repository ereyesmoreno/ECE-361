# ECE 361, HW 6 - Makefile

CC       = gcc
CFLAGS   = -std=c11 -Wall -Wextra -g
# -I. lets tests/ #include the headers in hw06/
CPPFLAGS = -I.
# -lm links the math library, for round()
LDLIBS   = -lm

# the program: every module plus the hardware model
OBJS      = main.o sensor.o panel.o scenario.o iom361_r4.o
# the unit tests: the same modules, but the test file instead of main.o
TEST_OBJS = tests/test_hw06.o sensor.o panel.o scenario.o iom361_r4.o

replay: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDLIBS)

tests/test_hw06: $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $(TEST_OBJS) $(LDLIBS)

# each .o: its .c, then every header it #includes
main.o:            main.c iom361_r4.h sensor.h panel.h scenario.h
sensor.o:          sensor.c sensor.h iom361_r4.h
panel.o:           panel.c panel.h iom361_r4.h
scenario.o:        scenario.c scenario.h
iom361_r4.o:       iom361_r4.c iom361_r4.h
tests/test_hw06.o: tests/test_hw06.c iom361_r4.h sensor.h panel.h scenario.h

# make test: the unit tests first, then the regression test
test: replay tests/test_hw06
	./tests/test_hw06
	./regress.sh

clean:
	rm -f *.o tests/*.o replay tests/test_hw06

.PHONY: test clean

