/* Written by S.V.N. Vishwanathan */
#include <stdio.h>
#include <stdlib.h>

/*
  malloc: Allocates memory requests size of bytes and returns a pointer
  to the first byte of allocated space
  
  calloc: Allocates space for an array of elements initializes them to
  zero and returns a pointer to the memory

  free: Frees previously allocated space
  
  realloc: Modifies the size of previously allocated space.
*/

/*
  The second pointer example: dynamic array using malloc/calloc
  The difference between Stack and Heap.
*/

int main(){
  
  float a[10];       /* allocated in stack */
  int i;             /* allocated in stack */
  float *b = NULL;   /* b is a "float pointer" which has initial value NULL. 
                       It is allocated in stack. */
  int size;          /* allocated in stack */
  
  printf("Please input a positive integer between 1-100:");
  scanf("%d", &size);
  b = (float *)calloc(size, sizeof(float)); /* now it points to some memory block in the heap */
  
  for (i=0;i<size;i++) { 
    *(b+i) = i; /* the same as "b[i] = i;"  */
  }  
  
  /* print out b's value */
  for (i=0;i<size;i++) { /* print the array elements. */
    printf("b[%d] = %f\n", i, b[i]);
  }
  
  /* find out where is b[0], b[1], ... */
  printf("\nThe address of 'i' is: %p\n", &i);
  printf("The address of 'b' is: %p\n", &b);
  printf("The contents of 'b' are: %p\n", b);
  printf("The address of 'size' is:: %p\n", &size);
  
  printf("Address of b[0]: %p\t  or \t%p\n", &(b[0]), b); /* "&(b[0])" is the same as "b" */
  printf("Address of b[1]: %p\t  or \t%p\n", &(b[1]), (b+1)); /* "&(b[1])" is the same as "b+1" */

  free(b); /* Remember to free the memory you allocated! */
  return 0;
}
