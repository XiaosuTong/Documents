/* Example illustrating recursion

   Can you guess what this function computes?  What is the complexity of computing f(n)?  Can it be done faster?
*/

#include<stdio.h>

int f(int n){
  if(n>1) 
    {
      return f(n-1)+f(n-2);
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
