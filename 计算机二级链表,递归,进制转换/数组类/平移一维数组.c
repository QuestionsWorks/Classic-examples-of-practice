/*
fun函数的功能:移动一维数组中的内容,若数组中有n个整数,要求把下标从0~p
(含p,p小于等于n-1)的数组元素到数组的最后. 例如:1 2 3 4 5 6 7 8 9 10
;p的值为3. 移动后,一维数组中的内容为5 6 7 8 9 10 1 2 3 4
*/

#include<stdio.h>
#define N 80
void fun(int *w,int p,int n)
{
	int i,j,t;
	for(i=0;i<=p;i++)//p用来控制循环几次的
	{
		t=w[0];          //先要保存w[0]的值,在覆盖完之后赋值给最后一位
		for(j=1;j<n;j++) //从下标为1的地方开始往前覆盖
		{
			w[j-1]=w[j];
		}
		w[n-1]=t;		
	}
}

int main()
{
	int a[N]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
	int i,p,n=15;
	printf("The original data:\n");
	for(i=0;i<n;i++)
	{
		printf("%3d",a[i]);
	}
	printf("\n\nEnter p:");
	scanf("%d",&p);
	fun(a,p,n);
	printf("\nThe data after moving:\n");
	for(i=0;i<n;i++)
		printf("%3d",a[i]);
	printf("\n\n");
	return 0;
}
