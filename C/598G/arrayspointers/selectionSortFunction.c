#include<stdlib.h>
#include<stdio.h>

/* Selection sort for randomly generated array */

void selectionSort( float *A, const int N ) {
  /* Arguments: Array A of N elements */
  
  /* Index variables */
  int i, j;

  int min_index;
  float temp;

  /* Selection sort */
  for( i=0; i<N-1; i++ )
    {
      min_index=i;
      for( j=i+1; j<N; j++ )
	if( A[j]<A[min_index] )
	  min_index=j;
 
      /* Swapping A[min_index] and A[i] */
      temp=A[min_index];
      A[min_index]=A[i];
      A[i]=temp;
    }

  return;
}

int main() {
  /* Constants */
  const int N=20;

  /* Declaring variable */
  float A[N];   // array

  /* Index variables */
  int i, j;  

  int min_index;

  float temp;
  /* Initializing the array */
  srand48(0); // random number seed initialization

  for( i=0; i<N; i++ )
    A[i]=(float)drand48();

  for( i=0; i<N; i++ )
    printf( "%0.6f\t", A[i] );
  printf( "\n\n" );

  selectionSort( A, N );

  for( i=0; i<N; i++ )
    printf( "%0.6f\t", A[i] );
  printf( "\n\n" );

  return 0;
}
