#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/* 
 *
 * An example of using struct in C: use "typedef" to simplify
 *
 */

typedef double real;

struct vector {
  int n; // number of elements
  real* X;
};

typedef struct vector VEC;

struct matrix {
  int m;  // number of rows
  int n;  // number of columns
  real** A;
};

typedef struct matrix MAT;

VEC* matrix_vector_multiply( MAT* M, VEC* v ) {
  VEC* vo=NULL;    // Output vector
  /* Index variables */
  int i,j;

  /* Checking whether dimensions match */
  if( M->n==v->n ) {
    /* Dimensions match */
    /* Initializing the output vector */
    vo=(VEC*)malloc(sizeof(VEC));
    /* Number of elements */
    vo->n=M->m;
    /* Array */
    vo->X=(real*)calloc(vo->n,sizeof(real));
    /* Computing the values */
    for( i=0; i<M->m; i++ )
      {
	vo->X[i]=0.0;
	for( j=0; j<M->n; j++ )
	  vo->X[i]+=M->A[i][j]*v->X[j];
      }
  }


  return( vo );
}

real vector_norm( VEC* v ) {
  real norm=0.0;
  int i;

  for( i=0; i<v->n; i++ )
    norm+=v->X[i]*v->X[i];

  return( sqrt(norm) );
}

real vector_norm_alt( VEC v ) {
  real norm=0.0;
  int i;

  for( i=0; i<v.n; i++ )
    norm+=v.X[i]*v.X[i];

  return( sqrt(norm) );
}


int main(){

  VEC v1, v2;
  MAT M;

  VEC* v;

  /* Index variables */
  int i,j;

  /* Initializing */
  v1.n=2;
  v1.X=(real*)calloc(2,sizeof(real));

  v2.n=2;
  v2.X=(real*)calloc(2,sizeof(real));

  v1.X[0]=3.0;
  v1.X[1]=4.0;

  v2.X[0]=1.0;
  v2.X[1]=2.0;

  M.m=3;
  M.n=2;
  M.A=(real**)calloc(M.m,sizeof(real*));
  for( i=0; i<M.m; i++ )
    M.A[i]=(real*)calloc(M.n,sizeof(real));

  /* Initializing the matrix */
  for( i=0; i<M.m; i++ )
    for( j=0; j<M.n; j++ )
      M.A[i][j]=(double)(i*M.n+j);

  printf( "Multiplying matrix M:\n" );
  for( i=0; i<M.m; i++ )
    {
      for( j=0; j<M.n; j++ )
	printf( "%0.6lf ", M.A[i][j] );
      printf( "\n" );
    }
  
  printf( "by a vector v1:\n" );
  for( i=0; i<v1.n; i++ )
    printf( "%0.6lf\n", v1.X[i] );

  v=matrix_vector_multiply( &M, &v1 );
  if( v ) {
    /* Not null */
    printf( "resulting in v:\n" );
    for( i=0; i<v->n; i++ )
      printf( "%0.6lf\n", v->X[i] );

    /*
      printf( "Norm of v1=%0.6lf,\tnorm of v2=%0.6lf\n",
      vector_norm( &v1 ), vector_norm( &v2 ) );
      printf( "Norm of v1=%0.6lf,\tnorm of v2=%0.6lf\n", 
      vector_norm_alt( v1 ), vector_norm_alt( v2 ) );
    */
    
    /* Deallocating the resulting vector */
    free(v->X);
    free(v);
  } else {
    perror( "Dimensions of the matrix and the vector do not match!\n" );
  }

  for( i=0; i<M.m; i++ )
    free(M.A[i]);
  free(M.A);

  free(v2.X);
  free(v1.X);

  return 0;
}


