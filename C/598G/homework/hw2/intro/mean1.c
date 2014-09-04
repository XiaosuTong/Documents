/* 
   This example illustrates how to use multiple C files together, and how to use a header file.

   Compile as
   gcc -c mean1.c 
   gcc -c mean2.c
   gcc -o mean mean1.o mean2.o
*/

#include <stdio.h> 
#include "mean.h"

int main() {

  float x1, x2, amean;
  x1 = 0.5;
  x2 = 0.8;
  
  amean = arithmetic_mean(x1, x2);
  printf("Arithmetic mean of %f and %f is %f \n", x1, x2, amean);
  
  return 0; 
} 
