/*
由N个有序整数组成的数列已经放在一维数组中,下列给定程序中函数的功能是:
利用折半查找法查找整数m在数组中的位置.若找到,返回其下标值,否则,返回-1

折半查找的基本算法是:每次查找前先确定数组中待查的范围low和high(low<high),
然后用m也中间位置(mid)上元素的值进行比较.如果m的值大于中间位置元素的值,
则下一次的查找范围落在中间位置之后的元素中;反之,下一次的查找范围落在中间
位置之前的元素中.指导low<high,查找结束.
*/

#include<stdio.h>
#define N 10

int fun(int a[],int m)
{
	int low=0,high=N-1,mid;
	while(low<=high)
	{
		mid=(low+high)/2;
		if(m<a[mid])
			high=mid-1;
		else if(m>a[mid])
		{
			low=mid+1;
		}
		else return(mid);
	}
	return -1;
}

int main()
{
	int i,a[N]={-3,4,7,9,13,45,67,89,100,180},k,m;
	printf("a数组中的数据如下:");
	for(i=0;i<N;i++)
	{
		printf("%4d",a[i]);
	}
	printf("\nEnter m:");
	scanf("%d",&m);
	k=fun(a,m);
	if(k>=0)
		printf("m=%d,index=%d\n",m,k);
	else
		printf("Not be found!\n");
	return 0;
}













