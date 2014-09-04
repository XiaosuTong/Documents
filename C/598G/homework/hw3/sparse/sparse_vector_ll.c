/* By S.V.N. Vishwanathan */
/* Modified by Sergey Kirshner */

#include "ll_sv.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

struct svec {
  int dim;
  node* list;
};

typedef struct svec svec;

int main(void){
  
  int i = 0, j = 9, nnz = 5;
  svec sa;
  
  
  /* Fill a with random numbers between 0 and 1.0*/
  srand48(12390);
 
  sa.dim = 10;
  sa.list = NULL;
  
  for(i = 0; i < nnz; i++){
    sll_add(&sa.list, j, drand48());
    j -= 2;
    printf("sa:\n");
    sll_print( sa.list );
  }
  printf( "Number of non-zero components: %d\n", sll_count( sa.list ) );

  sll_empty(sa.list);
  
  return( 0 );
}
