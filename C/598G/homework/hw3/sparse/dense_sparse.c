/* By S.V.N. Vishwanathan */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

/* Define and work with a dense vector */
struct dvec{
  double* val;
  int dim;
};

typedef struct dvec dvec;

/* Define and work with a sparse vector */
struct pair{
  int idx;
  double val;
};

typedef struct pair pair;

struct svec{
  pair* p;
  int nnz;
  int dim;
};

typedef struct svec svec;

/* Print out a dense vector a */
void dprint(dvec a){
  int i;
  for(i = 0; i < a.dim; i++)
    printf("%f ", a.val[i]);
  printf("\n");
  return;
}

/* Print out a sparse vector a */
void sprint(svec a){
  int i;
  int j = 0;
  for(i = 0; i < a.dim; i++){
    if((j < a.nnz) && (i == a.p[j].idx)){
      printf("%f ", a.p[j].val);
      j++;
    }else{
      printf("0.0 ");
    }
  }
  printf("\n");
  return;
}


int main(void){
  
  int i = 0, j = 0;
  dvec da;
  svec sa;
  
  da.dim = 10;
  da.val = (double*) calloc(da.dim, sizeof(double));
  
  /* Fill a with random numbers between 0 and 1.0*/
  srand48(12390);
  for(i = 0; i < da.dim; i++)
    da.val[i] = drand48();
  printf("da:\n");
  dprint(da);
 
  sa.dim = 10;
  sa.nnz = 5;

  sa.p = (pair *) calloc(sa.nnz, sizeof(pair));

  for(i = 0; i < sa.nnz; i++){
    sa.p[i].val = drand48();
    sa.p[i].idx =  j;
    j += 2;
  }
  
  printf("sa:\n");
  sprint(sa);

  free(da.val);
  free(sa.p);
  
  return( 0 );
}
