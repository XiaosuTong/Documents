#include <stdio.h>
void  sum(int *y);
int main(){
	int x=3;
	printf("main.x value %d\n", x);
	printf("main.x address %p\n", &x);
	sum(&x);
	//passed the address of x to sum function, so y in sum function is a pointer, or address. &y is the address of a address.
	printf("main.x value %d\n", x);
	printf("main.x value %p\n", &x);
	return 0;
}
void sum (int *y){
	printf("sum.x value %p\n", y);
	printf("sum.x address %p\n", &y);
	*y=*y+10;
	printf("sum.x value %p\n", y);
	printf("sum.x address %p\n", &y);
}

