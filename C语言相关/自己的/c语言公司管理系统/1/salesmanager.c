#include"ui.h"

//salesmanager增删改查的操作的选项
//此函数在salesmanager登录成功时调用
void salesmanageraction(char name[30],char pos[30])
{
	STNODE *head1=NULL;
	head1=readfiletolist("./personinfo.txt");//从文件中读取登录人员的信息
	int choice,choice1=1;

	while(choice1)
	{
		choice=SalesmanagerUI(name);//调用salesmanagerUI层的返回值
		switch(choice)
		{
			case 1:
				head1=AdddicinfoUI(head1,pos);  //增加人员信息
				rethome();
				break;
			case 2:
				head1=deletedicinfo(head1,pos); //删除人员信息
				rethome();
				break;
			case 3:
				head1=Modifydicinfo(head1,pos); //修改人员信息
				rethome();
				break;
			case 4:
				searchnameorID(head1,pos);      //查找人员信息
				rethome();
				break;
			case 5:
				showdicinfo(head1,pos);          //显示人员信息
				rethome();
				break;
			case 6:                              //查看删除人员的信息
				showdeleteinfo(pos);
				rethome();
				break;
			case 0:
		        confirmsave(head1);             //退出保存操作
				exit(0);
		}
	}
}

/***************************************
功能:salesmanager登录验证的子函数
使用:登录时loginUI中的经理登录中调用
****************************************/
void salesmanagerlogin(STNODE *head)//salesmanager登录验证函数
{
	int i;
	char sname[20];
	char pass[30];
	for(i=1;i<4;i++)
	{
		printf("\t\033[46;31m****************销售经理登录**************************\033[0m\n");
		printf("\033[;31m输入姓名:\033[0m");
		scanf("%s",sname);
		printf("\033[;31m输入密码:\033[0m");
		getchar();
		hiden(pass);
		printf("\n");
		STNODE *p=head->next;  
		while(p!=NULL)
		{ 
			if((strcmp(sname,p->person.name)==0&&strcmp(pass,p->person.passwd)==0)&&strcmp("销售经理",p->person.position)==0)
			{     
				if(iputchecking())//验证码输入为正确的
				{
					logininf(p->person.id,p->person.name,p->person.passwd);
					salesmanageraction(p->person.name,p->person.position);
					break;
				}
			}
		    p=p->next;
		}
		if(p==NULL)
			printf("\033[;31m用户名或密码错误!!\033[0m\n");
    }
    if(i==4)
    {
    	printf("\033[;31m输入错误3次,自动退出系统!!\033[0m\n");
    	exit(1);
    }
}


















