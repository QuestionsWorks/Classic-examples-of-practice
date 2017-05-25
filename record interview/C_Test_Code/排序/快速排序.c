#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define N 10

void autocreatenum(int a[])
{
	int i;
	srand(time(NULL));
	for(i = 0; i < N; i++)
		a[i] = rand()%80;
}

void print(int a[])
{
	int i;
	for(i = 0; i < N; i++)
		printf("%4d",a[i]);
	printf("\n");
}

void sort(int *a, int left, int right)
{
    if(left >= right)/*如果左边索引大于或者等于右边的索引就代表已经整理完成一个组了*/
    {
        return ;
    }
    int low = left;
    int high = right;
    int key = a[left];
     
    while(low < high)                               /*控制在当组内寻找一遍*/
    {
        while(low < high && key <= a[high])
        /*而寻找结束的条件就是，1，找到一个小于或者大于key的数（大于或小于取决于你想升
        序还是降序）2，没有符合条件1的，并且i与j的大小没有反转*/ 
        {
            high--;/*向前寻找*/
        }
         
        a[low] = a[high];
        /*找到一个这样的数后就把它赋给前面的被拿走的i的值（如果第一次循环且key是
        a[left]，那么就是给key）*/
         
        while(low < high && key >= a[low])
        /*这是i在当组内向前寻找，同上，不过注意与key的大小关系停止循环和上面相反，
        因为排序思想是把数往两边扔，所以左右两边的数大小与key的关系相反*/
        {
            low++;
        }
         
        a[high] = a[low];
    }
     
    a[low] = key;/*当在当组内找完一遍以后就把中间数key回归*/
    sort(a, left, low - 1);/*最后用同样的方式对分出来的左边的小组进行同上的做法*/
    sort(a, low + 1, right);/*用同样的方式对分出来的右边的小组进行同上的做法*/
                       /*当然最后可能会出现很多分左右，直到每一组的i = j 为止*/
}

int main()
{
	int a[N];
	printf("排序之前:");
	autocreatenum(a);
	print(a);
	printf("排序之后:");
	sort(a,0,N-1);
	print(a);
	return 0;
}


















