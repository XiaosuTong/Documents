#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "R.h"
#include "R_ext/RS.h"
#include "R_ext/BLAS.h"
	
#define DEBUG 0

  
/*
	The best way to read through a library of routines li	ke this is not to start at the top.
	The best way is to start with a function like the HW functions and look up functions 
	when you need to know what they do.
	
	Note there are two structs here row_matrix and col_matrix.
	They are much the same, but they store data differently (row major versus col major).
	In exercise 2, I use row_matrix.
	In exercise 3 and 4, I use col_matrix.
	Thus there are no math routines for row_matrix.
	
	In general "Matrix" in the function name indicates col_matrix arguments.
	While "RMatrix" in the function name indicates row_matrix arguments.

	
	
*/

typedef struct cmatrix{
	double** data;
	int nrows;
	int ncols;
	int allocated_data_storage; 	//1 if allocated the actual arrays holding the values. 0 if did not
	int flat_array_storage; 		//1 if data[0] is the beginning of all the data as from R; 0 if not for example if data[1], data[2] are not contingous one after another.
} col_matrix;

typedef struct rmatrix{
	double** data;
	int nrows;
	int ncols;
	int allocated_data_storage; 	//1 if allocated rows/cols. 0 if did not
	int flat_array_storage; 		//1 if data[0] is the beginning of all the data as from R; 0 if not for example if data[1], data[2] are not contingous one after another.
} row_matrix;


typedef struct ssubset{
	int start_row;
	int start_col;
	int nrows;
	int ncols;
} subset;






void checkDims(col_matrix* m, int actual_row, int actual_col){
	if(actual_row < 0 || actual_row >= m->nrows || actual_col < 0 || actual_col >= m->ncols){
		printf("Error: bad indexes in checkDims requested %d %d nrows %d  ncols %d\n", actual_row,actual_col, m->nrows, m->ncols);
	}
}

void checkEqualDims(col_matrix* dest, col_matrix* src){
	if(dest->nrows != src->nrows || dest->ncols != src->ncols)
		printf("Error: incompatable dimensions in checkEqualDims\n");
}
void checkFlatStorage(col_matrix* m){
	if(m->flat_array_storage != 1){
		printf("Error: not flat_array_storage not 1 and should be.\n");
	}
}












/* MATRIX OPERATIONS */
// In general all these ops respect subset.

/* fill matrix with value */
void fillMatrix(col_matrix* dest, double value){
	int nrows = dest->nrows;
	int ncols = dest->ncols;
	int i;
	int j;
	for(j = 0; j < ncols; ++j){
		for(i = 0; i < nrows; ++i){
			dest->data[j][i] = value;
			
		}
	}

}

/* copies the values inside of a src to dest*/
void equalMatrix(col_matrix* dest, col_matrix* src){
	if(DEBUG) checkEqualDims(dest,src);
	int nrows = dest->nrows;
	int ncols = dest->ncols;
	int j;
	for(j = 0; j < ncols; ++j){
		memcpy(dest->data[j],src->data[j],sizeof(double)*nrows);
	}
}
/*
   set dest equal to a subset of src.
*/
void equalSubsetOf(col_matrix* dest, col_matrix* src, subset s){
	int nrows = dest->nrows;
	int ncols = dest->ncols;
	int i;
	int j;
	int offset_row = s.start_row;
	int offset_col = s.start_col;
	for(j = 0; j < ncols; ++j){
		for(i = 0; i < nrows; ++i){
			dest->data[j][i] = src->data[j+offset_col][i+offset_row];
			
		}
	}

}

