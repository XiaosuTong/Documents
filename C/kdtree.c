#include <stdio.h>
#include <stdlib.h>

#define D 2
#define alpha 0.05
#define N 10000

struct tree
{
    float sub[D][N*alpha];
    struct tree *next;
};
typedef struct tree tree;

struct vertex
{
	float v[D];
	struct vertex *next;
};
typedef struct vertex vet;


void addvet(){
}

void addsub(){
}

void kdtree(int **tree, int depth)
{
	int d=D;
	float dmax=0;
	int r[N];
	v=malloc
	if(depth==1){
		v
	}
	for(i=0;i<d;i++){
		r[i] = range(tree[i]);
	}
	if(r[1] < r[2]){
		
	}
	else{

	}
	
}
