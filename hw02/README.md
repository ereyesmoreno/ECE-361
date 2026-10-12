Estefani Reyes Moreno
ECE 361 - Homework 2 

1. Because no global variables are allowed, the current ones in readings.c would have to be changed. That would be ticks, temps, hums, count, skipped, and threshold as local variables in the main program and passed as parameters to the function that needs them. The readings.c file also needs to be split up into different pieces (reading, stats, and histogram).

2. max_temp(int i) only works on the global temps array, because it reads temps and count directly. It will need to be changed to a recursive function that takes an array input and length: const float a[] and int n. This will allow it to work for temperature and humidity.

3. The minimum, maximum, and mean loop appears two times and can be altered to be one function.

4. MODULE DIAGRAM
                        -------------
                        |   Main    |
                        -------------
                        V           V
            --------------------------------------
            |   Reading   |  Stats  | Histogram  |
            --------------------------------------

5. The smaller pieces used in only one file can be become static helped functions, like checking whether a line is blank or a comment, and finding which bin the temperature goes to in the histogram.
   
7. Looking through the starter code, here's the split of what each module might include:
MAIN
- MAX_READINGS (size of main's arrays)
- int main(int argc, char *argv[]): command line checks usage error (if argc > 2) and if argc == 2 then read the threshold with strtof 
- arrays and variables global in starter changed to local
- results (prints and returns): readings, skipped, temperature, humidity
- printing the longest run (if (best == 0)):
- calling reading, stats, and histogram

READING
- LINE_LEN
- char line[LINE_LEN]
- while (fgets()) loop
- give count and skipped results to main

STATS
- max_temp (int i): rewritten as recursive stats_max(a, n)
- minimum and mean loop
- humidity (min, max, mean loop): replaced by adding the same functions on hums
- longest run loop: gives back the run's length and where it starts results

HISTOGRAM
- NUM_BINS
- BIN_WIDTH
- the loops that counts each temperature into a bin
- the loop that prints each non-empty bin: the range, th *s, and the count