// sets dest += src
void plusEqualMatrix(col_matrix* dest, col_matrix* src){
	if(DEBUG) checkEqualDims(dest,src);
	int nrows = dest->nrows;
	int ncols = dest->ncols;
	int i;
	int j;
	for(j = 0; j < ncols; ++j){
		for(i = 0; i < nrows; ++i){
			dest->data[j][i] += src->data[j][i];
			
		}
	}
}
/* sets a subset of dest equal to src*scale */
void plusEqualScaleToSubset(col_matrix* dest, subset s, col_matrix* src, double scale){
	int nrows = src->nrows;
	int ncols = src->ncols;
	int i;
	int j;
	int offset_row = s.start_row;
	int offset_col = s.start_col;
	for(j = 0; j < ncols; ++j){
		for(i = 0; i < nrows; ++i){
			dest->data[j+offset_col][i+offset_row] += scale*src->data[j][i];
			
		}
	}

}
/* set dest equal to itself plus a subset of src times a multiple. */
void plusEqualScaleSubsetOf(col_matrix* dest, col_matrix* src, subset s, double scale){
int nrows = dest->nrows;
	int ncols = dest->ncols;
	int i;
	int j;
	int offset_row = s.start_row;
	int offset_col = s.start_col;
	for(j = 0; j < ncols; ++j){
		for(i = 0; i < nrows; ++i){
			dest->data[j][i] += scale*src->data[j+offset_col][i+offset_row];
			
		}
	}
}

/*  from src s1 + scale*s2 set into dest*/
void addScaleSubsetsOf(col_matrix* src, subset s1, subset s2, double scale, col_matrix* dest){
	equalSubsetOf(dest,src,s1);
	plusEqualScaleSubsetOf(dest, src, s2,scale);
	
}
void matrixMultiply(col_matrix* m1, col_matrix* m2, col_matrix* result){
	int nrows = m1->nrows;
	int ncols = m2->ncols;
	int ninner = m2->nrows;
	int i,j,k;
	double** d1 = m1->data;
	double** d2 = m2->data;
	double** dr = result->data;
	
	for(i = 0; i < nrows; ++i){
		for(j = 0; j < ncols; ++j){
			double accum = 0.0;
			for(k = 0; k < ninner; ++k){
				double m1ik = d1[k][i];
				double m2kj = d2[j][k];
				accum += m1ik*m2kj;
				
			}
			dr[j][i] = accum;
		}
	}
	
}
/* using BLAS library supplied by R.  google BLAS dgemm */
//http://publib.boulder.ibm.com/infocenter/clresctr/vxrx/index.jsp?topic=/com.ibm.cluster.essl44.guideref.doc/am501_hsgemm.html
//pretty good info
//http://r.789695.n4.nabble.com/Problem-using-F77-CALL-dgemm-in-a-package-td3315118.html
void matrixMultiply_dgemm(col_matrix* m1, col_matrix* m2, col_matrix* result){
	//need flat storage to use dgemm
	if(DEBUG){
		checkFlatStorage(m1);
		checkFlatStorage(m2);
		checkFlatStorage(result);
	}
	//args TRANSA TRANSB  L   N   M  ALPHA  A  LDA  B  LDB  BETA  C  LDC
	//fillMatrix(result,0.0);
	double scale = 1.0;
	int dim = 1;
	double pre_scale_result = 0.0;
	F77_CALL(dgemm)("N","N",&result->nrows, &result->ncols,&m1->ncols,&scale,m1->data[0],&m1->nrows,m2->data[0],&m2->nrows,&pre_scale_result, result->data[0],&result->nrows);

}




/* ALLOCATIONS AND READS */

/*
	mallocs a matrix data structure and fills the structure with input arguments
	Really does not do much but set up all the variables in the structure.
*/
col_matrix* allocMatrixFromData(double** data, int nrows, int ncols, int allocated_data_storage, int flat_array_storage){
	col_matrix* m = (col_matrix*) malloc(sizeof(col_matrix));
	m->data = data;
	m->nrows = nrows;
	m->ncols = ncols;
	m->allocated_data_storage = allocated_data_storage;
	m->flat_array_storage = flat_array_storage;
	return(m);
}

