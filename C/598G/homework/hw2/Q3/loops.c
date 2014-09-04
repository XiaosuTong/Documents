/* gcc loops.c
   time ./a.out 

   real	0m0.052s
   user	0m0.020s
   sys	0m0.004s

   gcc -o3 loops.c
   time ./a.out 

   real	0m0.049s
   user	0m0.020s
   sys	0m0.000s
*/   


#include<stdio.h>
int main(){
	int i;
	int j;
	float sum=0;
	for(i=1;i<=1000;i++){
		for(j=1;j<i;j++){
			sum=sum+(3*i*i+5*j+7*i*j);
		}
	}
	printf("The result is:%f\n", sum);
	return 0;
}
