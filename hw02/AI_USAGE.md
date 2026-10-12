Estefani Reyes Moreno
ECE 361 - Homework 2 

Tools used: Claude

I had some trouble getting started with the started readings.c code, so when I got stuck with specific pieces I used Claude as support. I got stuck on the temperature loops and for some lines, I wasn't sure what module would utilize them. I also used it to review some of the definitions of C, for example argv and argc. Once I reviewed each line and had an idea of what arguments or lines would belong to what module, I used Claude to double check my thinking. For the temperature reading parts, I also used examples from Claude to better understand by visualizing with numbers.

For the Makefile, I used Claude to create it as I went through each module.

When I started on the recursive maximum, I followed the factorial example
from the lecture slides too closely. Factorial only takes one number, n, and
calls itself with n - 1, so I set up stats_max the same way. My recursive
call only made the number smaller and I left out the array, so I wasn't
getting what I needed. I was also missing some arguments when I called it
from main.c, which made my temperature code fail.

I figured it out by comparing my calls to the declaration in stats.h,
float stats_max(const float a[], int n), and to the array recursion example
on slide 17. The function needs both the array and its length, and the
recursive call has to make both smaller at the same time: stats_max(a + 1,
n - 1). In main.c I had to call it as stats_max(temps, count). After fixing
that, make test passed.