row_matrix* allocRMatrixFromData(double** data, int nrows, int ncols, int allocated_data_storage, int flat_array_storage){
	row_matrix* m = (row_matrix*) malloc(sizeof(row_matrix));
	m->data = data;
	m->nrows = nrows;
	m->ncols = ncols;
	m->allocated_data_storage = allocated_data_storage;
	m->flat_array_storage = flat_array_storage;
	return(m);
}
/*
	Allocates a col_matrix data structure from v.
	return is an allocated matrix structure.
	allocates an array of arrays in return->data to offsets in v.
	Much like I mentioned in lab.
	
*/
col_matrix* allocMatrixFromDoubles(double* v, int nrows, int ncols){	
	int dim;
	int stride;
	dim = ncols;
	stride = nrows;
	double** data = (double**) malloc(sizeof(double*)*dim);
	int i;
	for(i = 0; i < dim; ++i){
		data[i] = v + stride*i;
	}
	return(allocMatrixFromData(data,nrows,ncols,0, 1));
}
row_matrix* allocRMatrixFromDoubles(double* v, int nrows, int ncols){	
	int dim;
	int stride;
	dim = nrows;
	stride = ncols;
	double** data = (double**) malloc(sizeof(double*)*dim);
	int i;
	for(i = 0; i < dim; ++i){
		data[i] = v + stride*i;
	}
	return(allocRMatrixFromData(data,nrows,ncols,0, 1));
}
/*
	allocMatrix
input:
      dimensions
return:
	   allocated space for the matrix.  All set up for ya.
*/
col_matrix* allocMatrix(int nrows, int ncols){
	col_matrix* ret = allocMatrixFromDoubles(calloc(nrows*ncols,sizeof(double)),nrows,ncols);
	ret->allocated_data_storage = 1;
	return(ret);
}
/*

	It is a deep copy so it also copies into a new array of doubles.
*/
col_matrix* allocDeepCopy(col_matrix* m){
	int nrows = m->nrows;
	int ncols = m->ncols;
	col_matrix* t = allocMatrix(nrows,ncols);
	equalMatrix(t,m);
	return t;
	
}

col_matrix* allocSubsetCopy(col_matrix* m, subset s){
	col_matrix* t = allocMatrix(s.nrows,s.ncols);
	equalSubsetOf(t,m,s);
	return(t);
	
}
/*
	s1 and s2 must be same size.
	allocates a matrix
	copies s1 into it
	adds s2* scale to it
	returns it 
*/
col_matrix* allocAddScaleSubsetsOf(col_matrix* m, subset s1, subset s2, double scale){
	col_matrix* a = allocSubsetCopy(m,s1);
	plusEqualScaleSubsetOf(a,m,s2,scale);
	return a;
}

/*
	deallocates matrix_t pointer and data.
	if allocated_data_storage is true then it deallocates an array of arrays if flat_array_storage == 0
*/
void deallocMatrix(col_matrix* m){
	int dim;
	if(m->allocated_data_storage){
		if(m->flat_array_storage == 0){ //this is never true in this assignment but since the data is double** I felt it necessary to include...
			dim = m->ncols;
			int i;
			for(i = 0; i < dim; ++i){
				free(m->data[i]);
			}
		}else{
			free(m->data[0]);
		}
	}
	free(m->data);
	free(m);
	
	
}
void deallocRMatrix(row_matrix* m){
	int dim;
	if(m->allocated_data_storage){
		if(m->flat_array_storage == 0){ //this is never true in this assignment but since the data is double** I felt it necessary to include...
			dim = m->nrows;
			int i;
			for(i = 0; i < dim; ++i){
				free(m->data[i]);
			}
		}else{
			free(m->data[0]);
		}
	}
	free(m->data);
	free(m);	
}
/* various print routines */
void printDoubles(double* v, int length){
	int i = 0;
	for(i = 0; i < length; ++i){
		printf("%f ", v[i]);
	}
	printf("\n");
}
void printRMatrix(row_matrix* m){
	int r;
	for(r = 0; r < m->nrows; ++r){
		printDoubles(m->data[r], m->ncols);
	
	}
}
/*
reads in from pf
input:
	--- length: number of doubles to read
output:
	mallocs double array of length length and fills it
	returns it.
*/
double* allocReadDoubles(FILE* pf, int length){
	double* v = (double*) malloc(sizeof(double)*length);
	int i;
	for(i = 0; i < length; ++i){
		float f;
		int nowarning = fscanf(pf,"%f", &f); nowarning++; //hack to get fscanf to stop squaking with -Wall
		v[i] = f;
	}
	return v;
}
/* 
	allocates data and reads a matrix from pf of dim nrows,ncols.
	it assumes the file is row major
	and the return is row major
	ignores new lines
input:
	--- nrows, ncols number of rows and cols to read
output:
	mallocs memory, fills matrix, and
	returns it.
*/
row_matrix* allocReadRMatrix(FILE* pf, int nrows, int ncols){
	double* d = allocReadDoubles(pf,nrows*ncols);
	row_matrix* t = allocRMatrixFromDoubles(d,nrows,ncols);
	t->allocated_data_storage = 1;
	return(t);
}
























