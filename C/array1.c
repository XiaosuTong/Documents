#include <stdio.h>
void function(int a[]);
int main(){
	int i;
	int array[5];
	function(array);
	//function(&array[0]);
	//two are the same, since if you would like to pass the a[] into function, you actually passed the address of first element of array to the function.
	for(i = 0; i < 5; i++){
		printf("%d ", array[i]);
	}
}
void function(int a[]){
	int i;
	for(i=0; i<5 ;i++){
		a[i]=i;
	}

}

