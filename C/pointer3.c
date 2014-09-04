#include <stdio.h>
#include <stdlib.h>
int main(){
	int i;
	int a;
	int j;
	printf("PLease input your size:\n");
	scanf("%d", &a);
	int **array2;
	//int *array;
	array2=malloc(a*sizeof(int *));
	array2[0]=malloc(a*a*sizeof(int));
	//array = malloc(a*a*sizeof(int));

	for(i=0;i<a;i++){
		array2[i]=array2[0]+a*i;
		//array2[i]=array+a*i;
	}

	for(i=0;i<a;i++){
		for(j=0;j<a;j++){
			array2[i][j]=j;
		}
	}
	for(i=0;i<a;i++){
		for(j=0;j<a;j++){
			printf("%d ", array2[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	free(array2[0]);
	//free(array);
	free(array2);
	return 0;
}