/**************************************************************************************************
Implement Problem 1a here by editting gamrand(double alpha)
Input ---
	 alpha - shape parameter 
Return ---
	a pseudo-random observation from gamma(alpha)
Note: this function must generate valid pseudo-random numbers for any alpha between 0 and infinity.
It has in it the code for alpha < 1.  You need to add the code for alpha >= 1.
***************************************************************************************************/
double unifrand(){
	return rand()/(double)RAND_MAX;

}
double exprand(double lambda){
	return -log(unifrand())/lambda;
}
double gamrand(double alpha){
	double x; //value to be returned;
	double accept_prob;
	double e = exp(1);
	double k= e/(e+alpha);
	if(alpha <= 0.0001) 
		printf("Error: invalid alpha: %f\n", alpha);
	if(alpha < 1){
		
		while(1){
			double u1 = unifrand();
			double u2 = unifrand();
			
			if(u1 > k){
				x = -log((1-u1)/k/alpha);
				accept_prob= pow(x,alpha-1);
			
			}else{
				x = pow(u1/k,1/alpha);
				accept_prob = exp(-x);
			}
			if(u2 < accept_prob) 
				break;
		}
	}else{
		double expparam = 1/alpha;
		double m = pow(alpha,alpha-1)*exp((expparam - 1)*alpha);
		while(1){
			x = exprand(expparam);
			accept_prob = pow(x,alpha-1)*exp((expparam-1)*x)/m;
			double u = unifrand();
			if(u < accept_prob){
				break;
			}//otherwise reject and try again
		}
	}
	return x;


}
//wrapper to test from r
void rcall_gamrand(double* v, int* n, double* alpha){
	int i;
	for(i = 0; i < *n; ++i){
		v[i] = gamrand(*alpha);
	}

}
/*************************************************************************************************
Implement bonus problem 1b here or leave blank.
*************************************************************************************************/



/***********************************************************************************************
Implement Problem 2 here. 

You may define helper functions and use them as you wish.
The function should be called "problem2" or "exercise2" but it may call other functions.
Its arguments and return are up to you.
1) It must correctly parse the data.txt file in the same directory that this is executed in.
2) It must load both matrices into memory at once.
3) It must allocate and deallocate memory for those matrixes at some point. (No memory leaks!)
4) You must demonstrate this is done correctly some how (eg print them out or something).
I will adapt to what you do here if you accomplish all 4 of those things.
************************************************************************************************/



void exercise2(){
	char* filename = "data.txt";
	FILE* pf = fopen(filename, "r");
	int dim;
	int i = fscanf(pf,"%d",&dim); i++; //hack to get -Wall warnings to stop showing for fscanf.
	row_matrix* M1 = allocReadRMatrix(pf,dim,dim);
	row_matrix* M2 = allocReadRMatrix(pf,dim,dim);
	printf("Matrix 1:\n");
	printRMatrix(M1);
	printf("Matrix 2:\n");
	printRMatrix(M2);
	
	//no math ops for row_matrix are defined.

	deallocRMatrix(M1);
	deallocRMatrix(M2);

	fclose(pf);
	
	
}







/*********************************************************************************************************************************
Implement problem 3a here by editting squareMatrixMultiply
Instructions:
Write a C function which multiplies two n x n matrices together.
Input ---
	- m1: address of an array of doubles that is a matrix in column major ordering.
	- m2: address of an array of doubles that is a matrix in column major ordering.
	- dim: address of an int that has the dimensions of m1 and m2 (dim by dim)
	- ret: address of an array of doubles that the result will be stored in column major ordering.
			the person calling squareMatrixMultiply is responsible for allocating the memory.
Note: all arguments are pointers so this can be called from R without having to use a wrapper function in C.
If you desire this function can call another function as long as the work is O(n^3) time, but I don't see why you would need to.
*******************************************************************************************************************************/

