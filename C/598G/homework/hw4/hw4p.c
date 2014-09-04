/* Homework 4: Strassen Matrix Multiplication */
/* Solution by Sergey Kirshner (skirshne@purdue.edu) */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_blas.h>

#define MIN_STRASSEN_SIZE 64

void MatrixMultiplyUser( gsl_matrix mat1, gsl_matrix mat2, gsl_matrix* matprod ) {
  /* Hand-coded standard matrix multiplication */

  int i;
  int j;
  int k;
  int m;
  double sum;
  for(i=0;i<mat1.size1;i++){
    for(j=0;j<mat2.size2;j++){
      for(m=0;m<mat1.size2;m++){
       sum = sum + gsl_matrix_get(&mat1, i, m) * gsl_matrix_get(&mat2, m, j);
      }
      gsl_matrix_set(matprod, i, j, sum);
    }
  }

  return;
}

void MatrixMultiply( gsl_matrix mat1, gsl_matrix mat2, gsl_matrix* matprod ) {
  /* GSL native implementation of matrix multiplication */
  
  gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, 1.0, &mat1, &mat2, 0.0, matprod);

  return;
}

void MatrixMultiplyStrassen( gsl_matrix mat1, gsl_matrix mat2, gsl_matrix* matprod ) {
  /* Strassen matrix multipication */

  if(mat1.size1>64 && mat2.size1>64){	
      gsl_matrix_view A11 = gsl_matrix_submatrix(&mat1, 0, 0, mat1.size1/2, mat1.size2/2);
      gsl_matrix_view A12 = gsl_matrix_submatrix(&mat1, 0, mat1.size2/2, mat1.size1/2, mat1.size2/2);
      gsl_matrix_view A21 = gsl_matrix_submatrix(&mat1, mat1.size1/2, 0, mat1.size1/2, mat1.size2/2);
	  gsl_matrix_view A22 = gsl_matrix_submatrix(&mat1, mat1.size1/2, mat1.size2/2, mat1.size1/2, mat1.size2/2);
      gsl_matrix_view B11 = gsl_matrix_submatrix(&mat2, 0, 0, mat2.size1/2, mat2.size2/2);
	  gsl_matrix_view B12 = gsl_matrix_submatrix(&mat2, 0, mat2.size2/2, mat1.size1/2, mat1.size2/2);
      gsl_matrix_view B21 = gsl_matrix_submatrix(&mat2, mat2.size1/2, 0, mat1.size1/2, mat1.size2/2);
	  gsl_matrix_view B22 = gsl_matrix_submatrix(&mat2, mat2.size1/2, mat2.size2/2, mat1.size1/2, mat1.size2/2);
      gsl_matrix_view C11 = gsl_matrix_submatrix(matprod, 0, 0, (matprod -> size1)/2, (matprod -> size2)/2);
      gsl_matrix_view C12 = gsl_matrix_submatrix(matprod, 0, (matprod -> size2)/2, (matprod -> size1)/2, (matprod -> size2)/2);
      gsl_matrix_view C21 = gsl_matrix_submatrix(matprod, (matprod -> size1)/2, 0, (matprod -> size1)/2, (matprod -> size2)/2);
      gsl_matrix_view C22 = gsl_matrix_submatrix(matprod, (matprod -> size1)/2, (matprod -> size2)/2, (matprod -> size1)/2, (matprod -> size2)/2);

	  gsl_matrix* a = gsl_matrix_calloc(mat1.size1/2, mat1.size2/2);
	  gsl_matrix* b = gsl_matrix_calloc(mat2.size1/2, mat2.size2/2);
	  gsl_matrix* M1 = gsl_matrix_calloc(mat1.size1/2, mat2.size2/2);
      gsl_matrix* M2 = gsl_matrix_calloc(mat1.size1/2, mat2.size2/2);
	  gsl_matrix* M3 = gsl_matrix_calloc(mat1.size1/2, mat2.size2/2);
	  gsl_matrix* M4 = gsl_matrix_calloc(mat1.size1/2, mat2.size2/2);
	  gsl_matrix* M5 = gsl_matrix_calloc(mat1.size1/2, mat2.size2/2);
	  gsl_matrix* M6 = gsl_matrix_calloc(mat1.size1/2, mat2.size2/2);
	  gsl_matrix* M7 = gsl_matrix_calloc(mat1.size1/2, mat2.size2/2);
	  
	  gsl_matrix_memcpy(a, &A11.matrix);
      gsl_matrix_memcpy(b, &B11.matrix);
	  gsl_matrix_add(a, &A22.matrix);
	  gsl_matrix_add(b, &B22.matrix);
      MatrixMultiplyStrassen(*a, *b, M1);
      
	  gsl_matrix_memcpy(a, &A21.matrix);
      gsl_matrix_memcpy(b, &B11.matrix);
	  gsl_matrix_add(a, &A22.matrix);
	  MatrixMultiplyStrassen(*a, *b, M2);

      gsl_matrix_memcpy(a, &A11.matrix);
	  gsl_matrix_memcpy(b, &B12.matrix);
      gsl_matrix_sub(b, &B22.matrix);
	  MatrixMultiplyStrassen(*a, *b, M3);

      gsl_matrix_memcpy(a, &A22.matrix);
      gsl_matrix_memcpy(b, &B21.matrix);
	  gsl_matrix_sub(b, &B11.matrix);
	  MatrixMultiplyStrassen(*a, *b, M4);

	  gsl_matrix_memcpy(a, &A11.matrix);
	  gsl_matrix_memcpy(b, &B22.matrix);
	  gsl_matrix_add(a, &A12.matrix);
	  MatrixMultiplyStrassen(*a, *b, M5);

	  gsl_matrix_memcpy(a, &A21.matrix);
	  gsl_matrix_memcpy(b, &B11.matrix);
	  gsl_matrix_sub(a, &A11.matrix);
	  gsl_matrix_add(b, &B12.matrix);
	  MatrixMultiplyStrassen(*a, *b, M6);

	  gsl_matrix_memcpy(a, &A12.matrix);
	  gsl_matrix_memcpy(b, &B21.matrix);
      gsl_matrix_sub(a, &A22.matrix);
	  gsl_matrix_add(b, &B22.matrix);
	  MatrixMultiplyStrassen(*a, *b, M7);
      
	  gsl_matrix_add(M7, M1);
	  gsl_matrix_add(M7, M4);
	  gsl_matrix_sub(M7, M5);
	  gsl_matrix_memcpy(&C11.matrix, M7);

	  gsl_matrix_add(M5, M3);
	  gsl_matrix_memcpy(&C12.matrix, M5);

	  gsl_matrix_add(M4, M2);
	  gsl_matrix_memcpy(&C21.matrix, M4);

	  gsl_matrix_add(M1, M3);
	  gsl_matrix_add(M1, M6);
	  gsl_matrix_sub(M1, M2);
      gsl_matrix_memcpy(&C22.matrix, M1);

	  gsl_matrix_free(a);
	  gsl_matrix_free(b);
	  gsl_matrix_free(M1);
	  gsl_matrix_free(M2);
	  gsl_matrix_free(M3);
	  gsl_matrix_free(M4);
      gsl_matrix_free(M5);
      gsl_matrix_free(M6);
	  gsl_matrix_free(M7);

  }
  if(mat1.size1 <= 64 && mat2.size1 <= 64){
	   gsl_blas_dgemm (CblasNoTrans, CblasNoTrans, 1.0, &mat1, &mat2, 0.0, matprod);
  }
  
  
  return;
}

