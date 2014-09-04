#include <stdio.h>
void function(int a[]);
int main(){
	int i;
	int array[5];
	function(&array[0]);
	for(i = 0; i < 5; i++){
		printf("%d ", array[i]);
	}
	printf("\n");
	for(i=0;i<5;i++){
		printf("%p ", &array[i]);
	}
	printf("\n");
}
void function(int a[]){
	int i;
	for(i=0; i<5 ;i++){
		a[i]=i;
	}

}

