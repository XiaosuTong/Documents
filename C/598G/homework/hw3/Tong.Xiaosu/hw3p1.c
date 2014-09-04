/* Homework 3, problem 1 */
#include "linked_list.h"

/* Auxiliary functions */
#include<stdio.h>
#include<assert.h>


/* Stack implementation */
typedef struct singly_linked_list stack;

stack* stack_create( void ) {
	stack* m=(stack*)malloc(sizeof(stack));
	m -> head = NULL;
	m -> tail = NULL;
	return (m);
}

void stack_destroy( stack* s ) {
  node* tmp = s -> head;
  while(tmp != NULL){
	  s -> head = tmp -> next;
	  free (tmp);
	  tmp=s -> head;
	}
   s -> tail = NULL;
}

void push( stack* s, int value ) {
  node* new_node=(node*)malloc(sizeof(node));
  assert(new_node!=NULL);
  new_node -> data=value;
  new_node -> next=s -> head;
  s -> head = new_node;
  if(s -> tail == NULL)
	  s -> tail = new_node;

  return;
}

void pop( stack* s ) {
  if(s -> head ==NULL)
	  printf("Overflows!\n");
  else{ 
	  node* tmp = s -> head;
	  s-> head = tmp -> next;
      free(tmp);
      if(s -> head == NULL)
	      s -> tail = NULL;
  }
  return;
}

/* Queue implementation */
typedef struct singly_linked_list queue;

queue* queue_create( void ) {
   queue* n=(queue*)malloc(sizeof(queue));
   n -> head = NULL;
   n -> tail = NULL;
   return (n);
}

void queue_destroy( queue* q ) {
  node* tmp=q -> head;
  while(tmp != NULL){
	q -> head = tmp -> next;
    free (tmp);
	tmp=q -> head;
  }
  q -> tail = NULL;
}

void enqueue( queue* q, int value ) {
  node* new_node=(node*)malloc(sizeof(node));
  assert(new_node != NULL);
  new_node -> data = value;
  new_node -> next = NULL;
  if( q -> head == NULL)
	  q -> head =new_node;
  else
	  q -> tail -> next =new_node;
  q -> tail = new_node;

  return;

}

void dequeue( queue* q ) {
  if(q -> head ==NULL)
       printf("Overflows!\n");
 else{
	 node* tmp = q -> head;
     q-> head = tmp -> next;  
     free(tmp);
     if(q -> head == NULL)
         q -> tail = NULL;
 }
  return;

}

int main(void) {
  stack* s=stack_create();
  queue* q=queue_create();

  /* Part a */ 
  push( s, 1 );
  push( s, 2 );
  push( s, 3 );
  pop( s );
  push( s, 4 );
  push( s, 5 );
  pop( s );
  pop( s );
  push( s, 6 );
  pop( s );
  pop( s );
  pop( s );
  pop( s ); 
  stack_destroy( s ); 

  /* Part b */
  enqueue( q, 1 );
  enqueue( q, 2 );
  enqueue( q, 3 );
  dequeue( q );
  enqueue( q, 4 );
  enqueue( q, 5 );
  dequeue( q );
  dequeue( q );
  enqueue( q, 6 );
  dequeue( q );
  dequeue( q );
  dequeue( q );
  dequeue( q );
  queue_destroy( q );

  return( 0 );
}
