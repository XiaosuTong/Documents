#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/* 
 *
 * An example of using struct in C.
 *
 */

/* Structures are a shorthand for a collection of variables. */

/* Variables do not have to be of the same type. */

struct vector {
  int n; // number of elements
  double* X;
};

struct matrix {
  int m;  // number of rows
  int n;  // number of elements
  double** A;
};

double vector_norm( struct vector* v ) {
  double norm=0.0;
  int i;

  for( i=0; i<v->n; i++ )
    norm+=v->X[i]*v->X[i];

  return( sqrt(norm) );
}

double vector_norm_alt( struct vector v ) {
  double norm=0.0;
  int i;

  for( i=0; i<v.n; i++ )
    norm+=v.X[i]*v.X[i];

  return( sqrt(norm) );
}


int main(){

  struct vector v1, v2;

  /* Initializing */
  v1.n=2;
  v1.X=(double*)calloc(2,sizeof(double));

  v2.n=2;
  v2.X=(double*)calloc(2,sizeof(double));

  v1.X[0]=3.0;
  v1.X[1]=4.0;

  v2.X[0]=1.0;
  v2.X[1]=2.0;

  printf( "Norm of v1=%0.6lf,\tnorm of v2=%0.6lf\n",
	  vector_norm( &v1 ), vector_norm( &v2 ) );
  printf( "Norm of v1=%0.6lf,\tnorm of v2=%0.6lf\n", 
	  vector_norm_alt( v1 ), vector_norm_alt( v2 ) );

  free(v2.X);
  free(v1.X);

  return 0;
}
