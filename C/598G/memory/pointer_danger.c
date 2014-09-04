/* Originally created by Jian Zhang, modified by Sergey Kirshner */
#include <stdio.h>
#include <stdlib.h>

/* Illustrate some dangers when using pointers */

int main(){
  /* Using static memory via allocation */
  int i = 999;
  int a[4];
  int j = 999;
  int m[2][4];
  int *b = a;
  int k;

  /* initialize array using either "a" or "b" */
  for (k=0; k<4; k++){
    a[k] = k+1;
  }

  /* print out the addresses of all variables */
  /* What is the order of allocation? */
  printf("%p, %p, %p, %p, %p, %p\n", &k, &b, m, &j, a, &i );
  
  /* danger: invalid read */
  printf("a[4]=%d\n", a[4]);
  printf("a[4]=%d\n", *(b+4));
  
  /* danger: invalid write */
  printf("before change a[4]: i = %d\n", i);
  *(b+4) = -1;
  printf("after change a[4]: i = %d\n", i);

  /* danger: memory leak */
  b = calloc(10, sizeof(int));
  /* Where is b allocated? */
  printf( "%p\n", b );
  return 0;
}
