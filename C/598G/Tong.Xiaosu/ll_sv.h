/* By S.V.N. Vishawanathan, modified by Sergey Kirshner */
/* Implementation of a singly linked list */

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/* Type declarations */
/* Define a node of a linked list */
struct node { 
  int index;
  double value;
  struct node* next; 
};

typedef struct node node;

/* Function headers */
void sll_add( node**, int, double );
void sll_empty( node* );
int sll_count( node* );
void sll_print( node* );
