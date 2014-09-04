#include <stdio.h>
#include <stdlib.h>
int main(){
	int i;
	int a;
	int j;
	printf("PLease input your size:\n");
	scanf("%d", &a);
	int **array2;
	array2=malloc(a*sizeof(int *));
	for(i=0;i<a;i++){
	array2[i]=malloc(a*sizeof(int));
	}
	for(i=0;i<a;i++){
		for(j=0;j<a;j++){
		array2[i][j]=j;
		printf("%d ", array2[i][j]);
		}
	printf("\n");
	}
	for(i=0;i<a;i++){
	free(array2[i]);
	}
	free(array2);
	return 0;
}
