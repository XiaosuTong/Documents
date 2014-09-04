/* mergesort.c */
#include<stdio.h>
#define MAXNUMELTS 1000000

double scratch[MAXNUMELTS];   // Globally defined array for copying if needed

/* Header for the functions */
void MergeSort( double*, long );
void MergeSortedArrays( double*, long, long );
void swap( double*, double* );

int main( int argc, char* argv[] ) {
  long n;               // Number of elements to sort
  double A[MAXNUMELTS]; // Array of elements
  long i;  // Index variable
  printf("Please input your size:\n");
  fscanf( stdin, "%ld", &n ); // Reading in the number of array elements

  /* !!! No safety checking !!! */

  /* Reading in n numbers */
  printf("PLease input your data:\n");
  for( i=0; i<n; i++ )
    fscanf( stdin, "%lf", &(A[i]) );

  /* Sorting the array */
  MergeSort( A, n );

  /* Outputting the sorted array */
  for( i=0; i<n; i++ )
    fprintf( stdout, "%0.6lf\t", A[i] );
  fprintf( stdout, "\n" );

  return( 0 );
}

void MergeSort( double* A, long n ) {
  /* MergeSort: array A of n elements.
     Returns sorted in increasing order array A. */
	if(n>1){
	MergeSort(A, (n/2));
	MergeSort((A+n/2), (n-n/2));
    }
	MergeSortedArrays(A, (n/2), (n-n/2));
    return;
}

void MergeSortedArrays( double* A, long n, long m ) {
  /* MergeArrays: array A consisting on n+m elements with each 
     left n and right m elements sorted in increasing order.
     Returns sorted in increasing order array A. */
  int i=0;
  int j=0;
  int f=0;
  int k;
  while((i<n) && (j+n<m+n)){
	  if(A[i]<A[j+n]){
		  scratch[f]=A[i];
		  i++;
		  f++;		
	  }
	  else{
		  scratch[f]=A[j+n];
		  j++;
		  f++;
	  }
  }
  if(i>=n){
	  while( j<n+m ){
		  scratch[f]=A[j+n];
		  j++;
		  f++;
	  }
  }
  else{
	  while( i<n ){
		  scratch[f]=A[i];
		  i++;
		  f++;
	  }
  }
  for(k=0;k<(n+m);k++){
	  A[k]=scratch[k];
	}
  return;
}

void swap( double* d1, double* d2 ) {
  double temp;

  /* This function is not necessarily needed for MergeSort */

  /* Swapping two elements */
  temp=*d1;
  *d1=*d2;
  *d2=temp;

  return;
}