void squareMatrixMultiply(double* m1, double* m2, int* dim, double* ret){
	//TODO: Implement problem 3a here.
	int d = *dim;
	col_matrix* cm1 = allocMatrixFromDoubles(m1,d,d);
	col_matrix* cm2 = allocMatrixFromDoubles(m2,d,d);
	col_matrix* cret = allocMatrixFromDoubles(ret,d,d);
	matrixMultiply(cm1,cm2,cret);
	deallocMatrix(cm1);
	deallocMatrix(cm2);
	deallocMatrix(cret);
}












//these are specialized for column major viewpoint.  Hence they aren't in the general code above.  Also they may not have value outside of this function.
subset get11Subset(col_matrix* m){
	subset info;
	info.start_row = 0;
	info.start_col = 0;
	info.nrows = m->nrows/2;
	info.ncols = m->ncols/2;
	return(info);
}
subset get21Subset(col_matrix* m){
	subset info;
	info.nrows = m->nrows/2;
	info.ncols = m->ncols/2;
	info.start_row = info.nrows;
	info.start_col = 0;
	return(info);
}
subset get12Subset(col_matrix* m){
	subset info;
	info.nrows = m->nrows/2;
	info.ncols = m->ncols/2;
	info.start_row = 0;
	info.start_col = info.ncols;
	return(info);
}
subset get22Subset(col_matrix* m){
	subset info;
	info.nrows = m->nrows/2;
	info.ncols = m->ncols/2;
	info.start_row = info.nrows;
	info.start_col = info.ncols;
	return(info);
}
void strassenRecursion(col_matrix* A, col_matrix* B, col_matrix* ret);
//the Ms refer to wikipedia
col_matrix* allocCalcM1(col_matrix* A, col_matrix* B,col_matrix* a, col_matrix* b){
	int dim = A->nrows/2;
	col_matrix* m = allocMatrix(dim, dim);
	addScaleSubsetsOf(A,get11Subset(A), get22Subset(A), 1.0,a);
	addScaleSubsetsOf(B,get11Subset(B), get22Subset(B), 1.0,b);
	strassenRecursion(a,b,m);
	return(m);

}

