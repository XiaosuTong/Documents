 #include <stdio.h>
 #include <assert.h>
 #include <string.h>
 #include <gsl/gsl_linalg.h>
 #include <gsl/gsl_matrix.h>
 #include <gsl/gsl_blas.h>

 void MatrixMultiplyStrassen( gsl_matrix mat1, gsl_matrix mat2, gsl_matrix* matprod ) {
   /* Strassen matrix multipication */
 
   if(mat1.size1>64 && mat2.size1>64){
       gsl_matrix_view A11 = gsl_matrix_submatrix(&mat1, 0, 0, mat1.size1/2, mat1.size2/2);
       gsl_matrix_view A12 = gsl_matrix_submatrix(&mat1, 0, mat1.size2/2, mat1.size1/2, mat1.size2/2);
       gsl_matrix_view A21 = gsl_matrix_submatrix(&mat1, mat1.size1/2, 0, mat1.size1/2, mat1.size2/2);
       gsl_matrix_view A22 = gsl_matrix_submatrix(&mat1, mat1.size1/2, mat1.size2/2, mat1.size1/2, mat1.size2/    2);
       gsl_matrix_view B11 = gsl_matrix_submatrix(&mat2, 0, 0, mat2.size1/2, mat2.size2/2);
       gsl_matrix_view B12 = gsl_matrix_submatrix(&mat2, 0, mat2.size2/2, mat1.size1/2, mat1.size2/2);
       gsl_matrix_view B21 = gsl_matrix_submatrix(&mat2, mat2.size1/2, 0, mat1.size1/2, mat1.size2/2);
       gsl_matrix_view B22 = gsl_matrix_submatrix(&mat2, mat2.size1/2, mat2.size2/2, mat1.size1/2, mat1.size2/    2);
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


 void Matrix(double *x, int *nrx, int *ncx, double *y, int *nry, int *ncy, double *ans ){
 
  int i;
  int j;
  gsl_matrix* mat1;
  gsl_matrix* mat2;
  gsl_matrix* matprod;
 
  mat1 = gsl_matrix_alloc(*nrx, *ncx);
  mat2 = gsl_matrix_alloc(*nry, *ncy);
  matprod = gsl_matrix_alloc(*nrx, *ncy);
 
  for(i=0;i<*ncx;i++){
      for(j=0;j<*nrx;j++){
          gsl_matrix_set(mat1, j, i, x[i*(*nrx)+j]);
      }
  }
 
  for(i=0;i<*ncy;i++){
      for(j=0;j<*nry;j++){
          gsl_matrix_set(mat2, j, i, y[i*(*nry)+j]);
      }
  }
  MatrixMultiplyStrassen(*mat1, *mat2, matprod);
 
  for(i=0;i<*ncy;i++){
      for(j=0;j<*nrx;j++){
          ans[i*(*nrx)+j]=gsl_matrix_get(matprod, j, i);
      }
  }

 }
