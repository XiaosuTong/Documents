#include <stdio.h>
int x; //x is a globle variable which can be called from all functions. Here we defined x which allocates memory for x already.
void sum(int a);
int main(){
	x=3;
	printf("main.x value%d\n", x);
	printf("main.x address %p\n", &x);
	//pass the value of x into sum function
	//since in the sum function, it is still x that is be operated, address of x is not changed.
	sum(x);
	printf("main.x value%d\n", x);
	printf("main.x value%p\n", &x);
	return 0;
}
void sum (int a){
	printf("sum.x value%d\n", x);
	printf("sum.x address%p\n", &x);
	x=x+10;
	printf("sum.x value%d\n", x);
	printf("sum.x address%p\n", &x);
}

