/* By S.V.N. Vishawanathan, modified by Sergey Kirshner */
/* Implementation of a singly linked list */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Type declarations */
/* Define a node of a linked list */
struct node{ 
  int data;
  struct node* next; 
};

typedef struct node node;

/* Define a singly linked list */
struct singly_linked_list {
  node* head;
  node* tail;
};

typedef struct singly_linked_list sll;

/* Function headers */
void sll_initialize( sll* );
void sll_add( sll*, int );
void sll_addtotail( sll*, int );
void sll_empty( sll* );
int sll_count( sll );
void sll_print( sll );
node* sll_find( sll, int );
