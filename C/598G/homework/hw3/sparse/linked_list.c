/* By S.V.N. Vishawanathan, modified by Sergey Kirshner */
/* Implementation of a singly linked list */

#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Initializing the singly linked list */
void sll_initialize( sll* list ) {
  list->head=NULL;
  list->tail=NULL;

  return;
}

/* Adding a node to the beginning of a singly linked list */
void sll_add( sll* list, int data ) {
  node* new_node=(node*)malloc(sizeof(node)); // creating new element
  assert(new_node!=NULL); // making sure memory is allocated
  new_node->data=data; // putting the value into the new element
  new_node->next=list->head; // making the old head element second
  list->head=new_node; // making the new element head
  if( list->tail==NULL )
    list->tail=new_node; // making the new element tail if the list was empty

  return;
}

/* Adding a node to the end of a singly linked list */
void sll_addtotail( sll* list, int data ) {
  node* new_node=(node*)malloc(sizeof(node)); // creating new element
  assert(new_node!=NULL); // making sure memory is allocated
  new_node->data=data;
  new_node->next=NULL;
  if( list->head==NULL )
    /* List is empty */
    list->head=new_node; // new node is now head
  else
    list->tail->next=new_node; // old tail points to the new one

  list->tail=new_node; // tail is now the new node  

  return;
}

/* Empty the linked list */
void sll_empty( sll* list ) {
  node* tmp=list->head;
  while( tmp!=NULL ) {
    /* Elements still left in the list */
    list->head=tmp->next; // reassigning head to the next element
    free(tmp); // deallocating the current node
    tmp=list->head; // figuring out the node to delete in the next iteration
  }
  list->tail=NULL; // setting the tail
  
  return;
}

/* Counting the number of elements */
int sll_count( sll list ) {
  int total=0;
  node* head=list.head;
  while( head!=NULL ) {
    total++;
    head=head->next;
  }

  return( total );
}

/* Printing elements of a linked list */
void sll_print( sll list ) {
  node* head=list.head;
  while( head!=NULL ) {
    printf( "%d\t", head->data );
    head=head->next;
  }
  printf( "\n" );

  return;
}

/* Find an element in the linked list */
node* sll_find( sll list, int value ) {
  node* head=list.head;
  while( head!=NULL ) {
    if( head->data==value )
      break;
    head=head->next;
  }

  return( head );
}
