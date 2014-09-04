#include <stdio.h> 
/* Learning declarations of functions */

float arithmetic_mean(float x, float y){
  float z;
  z = (x+y)/2.0;
  return z;
}
  
int main() {

  float x1, x2, amean;
  x1 = 0.5;
  x2 = 0.8;
  
  amean = arithmetic_mean(x1, x2);
  printf("Arithmetic mean of %f and %f is %f \n", x1, x2, amean);
  
  return 0; 
} 
