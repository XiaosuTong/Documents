/* Example illustrating recursion

   Can you guess what this function computes?  What is the complexity of computing f(n)?  Can it be done faster?
*/

#include<stdio.h>

int f(int n){
  int a0=0;
  int a1=1;
  int a;
  int i;
	if(n>1)  {
      for(i=2;i<=n;i++){
		  a=a0+a1;
		  a0=a1;
		  a1=a;
		}
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
