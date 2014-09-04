#include <stdio.h>
#include <stdlib.h>
struct student
{
	int ID;
	char name[20];
	float score;
	struct student *next;
};

typedef struct student STU;

STU* creat( STU* head)
{
	int n=1;
	int flag = 1;
	STU *p1, *p2;
	p1=(STU *)malloc(sizeof(STU));
	printf("Please input %dth studnet's ID, name, and score:\n",n++);
	scanf("%d%s%f", &(p1->ID), p1->name,&(p1->score));
	p1->next = NULL;
	while(flag){
		if(head == NULL){
			head = p1;
		}
		else{
			p2 = p1;
			p1 = (STU *)malloc(sizeof(STU));
			p2->next = p1;
			printf("Please input %dth studnet's ID, name, and score:\n",n++);
			scanf("%d%s%f", &(p1->ID), p1->name,&(p1->score));
			p1->next = NULL;
			printf("Continue?Y/N\n");
			scanf("%d", &flag);
		}
	}
	return head;
}		

void output( STU* head)
{
	while(head != NULL){
		printf("student ID:%d, name:%s, score:%f\n",head->ID, head->name, head->score);
		head = head->next;
	}
}

void main(){
	STU* head;
	head = NULL;
	head=creat(head);
	output(head);
}
