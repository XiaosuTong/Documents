#include "ll_sv.h"
#include<ctype.h>
#include<assert.h>
#include<string.h>
#include<math.h>
#include<stdio.h>

/****************************************************************************************************/
/********************************    DATA READING    ************************************************/
/****************************************************************************************************/


/* Data structure for a observation */
struct svec{
	int dim;
	node* list;
};
/* Data structure for a observation */

typedef struct svec svec;


/* Data structure for whole data set */
struct data {
	int num_vectors;
	int hd;
	int* label;
	svec** vector;
};
/* Data structure for whole data set */

typedef struct data data;



/* Reading a line from the data file */
char* readline( FILE* f, char* line, int* length){
	char* linestart = line;
	int linelength = *length;
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
/* Reading a line from the data file */


/* Reading in a sparse vector from the line already read*/
svec* read_vector( FILE* f ) {
     int i;
     svec* vector=malloc(sizeof(svec*));
     assert(vector!=NULL);
     vector -> list = NULL;
     int line_length=10000000;
     char* line=calloc(line_length, sizeof(char));
     assert(line!=NULL);
     char* strindex;
     char* strvalue;
	 char* strlabel;
     vector -> dim=0;
     if((line=readline(f, line, &line_length)) != NULL){
       strlabel = strtok( line, " \t");
	   node* intercept = (node*)malloc(sizeof(node));
	   assert(intercept!=NULL);
       intercept -> index = 0;
	   intercept -> value = 1;
	   intercept -> next = vector -> list;
	   vector -> list = intercept;
	   while(1){
			 strindex = strtok( NULL, ":");
             strvalue = strtok( NULL, " \t");
			 if( strvalue == NULL)
				 break;
             node* newnode=(node*)malloc(sizeof(node));
             assert(newnode!=NULL);
             newnode -> index= atoi(strindex);
             newnode -> value= atof(strvalue);
             newnode -> next= vector -> list;
             vector -> list= newnode;
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
/* Reading in a sparse vector from the line already read*/


/* calculate the maximum number of estimator */
void get_datastats( FILE* f, data* dataset ) {
  
   int linelength=10000000;
   char* line=calloc(linelength,sizeof(char));
   assert(line!=NULL);
   char* strlabel;
   char* strindex;
   char* strvalue;
   int index;
   int i = 0;
   dataset -> label=(int*)calloc(dataset -> num_vectors, sizeof(int));
   assert( dataset -> label != NULL );
   /* Initialize the counters */
   
   dataset -> hd = 0;
   while( (line = readline( f, line, &linelength )) != NULL ) {
     /* Reading in the line */
   /* Parse the line */
     /* Skip the label */
	 strlabel=strtok( line, " \t" );
     dataset -> label[i] = atoi(strlabel);
     /* Reading in index feature pairs */
     while( 1 ) {
       /* Read in the index */
       strindex=strtok( NULL, ":" );
 
       /* Read the feature */
       strvalue=strtok( NULL, " \t" );
       if( strvalue==NULL )
       /* No more features to read */
         break;
 
       /* Determine whether the index is the large    st */
       index=atoi(strindex);
 
       if( index > dataset -> hd )
       dataset -> hd = index;
     }
	 i++;
   }
   return;
}
/* calculate the maximum number of estimator */


/* Reading in all data */
void read_vectors( FILE* f, data* d ) {
   int array_size=1; // Starting with array of size 1
   svec** temp_vec_array;
   int i;
   int is_done=0;

   d -> num_vectors = 0;
 
   /* Allocating array for vectors */
   d->vector=(svec**)calloc(array_size,sizeof(svec*));
 
   while( !is_done ) {
     while( d->num_vectors<array_size ) {
       /* Reading in the next vector */
       if(( d->vector[d->num_vectors]=read_vector( f ))!=NULL ){
           d -> num_vectors++;
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
	 } 
	 else{
       is_done=1;
     }
   }
   return;
}
/* Reading in all data */


/* free the memory */
void sll_empty( node* head ) {
     node* tmp;
     while( head!=NULL ) {
 
         tmp=head;
         head=head->next;
         free(tmp);
     }
      return;
  }
/* free the memory */

/****************************************************************************************************/
/********************************    DATA READING FUNCTION   ****************************************/
/****************************************************************************************************/




/****************************************************************************************************/
/********************************    CALCULATION FUNCTION   *****************************************/
/****************************************************************************************************/


/* Uper bound on the second derivative */

double F( double gamma, double delta){
	double a;
	if(fabs(gamma) <= fabs(delta))
		return(0.25);
	else{
		a = 1/(2+exp(fabs(gamma)-fabs(delta))+exp(fabs(delta)-fabs(gamma)));
		return(a);
	}
}

/* Uper bound on the second derivative */



/* tentative step computation functon */
double tentative_step(data* dataset, int J, double* beta, double delta, double lambda, int s){
	node* a;
	node* b;
	int i;
	double xij;
	double tentative = 0;
	double sum1 = 0;
	double sum2 = 0;
	double sum3 = 0;


	for(i = 0; i < dataset -> num_vectors; i++){
	   sum1=0;
	   a = (dataset -> vector[i]) -> list;
	   while(a -> index > J){
		   a = a -> next;
	   }
	   /* Check if there is Jth beta in the ith observation */
	   if(a -> index == J){
		   xij = a -> value;
		   b = (dataset -> vector[i]) -> list;
		   while(b != NULL){
			   sum1 = sum1 + beta[ b -> index] * (b -> value);
			   /* calculate the inner production between ith observation and beta */
               b = b -> next;
		   }
           sum2 = sum2 + (xij * (dataset -> label[i])) / (1 + exp(sum1 * (dataset -> label[i])));
		   /* calculate the summation in numerator of formula (8) in the report */
		   sum3 = sum3 + xij * xij * F((sum1 * (dataset -> label[i])), delta * xij);
		   /* calculate the summation in denominator of formula (8) in the report */
	   }
	}
	/* if there is no Jth beta in the observation */
	if(sum2==0 || sum3==0){
		tentative = 0;
	}
	else{
		if(J == 0)
			tentative = (sum2/dataset->num_vectors ) / (sum3/dataset -> num_vectors);
		else
			tentative = (sum2/dataset->num_vectors - lambda * s) / (sum3/dataset -> num_vectors);
	}
	return (tentative);
}
/* tentative step computation functon */


/* Log Likelihood function */
double loglikelihood(data* dataset, double* beta, double lambda){
	int i;
    double sum = 0;
    double sum1 = 0;
	double sum2 = 0;
	double result;
    node* a;
	for(i = 0; i < dataset->num_vectors; i++){
		sum = 0;
     	a = (dataset -> vector[i]) -> list;
		while(a != NULL){
			/* calculate the inner production between ith observation and beta */
			sum = sum + beta[ a -> index] * (a -> value);
			a = a -> next;
		}
        sum1 = sum1 + log(1 + exp(-sum * (dataset -> label[i])));
	}
	for(i = 1; i < (dataset -> hd)+1; i++)
        sum2 = sum2 + lambda * fabs(beta[i]);
	return ( (sum1 / dataset-> num_vectors) + sum2);
}
/* Log Likelihood function */


/* evaluation residual function */
float Residual(data* dataset, double* beta){
     double prob;
	 int y; 
	 int count = 0;
	 float persent;
     int i;
     int j;
     double sum;
     node* a;
     for(i = 0; i< dataset -> num_vectors; i++){
		 sum = 0;
         a = (dataset -> vector[i]) -> list;
         while(a != NULL){
             sum = sum + beta[a -> index] * (a -> value);
             a = a-> next;
         }
         prob = 1 / (1+ exp(-sum));
		 if(prob > 0.5)
			 y = 1;
		 else
			 y = -1;
		 if(y == dataset -> label[i])
			 count++;

     }
	 persent = ((float)count / (float)(dataset -> num_vectors)) * 100;
	 return (persent);
 }
/*  evaluation residual function */




/****************************************************************************************************/
/********************************    CALCULATION FUNCTION   *****************************************/
/****************************************************************************************************/



int main( int argc, char* argv[] ) {
   FILE* f;
   data* d;
   int i, j;
   node* a;
   double* beta;
   double* delta;
   double* lambda;
   int s;
   int k;
   int m;
   double tentative;
   double difference;
   int iteration = 0;
   double l1;
   double l2;
   int y;

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
   rewind(f);
   get_datastats( f, d);
   rewind(f);
	   

   printf("Do you want to change the scale of y? (1 is yes; 0 is no)\n");
   scanf("%d", &y);
   if(y == 1){
      for(i=0;i<d->num_vectors;i++){
	      if(d -> label[i] == 1)
               d -> label[i] = -1;
          if(d -> label[i] == 2)
               d -> label[i] = 1;
	  }
   }
   printf("The total size of the data is:%d\n", d -> num_vectors);
   printf("Please input the number of lambdas:\n");
   scanf("%d", &k);
   lambda = (double*)calloc(k, sizeof(double));
   assert( lambda != NULL);
   printf("Please input your sequence of lambda values:\n");
   for(i=0;i<k;i++)
	   scanf("%lf", &lambda[i]);
   beta = (double*)calloc((d -> hd) + 1, sizeof(double));
   assert( beta != NULL);
   delta = (double*)calloc((d -> hd) + 1, sizeof(double));
   assert( delta != NULL);
   for(i = 0; i<(d -> hd)+1; i++)
	   delta[i]=1;
   for(m=0;m<k;m++){
	 l1 = 1;
	 l2 = 0;
	 while(fabs(l1 -l2) >= 0.000001){
	   l1 = loglikelihood(d, beta, lambda[m]);
	   printf("l1 is %lf\n", l1);
	   for(j = d -> hd; j >= 0; j--){
		   if(beta[j] == 0){
			   s = 1;               /* try positive direction */
			   tentative = tentative_step(d, j, beta, delta[j], lambda[m], s);
			   if(tentative <= 0){   /* positive direction failed */
				   s =-1;           /* try negative direction */
				   tentative = tentative_step(d, j, beta, delta[j], lambda[m], s);
				   if(tentative >= 0)  /* negative direction failed */
					   tentative = 0;
			   }
		   }
		   else{
			   if(beta[j] > 0)
				   s = 1;
			   else if(beta[j] < 0)
				   s = -1;
			   tentative = tentative_step(d, j, beta, delta[j], lambda[m], s);
			   if(s * (beta[j] + tentative) < 0)   /* cross over zero */
				   tentative = -beta[j];
		   }
		   /* reduce the step to the interval */
	       difference = fminf(fmaxf(tentative, -delta[j]), delta[j]);
           beta[j] = beta[j] + difference;
	       delta[j] = fmaxf(2 * fabs(difference), delta[j] / 2);
	   }

	   iteration++;
	   l2 = loglikelihood(d, beta, lambda[m]);
	   printf("l2 is %lf\n", l2);
	   for(i=0; i< (d -> hd) +1; i++)
		   printf("%lf ", beta[i]);
	   printf("\n");
	 }

   }
   printf("%d\n", iteration);
   printf("The persentage of correction for the data is:%4.2f%%\n", Residual(d,  beta)) ;
   for( i=0; i<(d->num_vectors); i++ ){
	   sll_empty( d->vector[i]->list );
       free( d->vector[i] );
   }
   free( d -> label); 
   free( d->vector );
   free( d );
   free( beta );
   free( delta );
   free( lambda );
   fclose( f );
 
   return 0;
 }
