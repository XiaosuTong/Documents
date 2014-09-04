/*******************************************************************
* You will likely want to compile this file with
* gcc -Wall  lastname.firstname.hw2.c -lm  -o hw2
* -Wall: indicates show all warnings
* -lm: indicates link against the math library
* This website has an adequate explanation:
* http://www.network-theory.co.uk/docs/gccintro/gccintro_17.html
*******************************************************************/


/********************************************
*    INCLUDE ANY HEADERS YOU WANT OR NEED   *
********************************************/
//TODO: Include headers

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define PI 3.14159265358979323846

/*******************************************************************
              Problem 1
INPUT:  n
RETURN: The same integer that f(n) would produce in recursion.c
Notes: 	See instructions for further information.  
		This routine must execute in O(n) time.
*******************************************************************/
int f(int n){
		//else
	int Fn = 0;
	int Fnminus = 1;
	int Fnminus2 = 0;
	int i;
	if(n == 0) return 0;
	if(n == 1) return 1; 

	for(i = 2; i <= n; ++i){
		Fn = Fnminus + Fnminus2;
		Fnminus2 = Fnminus;
		Fnminus = Fn;
	}
	return Fn;
}




/******************************************************************
			Problem 6a
INPUT: 	none
RETURN: A random number uniform on 0 to 1.
Note: 	The seeding is most appropriately done before calling this routine (likely in main)
		Just make a comment about where and how you are seeding here.
******************************************************************/
double unifrand(){
	//TODO: Implement problem 6a here.
	return rand()/(double)RAND_MAX;

}



/******************************************************************
			Problem 6b
INPUT:	none
RETURN:  A random observation from an Exponential (mean = 1) distribution.
******************************************************************/
double exprand(){
	//TODO: Implement problem 6b here.
	return -log(unifrand());

}


/********************************************************************
			Problem 6c
INPUT: 	none
RETURN:	A random observation from a standard normal distribution
********************************************************************/
double normrand(){
	//Using a double laplace proposal density
	double k = 2*pow(2*PI,-.5);
	double c = exp(.5);
	double p;
	while(1){
		p = exprand();
		double fp = exp(-.5*p*p);
		double gp = exp(-p);
		double u = unifrand();
		if( u * c * gp < fp)
			break;
		//else try again
	}
	//the next line started in the loop, but there is no reason to do this work before you accept.
	if(unifrand() < .5)
			p = -p;
	return p;
}


/********************************************************************
			Problme 6d
INPUT:	none
RETURN: A random observation from a Gamma(alpha) distribution.
NOTE: See algorithm 1 in the HW assignment
*******************************************************************/
double gamrand(double alpha){
	//TODO: Implement problem 6c here.
	double x,accept_prob;
	double e = exp(1);
	while(1){
		double u1 = unifrand();
		double u2 = unifrand();
		double k= e/(e+alpha);
		if(u1 > k){
			x = -log((1-u1)/k/alpha);
			accept_prob= pow(x,alpha-1);
			
		}else{
			x = pow(u1/k,1/alpha);
			accept_prob = exp(-x);
		}
		if(u2 < accept_prob) 
			break;
		
		
	}
	return x;
	
}




