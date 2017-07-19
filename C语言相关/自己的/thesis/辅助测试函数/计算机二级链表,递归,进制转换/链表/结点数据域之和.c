/*
函数fun的功能:计算一个带头结点的单项链表中个结点数据域中数值之和,
结果作为函数值返回
*/

#include<stdio.h>
#include<stdlib.h>
#define N 8
typedef struct list
{
	int data;
	struct list *next;
}SLIST;

int fun(SLIST *h)
{
	SLIST *p;
	int s=0;
	p=h->next;
	while(p)
	{
		s+=p->data;
		p=p->next;
	}
	return s;
}

SLIST *creatlist(int a[])
{
	SLIST *h,*p,*q;
	int i;
	h=p=(SLIST *)malloc(sizeof(SLIST));
	for(i=0;i<N;i++)
	{
		q=(SLIST *)malloc(sizeof(SLIST));
		q->data=a[i];
		p->next=q;
		p=q;
	}
	p->next=0;
	return h;
}

void outlist(SLIST *h)
{
	SLIST *p;
	p=h->next;
	if(p==NULL)
		printf("\nthe list is null!\n");
	else
	{
		printf("\nHead");
		do
		{
			printf("->%d",p->data);
			p=p->next;
		}while(p!=NULL);
		printf("->End\n");
	}
}

int main()
{
	SLIST *head;
	int x;
	int a[N]={12,87,45,32,91,16,20,48};
	head=creatlist(a);
	outlist(head);
	printf("\nsum=%d\n",fun(head));
	return 0;
}

















