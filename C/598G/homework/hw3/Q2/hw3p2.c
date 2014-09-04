/* Homework 3, problem 2 */

#include "ll_sv.h"
#include<ctype.h>
#include<assert.h>
#include<string.h>
#define MAXWORDSIZE 1000

/* Data structure for a vector */
struct svec {
  /* Assuming components are stored in the list in the decreasing order of indices */
  int dim;
  node* list;
};

typedef struct svec svec;

/* Data structure for a data set of vectors */
struct data {
  int num_vectors;
  svec** vector;
};

typedef struct data data;

double svec_ip( svec a, svec b ) {
  /* Inner product */
	double sum=0;
	node* comparea=a.list;
	node* compareb=b.list;
	while((comparea != NULL) && (compareb !=NULL)){
		if(comparea->index == compareb->index){
			sum= sum +( comparea -> value) *( compareb -> value);
			comparea=comparea -> next;
			compareb=compareb -> next;
		}
		else{
             if((comparea != NULL) && (compareb != NULL))
				 if(comparea -> index > compareb -> index){
                      comparea=comparea -> next;
                 }
                 else if(comparea -> index < compareb -> index){
					  compareb=compareb -> next;
                 }  
		}

	}
	return (sum);
}

/* AUXILIARY ROUTINES FOR READING IN FIELDS */
char* readline( FILE* f, char* line, int* length){ 
	 char* linestart=line;
     int linelength=*length;
     int readlength;
     while(1){
	   if(fgets( linestart, linelength, f) == NULL){
		   free(line);
	       line=NULL;
	       return(NULL);
	   }
       if(strrchr(line, '\n') != NULL)
           return( line);
       else{
            linelength*=2;
            line=(char*)realloc(line, linelength);
            readlength=strlen(line);
            linestart=line+readlength;
			linelength=*length -readlength;
	   }
	 }
}


svec* read_vector( FILE* f ) {
  /* Reading in a sparse vector */
    int i;
	svec* vector=malloc(sizeof(svec*));
    assert(vector!=NULL);
    vector -> list = NULL;
    int line_length=1000;
    char* line=calloc(line_length, sizeof(char));
	assert(line!=NULL);
	char* strindex;
	char* strvalue;
	vector -> dim=0;
	if((line=readline(f, line, &line_length)) != NULL){
			 strindex=strtok( line, ":");
             strvalue=strtok( NULL, " \t");
	    while(strvalue != "\n" && strindex && strvalue){
			node* newnode=(node*)malloc(sizeof(node));
			assert(newnode!=NULL);
			newnode -> index= atoi(strindex);
			newnode -> value= atof(strvalue);
			newnode -> next= vector -> list;
			vector -> list= newnode;
            strindex=strtok( NULL, ":");
            strvalue=strtok( NULL, " \t");
			if (newnode -> index > vector -> dim)
			vector -> dim = newnode-> index;
		}
	
	free(line);
    return (vector);
	}
	else{
		free(line);
		return(NULL);
	}
}



void read_vectors( FILE* f, data* d ) {
  int array_size=1; // Starting with array of size 1
  svec** temp_vec_array;
  int i;
  int is_done=0;

  d->num_vectors=0;

  /* Allocating array for vectors */
  d->vector=(svec**)calloc(array_size,sizeof(svec*));
  
  while( !is_done ) {
    while( d->num_vectors<array_size ) {
      /* Reading in the next vector */
      if(( d->vector[d->num_vectors]=read_vector( f ))!=NULL ){
		  d->num_vectors++;
	  }
      else{
	/* EOF is reached */
		break;
	  }
	  }
    
    
    if( d->num_vectors==array_size ) {
      /* Need to increase the size of array */
      /* Creating a new array -- twice the size of the old one */
      array_size*=2;
      temp_vec_array=(svec**)calloc(array_size,sizeof(svec*));
      /* Copying old data into the new one */
      for( i=0; i<d->num_vectors; i++ )
	temp_vec_array[i]=d->vector[i];
      /* Deleting the old array */
      free( d->vector );
      d->vector=temp_vec_array;
    } else{
      is_done=1;
	}
  }
  return;
}


void sll_empty( node* head ) {
	node* tmp;
    while( head!=NULL ) {
     
		tmp=head;
        head=head->next; 
	    free(tmp); 
    } 
	 return;
 }


int main( int argc, char* argv[] ) {
  FILE* f;
  data* d;
  int i, j;

  if( argc<2 ) {
    fprintf( stderr, "Need to pass a filename\n" );
    exit( -1 );
  }

  f=fopen( argv[1], "r" );
  if( !f ) {
    fprintf( stderr, "Unable to open file %s\n", argv[1] );
    exit( -1 );
  }


  /* Allocating the data set structure */
  d=(data*)malloc(sizeof(data));
  assert( d!=NULL );
  
  read_vectors( f, d );

  printf( "Inner products:\n" );
  for( i=0; i<d->num_vectors; i++ ) {
    for( j=0; j<d->num_vectors; j++ )
    printf( "%0.4lf  ", svec_ip( *(d->vector[i]), *(d->vector[j]) ) );
    printf( "\n" );
  }
  /* Deallocating the data set structure */
  for( i=0; i<d->num_vectors; i++ ) {
    sll_empty( d->vector[i]->list );
    free( d->vector[i] );
  }

  free( d->vector );
  free( d );
  

  fclose( f );

  return 0;
}
