/* By S.V.N. Vishawanathan */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "linked_list.h"



int main(void){
  sll list;
  int i;
  node* found;

  sll_initialize( &list );
  for( i = 5; i > 0; i-- ){
    sll_add( &list, i );
  }
  sll_print( list );
  printf("Number of elements: %d \n", sll_count(list));
  
  sll_addtotail( &list, 10 );
  sll_print(list);
  printf("Number of elements: %d \n", sll_count(list));

  if( (found=sll_find(list,5)) )
    printf( "%d is an element of the list\n", found->data );
  else
    printf( "5 is not found in the list\n" );

  if( (found=sll_find(list,6)) )
    printf( "%d is an element of the list\n", found->data );
  else
    printf( "6 is not found in the list\n" );


  sll_empty( &list );

  return 0;
}
