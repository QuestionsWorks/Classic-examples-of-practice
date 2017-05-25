/*
函数fun的功能:在形参s所指字符串中的每个数字字符之后插入一个*号.
例如:形参s所指的字符串def35adh3kjsdf7,执行后结果为 def3*5*adh3*kjsdf7*
*/

#include<stdio.h>

void fun(char *s)
{
	int i,j,n;
	for(i = 0; s[i] != '\0'; i++)
	{
		if(s[i] >= '0' && s[i] <= '9')
		{
			n = 0;
			while(s[i+1+n] != '\0') //n的值是计算是数字的值离数组末尾的差值是多少
				n++; printf("n = %d\n", n);
			for(j = i+n+1; j > i; j--) //i+n+1 扩了一位 把最后一位往右移动一位 i+n的值是最后一位的最大编号
				s[j+1] = s[j];//往后挪所以要将前面的赋值给后面的
			s[j+1] = '*';
			i = i+1;
		}
	}
}

int main()
{
	char s[60] = "def35adh3kjsdf7";
	printf("\nThe original string is :%s\n",s);
	fun(s);
	printf("\nThe result is :%s\n",s);
	return 0;
}



