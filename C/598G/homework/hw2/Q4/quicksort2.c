/* mergesort.c */
#include<stdio.h>
#include<stdlib.h>

#define MAXNUMELTS 1000000

/* Header for the functions */
void QuickSort( double*, long );
void swap( double*, double* );

int main( int argc, char* argv[] ) {
  long n;               // Number of elements to sort
  double A[MAXNUMELTS]; // Array of elements
  long i;               // Index variable
  FILE *fr;
  int k;
  /* Initializing the double random number generator */
  srand48(0);
  fr=fopen("unsorted","rt");
  fscanf( fr, "%ld", &n ); // Reading in the number of array elements

  /* !!! No safety checking !!! */

  /* Reading in n numbers */

  for( i=0; i<n; i++ )
    fscanf( fr, "%lf", &(A[i]) );
  fclose(fr);
  /* UNCOMMENT FOR PROBLEM 4c */
 for( k=0; k<100; k++ ){
  /* Sorting the array */
  QuickSort( A, n ); 

  /* Outputting the sorted array */
  for( i=0; i<n; i++ )
    fprintf( stdout, "%0.6lf\t", A[i] );
  fprintf( stdout, "\n" );
 }
  return( 0 );
	
}

void QuickSort( double* A, long n ) {
  /* MergeSort: array A of n elements.
     Returns sorted in increasing order array A. */
  int i=0;
  int j;
  int r=n*drand48();
  if(n<=1){
	  return;
  }
  else{
  swap((A+r), (A+n-1));
  for(j=0;j<n-1;j++){
	  if(A[j]<=A[n-1]){
		  swap((A+j), (A+i));
		  i++;
	  }
  }
  swap((A+n-1), (A+i));
  QuickSort((A+i), (n-i));
  QuickSort(A, i);
  }
  return;
}

void swap( double* d1, double* d2 ) {
  /* Swapping the values in locations d1 and d2 */
  double temp;

  /* Swapping two elements */
  temp=*d1;
  *d1=*d2;
  *d2=temp;

  return;
}