col_matrix* allocCalcM2(col_matrix* A, col_matrix* B,col_matrix* a, col_matrix* b){
	int dim = A->nrows/2;
	col_matrix* m = allocMatrix(dim, dim);
	addScaleSubsetsOf(A,get21Subset(A), get22Subset(A), 1.0,a);
	equalSubsetOf(b,B,get11Subset(B));
	strassenRecursion(a,b,m);
	return(m);
}
col_matrix* allocCalcM3(col_matrix* A, col_matrix* B,col_matrix* a, col_matrix* b){
	int dim = A->nrows/2;
	col_matrix* m = allocMatrix(dim, dim);
	addScaleSubsetsOf(B,get12Subset(B), get22Subset(B), -1.0,b);
	equalSubsetOf(a,A,get11Subset(A));
	strassenRecursion(a,b,m);
	return(m);
	
}
col_matrix* allocCalcM4(col_matrix* A, col_matrix* B,col_matrix* a, col_matrix* b){
	int dim = A->nrows/2;
	col_matrix* m = allocMatrix(dim, dim);
	addScaleSubsetsOf(B,get21Subset(B), get11Subset(B), -1.0,b);
	equalSubsetOf(a,A,get22Subset(A));
	strassenRecursion(a,b,m);
	return(m);
	
}
col_matrix* allocCalcM5(col_matrix* A, col_matrix* B,col_matrix* a, col_matrix* b){
	int dim = A->nrows/2;
	col_matrix* m = allocMatrix(dim, dim);
	addScaleSubsetsOf(A,get11Subset(A), get12Subset(A), 1.0,a);
	equalSubsetOf(b,B,get22Subset(B));
	strassenRecursion(a,b,m);
	return(m);
}
col_matrix* allocCalcM6(col_matrix* A, col_matrix* B,col_matrix* a, col_matrix* b){
	int dim = A->nrows/2;
	col_matrix* m = allocMatrix(dim, dim);
	addScaleSubsetsOf(A,get21Subset(A), get11Subset(A), -1.0,a);
	addScaleSubsetsOf(B,get11Subset(B), get12Subset(B), 1.0,b);
	strassenRecursion(a,b,m);
	return(m);
}
col_matrix* allocCalcM7(col_matrix* A, col_matrix* B,col_matrix* a, col_matrix* b){
	int dim = A->nrows/2;
	col_matrix* m = allocMatrix(dim, dim);
	addScaleSubsetsOf(A,get12Subset(A), get22Subset(A), -1.0, a);
	addScaleSubsetsOf(B,get21Subset(B), get22Subset(B), 1.0, b);
	strassenRecursion(a,b,m);
	return(m);
}
void strassenRecursion(col_matrix* A, col_matrix* B, col_matrix* result){
	if(DEBUG) printf("in strassenRecursion nrows %d ncols %d \n", A->nrows, A->ncols);
	if(A->nrows < 256){
		matrixMultiply_dgemm(A,B,result);
		return;
	}
	int dim = A->nrows/2;
	//a and b are buffers.
	col_matrix* a = allocMatrix(dim,dim); //could avoid this by using chunks of result for storage but I dont have a routine handy.
	col_matrix* b = allocMatrix(dim,dim);
	
	col_matrix* M1 = allocCalcM1(A,B,a,b);
	col_matrix* M2 = allocCalcM2(A,B,a,b);
	col_matrix* M3 = allocCalcM3(A,B,a,b);	
	col_matrix* M4 = allocCalcM4(A,B,a,b);
	col_matrix* M5 = allocCalcM5(A,B,a,b);
	col_matrix* M6 = allocCalcM6(A,B,a,b);
	col_matrix* M7 = allocCalcM7(A,B,a,b);
	
	fillMatrix(result,0.0);
	
	//if(DEBUG) printf("\tafter fill\n");
	
	subset s = get11Subset(result);
	plusEqualScaleToSubset(result,s,M1, 1.0);
	plusEqualScaleToSubset(result,s,M4, 1.0);
	plusEqualScaleToSubset(result,s,M5, -1.0);
	plusEqualScaleToSubset(result,s,M7, 1.0);
	
	s = get12Subset(result);
	plusEqualScaleToSubset(result,s,M3, 1.0);
	plusEqualScaleToSubset(result,s,M5, 1.0);
	

	s = get21Subset(result);
	plusEqualScaleToSubset(result,s,M2, 1.0);
	plusEqualScaleToSubset(result,s,M4, 1.0);

	
	s = get22Subset(result);
	plusEqualScaleToSubset(result,s,M1, 1.0);
	plusEqualScaleToSubset(result,s,M2, -1.0);
	plusEqualScaleToSubset(result,s,M3, 1.0);
	plusEqualScaleToSubset(result,s,M6, 1.0);
	
	//if(DEBUG) printf("\tbeginning dealloc\n");
	deallocMatrix(M1);
	deallocMatrix(M2);
	deallocMatrix(M3);
	deallocMatrix(M4);
	deallocMatrix(M5);
	deallocMatrix(M6);
	deallocMatrix(M7);
	deallocMatrix(a);
	deallocMatrix(b);
	//if(DEBUG) printf("\texiting recursion\n");

}




/********************************************************************************************************************
* problem 4b
* Implement squareMatrixMultiplyStrassen
Input ---
	- m1: address of an array of doubles that is a matrix in column major ordering.
	- m2: address of an array of doubles that is a matrix in column major ordering.
	- dim: address of an int that has the dimensions of m1 and m2 (dim by dim)
	- ret: address of an array of doubles that the result will be stored in column major ordering.
			the person calling squareMatrixMultiply is responsible for allocating the memory.
In this function you set up and call your recursion routine.  It is an interface between your routine in 4a and R in 4c.
**********************************************************************************************************************/
void squareMatrixMultiplyStrassen(double* m1, double* m2, int* dim, double* ret){
	int d = *dim;
	col_matrix* cm1 = allocMatrixFromDoubles(m1,d,d);
	col_matrix* cm2 = allocMatrixFromDoubles(m2,d,d);
	col_matrix* cret = allocMatrixFromDoubles(ret,d,d);
	strassenRecursion(cm1,cm2,cret);
	deallocMatrix(cm1);
	deallocMatrix(cm2);
	deallocMatrix(cret);

}



int main(){
	//for use with valgrind
	exercise2();
	return 0;
}

