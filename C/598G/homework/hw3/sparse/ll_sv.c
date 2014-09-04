/* By S.V.N. Vishawanathan, modified by Sergey Kirshner */
/* Implementation of a singly linked list for sparse vectors */

#include "ll_sv.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Adding a node to the beginning of a singly linked list */
void sll_add( node** head, int index, double value ) {
  node* new_node=(node*)malloc(sizeof(node)); // creating new element
  assert(new_node!=NULL); // making sure memory is allocated
  new_node->index=index;
  new_node->value=value;
  new_node->next=*head; // making the old head element second
  *head=new_node; // making the new element head

  return;
}

/* Empty the linked list */
void sll_empty( node* head ) {
  node* tmp;
  while( head!=NULL ) {
    /* Elements still left in the list */
    tmp=head;
    head=head->next; // reassigning head to the next element
    free(tmp); // deallocating the current node
  }
  
  return;
}

/* Counting the number of elements */
int sll_count( node* head ) {
  int total=0;
  while( head!=NULL ) {
    total++;
    head=head->next;
  }

  return( total );
}

/* Printing elements of a linked list */
void sll_print( node* head ) {
  while( head!=NULL ) {
    printf( "%d:%lf\t", head->index, head->value );
    head=head->next;
  }
  printf( "\n" );

  return;
}