void FillMatrix( gsl_matrix* mat ) {
  int i,j;

  for( i=0; i<(int)mat->size1; i++ )
    for( j=0; j<(int)mat->size2; j++ )
      /* Filling in with numbers between -5 and 5 */
      gsl_matrix_set( mat, i, j, drand48()*10.0-5.0 );

  return;
}

void PrintMatrix( gsl_matrix* mat, FILE* f ) {
  int i,j;

  for( i=0; i<(int)mat->size1; i++ ) {
    for( j=0; j<(int)mat->size2; j++ )
      fprintf( f, "%+0.6le ", gsl_matrix_get( mat, i, j ) );
    fprintf( f, "\n" );
  }
}

int main ( int argc, char* argv[] ) {
  char method_type[1000]="blas";          // Product implementation
  char output_filename[1000]="none";      // Output file name
  unsigned int N=8;                       // All matrices NxN
  unsigned int seed=0;                    // RNG seed
  FILE* output_file;
  int i;

  gsl_matrix* mat1;
  gsl_matrix* mat2;
  gsl_matrix* matprod;

  if( argc<2 ) {
    fprintf( stderr, "hw4p: Not enough input arguments!\n" );
    fprintf( stderr, "See \"hw4p --help\" for info\n" );
    exit( -1 );
  }
      
  if( argc==2 && (strcmp(argv[1],"--help")==0 || strcmp(argv[1],"-h")==0) ) {
    fprintf( stdout, "hw4p options:\n" );
    fprintf( stdout, "-m <method type> (user, blas, strassen, default: %s)\n", method_type );
    fprintf( stdout, "-o <output file> (default: %s)\n", output_filename );
    fprintf( stdout, "-n <matrix size> (default: %d)\n", N );
    fprintf( stdout, "-s <random number generator seed> (default: %d)\n", seed );

    fprintf( stdout, "\n-h or --help\n" );
    return 0;
  }

  if( argc%2==0 ) {
    fprintf( stderr, "hw4p: specifications come in pairs\n" );
    return 0;
  }

  /* Processing inputs */
  for( i=1; i<argc; i+=2 ) {
    if( strcmp(argv[i],"-m")==0 ) {
      strcpy(method_type,argv[i+1]);
    } else if( strcmp(argv[i],"-o")==0 ) {
      strcpy(output_filename,argv[i+1]);
    } else if( strcmp(argv[i],"-n")==0 ) {
      N=(unsigned int)atol(argv[i+1]);
    } else if( strcmp(argv[i],"-s")==0 ) {
      seed=(unsigned int)atol(argv[i+1]);
    } else {
      fprintf( stderr, "Unknown option: %s! Exiting\n", argv[i] );
      exit( -1 );
    }
  }

  /* !!!No safety checking!!! */

  /* Checking whether the size is an integer power of 2 */
  fprintf( stdout, "Settings for hw4p:\n" );
  fprintf( stdout, "Matrix multiplication method: %s\n", method_type );
  fprintf( stdout, "Output filename: %s\n", output_filename );
  fprintf( stdout, "Matrix size: %dx%d\n", N, N );
  fprintf( stdout, "Random number generator seed: %d\n", seed );
  
  /* Opening the output file */
  if( strcmp(output_filename,"none")!=0 ) {
    output_file=fopen(output_filename, "w" );
    if( !output_file ) {
      fprintf( stderr, "hw4p: unable to open %s for writing! Exiting.\n", output_filename );
      exit( -1 );
    }
  } else {
    output_file=NULL;
  }
    
  /* Initializing the random number generator */
  srand48(seed);

  /* Initializing the matrices */
  mat1 = gsl_matrix_alloc( N, N );
  mat2 = gsl_matrix_alloc( N, N );
  matprod = gsl_matrix_alloc( N, N );
  assert( mat1 ); assert( mat2 ); assert( matprod );

  /* Initializing the matrices */
  FillMatrix( mat1 );
  FillMatrix( mat2 );

  /* Naive matrix multiplication */
  if( strcmp( method_type, "user" )==0 ){
    /* User implemented matrix multiplication */
    MatrixMultiplyUser( *mat1, *mat2, matprod );
  } else if( strcmp( method_type, "blas" )==0 ) {
    /* BLAS matrix multiplication */
    MatrixMultiply( *mat1, *mat2, matprod );
  } else if( strcmp( method_type, "strassen" )==0 ) {
    MatrixMultiplyStrassen( *mat1, *mat2, matprod );
  } else {
    fprintf( stderr, "Unknown multiplication type! Exiting.\n" );
    exit( -1 );
  }

  if( output_file )
    PrintMatrix( matprod, output_file );

  /* Deallocating matrices */
  gsl_matrix_free( mat1 );
  gsl_matrix_free( mat2 );
  gsl_matrix_free( matprod );

  /* Closing the output file */
  if( output_file )
    fclose( output_file );

  return 0;
}
