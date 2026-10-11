Estefani Reyes Moreno
ECE 361 - Homework 2 

**Part 1: What I would change from the hw02_starter**
1. Because no global variables are allowed, the current ones in readings.c would have to be changed. That would be ticks, temps, hums, count, skipped, and threshold as local variables in the main program. The readings.c file in the started also need to be split up into different pieces (reading, stats, and histogram).

2. Looking through the starter code, here's the split of what each module might include:
MAIN
- MAX_READINGS
- if statements under int main
- results (prints and returns) - readings, skipped, temperature, humidity

READING
- LINE_LEN
- int main(int argc, char *argv[])
    char line[LINE_LEN]

STATS
- max_temp (int i) {
- min and mean loop
- humiditity (min, max, mean loop)
- longest run loop

HISTOGRAM
- NUM_BINS
- BIN_WIDTH
