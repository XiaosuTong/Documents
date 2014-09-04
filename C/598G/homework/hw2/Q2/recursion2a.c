/* Example illustrating recursion

   Can you guess what this function computes?  What is the complexity of computing f(n)?  Can it be done faster?
*/

#include<stdio.h>
#include<math.h>

double sqrt( double x);
double pow(double x, double y);
int f(int n){
  double x=(1+sqrt(5))/2;
  double y=(1-sqrt(5))/2;
  int a;
  int i;
	if(n>1)  {
      a=(pow(x,n)-pow(y,n))/sqrt(5);
	  return a;
	}
  else
    {
      return n ;
    }
}

int main() {
  printf( "%d\n", f(30) );
  return 0;
}
