#include <stdio.h>
int x;
int  sum(int a);
int main(){
	x=3;
	printf("main.x value%d\n", x);
	printf("main.x address %p\n", &x);
	x=sum(x);
	//passed the value of x into sum function.
	//operated on a in sum function, which has a totally different address with x. Once all operations have been finished, the value of a will be returned to x.
	printf("main.x value%d\n", x);
	printf("main.x value%p\n", &x);
	return 0;
}
int sum (int a){
	printf("sum.x value%d\n", a);
	printf("sum.x address%p\n", &a);
	a=a+10;
	printf("sum.x value%d\n", a);
	printf("sum.x address%p\n", &a);
	return a;
}

