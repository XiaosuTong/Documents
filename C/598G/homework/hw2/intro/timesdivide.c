/* Learning basic types, reading in and printing variables, declarations */

#include <stdio.h>

int main() {
  /* Declaring variables */
  int n1,n2;

  printf( "Enter first number: " );
  scanf( "%d", &n1 );
  printf( "Enter second number: " );
  scanf( "%d", &n2 );

  printf( "Product: %d*%d=%d\n", n1, n2, n1*n2 );
  printf( "Division: %d/%d=%d\n", n1, n2, n1/n2 );

  return 0;
}
