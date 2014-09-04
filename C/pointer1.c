#include <stdio.h>
#include <stdlib.h>
int main(){
	int i;
	int a=5;
	int *array, *array2;
	array=malloc(a*sizeof(int));
	array2=malloc(a*sizeof(int));
	printf("Please input your numvers:\n");
	for(i=0;i<10;i++){
	array[i]=i;
	printf("%d ",array[i]);
	}
	printf("\n");
	for(i=0;i<5;i++){
	printf("%d ", array2[i]);
	}
	printf("\n");

	return 0;
}
