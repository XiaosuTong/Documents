#include<stdio.h>
#include<stdlib.h>
int main(){
	int *array;
	int a;
	int i;
	int j;
	int value;
	printf("Please input the size of vector:\n");
	scanf("%d", &a);
	array=malloc(a*sizeof(int));
	printf("PLease input your vector:\n");
	for(i=0;i<a;i++){
		scanf("%d",&array[i]);
	}
	printf("The array you inputed is:");
	for(i=0;i<a;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
	for(i=1;i<a;i++){
		for(j=0;j<a-i;j++){
			if(array[j]>array[j+1]){
				value=array[j+1];
				array[j+1]=array[j];
				array[j]=value;
			}
		}
	}
	printf("The sorted array is:\n");
	for(i=0;i<a;i++){
		printf("%d ",array[i]);
	}
	printf("\n");
	return 0;
}
