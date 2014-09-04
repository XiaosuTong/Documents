/* Solution to Homework 3, problem 3 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define MAXWORDLENGTH 1000

/* Read in the next word possibly preceeded by blanks/delimiters -- common to all parts */
int read_word( FILE* f, char* word ) {
  /* PUT YOUR CODE HERE -- OPTIONAL */
}

/* Part a */
void p3a( FILE* f ) {
 int length;
 int i;
 int j;
 char* word=malloc(MAXWORDLENGTH*sizeof(char));
 while( fscanf(f,"%s", word)==1 ){
	 length=strlen(word);
	 for(i=0;i<length;i++){
		 if(isalnum(word[i])){
			if((word[i]>=65) && (word[i]<=90))
				 word[i]=tolower(word[i]);
		 }
		 else{
			 for(j=i+1;j<=length;j++)
				 word[j-1]=word[j];
		 }
	 }
	 if(word[0] != '\0')
	 printf("%s \n", word);
 }
 free(word);
  return;
}

/* Part b */
void p3b( FILE* f ) {
  int length;
  int i;
  int j;
  int lengtha;
  char* word=malloc(MAXWORDLENGTH*sizeof(char));
  char* longest=malloc(MAXWORDLENGTH*sizeof(char));
  int longestlength=0;
  while( fscanf(f,"%s", word)==1 ){
      length=strlen(word);
      for(i=0;i<length;i++){
          if(isalnum(word[i])){
             if((word[i]>=65) && (word[i]<=90))
                  word[i]=tolower(word[i]);
          }
          else{
              for(j=i+1;j<=length;j++)
                  word[j-1]=word[j];
          }
      }
	  lengtha=strlen(word);
      if(lengtha>longestlength){
		  longestlength=lengtha;
		  for(i=0;i<longestlength;i++)
			  longest[i]=word[i];
	  }
  }

  for(i=0;i<longestlength;i++)
	  printf("%c", longest[i]);
  printf("\n");
  printf("%d\n",longestlength);
  free(word);
  free(longest);
  return;

}

/* Part c */
void p3c( FILE* f ) {
   int length;
   int i;
   int j;
   int lengtha;
   char* word=malloc(MAXWORDLENGTH*sizeof(char));
   int* length_all=malloc(MAXWORDLENGTH*sizeof(int));
   memset(length_all, 0, MAXWORDLENGTH*sizeof(int));
   int longestlength=0;
   while( fscanf(f,"%s", word)==1 ){
       length=strlen(word);
       for(i=0;i<length;i++){
           if(isalnum(word[i])){
              if((word[i]>=65) && (word[i]<=90))
                   word[i]=tolower(word[i]);
           }
           else{
               for(j=i+1;j<=length;j++)
                   word[j-1]=word[j];
           }
       }
	   lengtha=strlen(word);
       if(lengtha>longestlength)
           longestlength=lengtha;
	   if(word[0] != '\0')
       length_all[(lengtha-1)]=length_all[(lengtha-1)]+1;           
       }
 
   for(i=0;i<longestlength;i++){
	   printf("%d %d", (i+1), length_all[i]);
       printf("\n");
   }
  free(word);
  free(length_all);

 return;
}

/* Part d begin */
/* BEGIN STRUCTURES */
typedef struct node node;

struct node{
	node* parent;
	node* left;
	node* right;
	char* word;
	int count;
};

/* END STRUCTURES */

/* BEGIN AUXILIARY FUNCTIONS */

 node* insert( node* current, node* parent, char* newword ) {
   /* Insert a new value */

   if( current ){
     /* Non-empty subtree */
     if(strcmp(newword, (current->word))==-1){
		 /* Inserting to the left */
		current->left=insert( current->left, current, newword);
	 }
     else if(strcmp(newword, (current->word))==1){
       /* Inserting to the right */
       current->right=insert( current->right, current, newword);
	 }
     else if(strcmp(newword, (current->word))==0){
		 current->count++;
	 }
   }
   else
     { /* Subtree is empty */
       /* Creating a new node */
       current=(node*)malloc(sizeof(node));
       current->left=NULL;
       current->right=NULL;
	   current->word=newword;
       current->parent=parent;
	   current->count=1;
     } /* Subtree is empty */
   return( current );
 }

 void traverse_inorder( node* root ) {
   /* Outputting subtree value in order */
 
   if( root ) {
     /* Smaller values first */
     traverse_inorder( root->left);
     /* Outputting value with this node */
     printf(  "%s %d\n", root->word,root->count );
	 /* Larger values last */
     traverse_inorder( root->right);
   }
 
   return;
 }
					  
/* END AUXILIARY FUNCTIONS */

/* BEGIN DATA STRUCTURE FUNCTIONS */

/* PUT YOUR CODE HERE */

/* END DATA STRUCTURE FUNCTIONS */

void p3d( FILE* f ) {
  int i;
  node* root= NULL;
  int length;
  int j;
  int sum;
  char* wordnew=malloc(MAXWORDLENGTH*sizeof(char));
  while( fscanf(f,"%s", wordnew)==1 ){

	  length=strlen(wordnew);
      
      for(i=0;i<length;i++){
          if(isalnum(wordnew[i])){
             if((wordnew[i]>=65) && (wordnew[i]<=90))
                  wordnew[i]=tolower(wordnew[i]);
          }
          else{
              for(j=i+1;j<=length;j++)
                  wordnew[j-1]=wordnew[j];
          }
      }
	  char* wordnew2=malloc(MAXWORDLENGTH*sizeof(char));
	  for(i=0;i<strlen(wordnew);i++)
		  wordnew2[i]=wordnew[i];
      if(wordnew2[0] != '\0'){
		  sum++;
		  root = insert( root, NULL, wordnew2);
	  }
  }
  printf( "Words (in-order) are: \n" );
  traverse_inorder( root );
  printf("Total:%d\n",sum);
  printf( "\n" );
  

  return;
}

/* Part d end */

int main( int argc, char *argv[] ) {
    if( argc!=2 ) {
    perror( "Need to pass the filename as an argument\n" );
    return( -1 );
  }

  FILE* file=fopen( argv[1], "r" );
  if( !file ) {
    fprintf( stderr, "Cannot open file %s for reading.  Aborting.\n", argv[1] );
    return( -1 );
  }

 /*  Running part a */
  p3a( file );

  rewind( file ); // Back to the beginning of the file

  /* Running part b */
  p3b( file );
  
  rewind( file ); // Back to the beginning of the file

  /* Running part c */
  p3c( file );
  
  rewind( file ); // Back to the beginning of the file

  /* Running part d (including bonus) */
  p3d( file );

  rewind( file );

  fclose( file );

  return 0;
}

