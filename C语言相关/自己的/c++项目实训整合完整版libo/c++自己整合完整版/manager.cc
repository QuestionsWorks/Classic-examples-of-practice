#include"ui.h"

int ManagerUI(int id)
{
    int iChoice=1;
    char ch;
	Manager manager;
	while(iChoice!=0)
	{
	    system("clear");
		cout<<"\t\033[46;31m**********************经 理 界 面*****************\033[0m"<<endl;
		cout<<"\t\033[46;31m**               1.添加技术人员信息             **\033[0m"<<endl;
		cout<<"\t\033[46;31m**               2.删除技术人员信息             **\033[0m"<<endl;
		cout<<"\t\033[46;31m**               3.修改技术人员信息             **\033[0m"<<endl;
		cout<<"\t\033[46;31m**               4.修改技术人员密码             **\033[0m"<<endl;
		cout<<"\t\033[46;31m**               5.修改 自己的 密码             **\033[0m"<<endl;
		cout<<"\t\033[46;31m**               6.查找技术人员信息             **\033[0m"<<endl;
		cout<<"\t\033[46;31m**               7.按编号显示技术人员信息       **\033[0m"<<endl;
		cout<<"\t\033[46;31m**               8.按部门显示技术人员信息       **\033[0m"<<endl;
		cout<<"\t\033[46;31m*                0.返回登录界面                 **\033[0m"<<endl;
		cout<<"\t\033[46;31m**************************************************\033[0m"<<endl;
       
       

		cout<<" \033[;31m选择要使用的功能(0~8):\033[0m" <<endl;
//		cin>>iChoice;
        iChoice=inputdigit09(ch);
		switch(iChoice)
		{
		        case 1:
		        manager.add();
				break;
			case 2:
			    manager.del();
				break;
			case 3:
				manager.mod();
				break;
			case 4:
				manager.managermodifypasswd();
				break;
			case 5:
				modifypasswd(id);
				break;
			case 6:
				manager.look();
				break;
			case 7:
				manager.showposition();
				break;
			case 8:
			    manager.showdepartment();
			    break;
			case 0:
			    LoginUI();
				break;
			default:
				cout<< "\033[;31m输入有误,请重新输入\033[0m" <<endl;
				break;
		
	      }
   }
}
//经理添加人员信息
void Manager::add()
{
	
	char man[300];
	employee e;
	char ch;
	int choice=1;
	while(choice)
	{
		cout<<"             \033[;31m  请输入要添加技术人员的信息:\033[0m"<<endl;
		cout <<"\033[;31m姓名:\033[0m";
		cin>>e.name;
		cout <<"\033[;31m密码:\033[0m";
		cin>>e.passwd;
		cout <<"\033[;31m性别: (男:女 )\033[0m";
		cin>>e.sex;
		strcpy(e.position,"技术人员");
    	strcpy(e.department,depart(e).department);//部门 
		strcpy(e.grade,gradechoice(e).grade);//等级
		strcpy(e.leader,leaderchoice(e).leader); //上级
		e.stablesalary=stablesal(e).stablesalary;//固定工资
		e.worktime=wtime(e,e.worktime);        //工作时间
		e.timereward=treward(e);    //单位时间报酬
		e.ticheng=0;                //提成
		e.zonge=0;                  //销售总额
		strcpy(e.performance,"一般"); //工作表现
		e.latertimes=0;             //迟到次数
		e.salary=0;                 //工资
		e.jifen=jifeninit(e);       //积分(用来提升等级)
		strcpy(e.beizhu,"此人员的工资备注暂为空");      //备注信息
		sprintf(man,"insert into personinfo(name,passwd,sex,position,department,grade,leader,stablesalary,worktime,timereward,ticheng,zonge,performance,latertimes,salary,jifen,beizhu)values('%s','%s','%s','%s','%s','%s','%s',%lf,%d,%d,%lf,%lf,'%s',%d,%lf,%d,'%s')",e.name,e.passwd,e.sex,e.position,e.department,e.grade,e.leader,e.stablesalary,e.worktime,e.timereward,e.ticheng,e.zonge,e.performance,e.latertimes,e.salary,e.jifen,e.beizhu);

		printf("%s\n",man);
		if(mysql_query(conn,man))    //发送SQL语句，成功返回0；
		{
			fprintf(stderr,"%s\n",mysql_error(conn));
			exit(1);
		}
		cout <<"\033[;31m添加成功!!\033[0m"<<endl;
		cout <<"\033[;31m是否继续添加? 1:是,0:否 \033[0m";
//		cin>> choice;
		choice=inputdigit01(ch);
		}
	//mysql_free_result(res);  //释放结果集使用内存
//	mysql_close(conn);  // 关闭数据库连接
} 
//经理删除人员信息  
void Manager:: del()
{
	//按编号,按姓名
	int choice1 =1;
	int choice2;
	int idnum;
	char name[20];
	char ch;
	char man[200];
	char confirm;
	int flag=0;

	while(choice1)
	{
		cout <<"\033[;31m 1: 按编号删除  2: 按姓名删除\n\033[0m";
//		cin>> choice2;
		choice2=inputdigit12(ch);
		switch(choice2)
		{
			case 1:
				cout<<"\033[;31m请输入要删除的编号:\033[0m";
				cin >>idnum;
				sprintf(man,"select id,name,position,department,grade,leader from personinfo where id=%d and position='%s'",idnum,"技术人员");
				cout<<"               \t\033[;31m您想要删除的人员信息如下:\033[0m"<<endl;
				flag=findnumber(man,idnum);//数据库按编号查找
				mysql_free_result(res);  //释放结果集使用内存
				if(flag==1)
				{
					cout<<"\033[;31m是否确认删除?  [y/n]:\033[0m";
					while(getchar()!='\n');
						confirm=getchar();
					deletenumber(confirm,idnum);
				}
				if(flag==0)
					printf("\033[;31m没有编号为%d的技术人员的信息!!!\n\033[0m",idnum);
				//mysql_free_result(res);  //释放结果集使用内存
				break;
			case 2:
				cout<<"\033[;31m请输入要删除的姓名:";
				cin >>name;
				sprintf(man,"select name,id,position,department,grade,leader from personinfo where name='%s' and position='%s'",name,"技术人员");
				cout<<"               \t\033[;31m您想要删除的人员信息如下:\033[0m"<<endl;
				flag=findname(man,name);//数据库按姓名查找
				mysql_free_result(res);  //释放结果集使用内存
				if(flag == 1)
				{
					cout<<"\033[;31m是否确认删除?  [y/n]:\033[0m";
					while(getchar()!='\n');
						confirm=getchar();
					deletename(confirm,name);
				}
				if(flag==0)
					printf("\033[;31m没有姓名为%s的技术人员的信息!!!\n\033[0m",name);
				//mysql_free_result(res);  //释放结果集使用内存
				break;
		}
		cout <<" \033[;31m是否继续删除 ?  1: 继续  0: 退出\n\033[0m";
//		cin>> choice1;
		choice1=inputdigit01(ch);
	}
}  
//修改密码
void Manager::managermodifypasswd()
{
	char man[200];
	int chonum;
	cout<<"\033[;31m请输入您想要修改密码的人员的编号:\033[0m";
	cin>>chonum;
	sprintf(man,"select id,name,position,department,grade,leader from personinfo where id=%d",chonum);
	if(mysql_query(conn,man))
	{
		fprintf(stderr,"%s\n",mysql_error(conn));	
		exit(1);
	}
	res=mysql_use_result(conn);//发送结果集
	if((row=mysql_fetch_row(res)) != NULL)
	{	
		printf("%-10s%-12s%-15s%-15s  %-13s%-10s","\t编号","  姓名","职  称","  部  门","等级","上 级\n");
		printf("\t%-6d\t %-10s%-18s %-17s%-10s%-10s\n\n",atoi(row[0]),row[1],row[2],row[3],row[4],row[5]);
		mysql_free_result(res);
		modifypasswd(chonum);	
		
	}
	else
		cout<<"    \033[;31m没有编号为\033[0m"<< chonum <<"\033[;31m的人员信息!!!\n\033[m"<<endl;
}

//经理修改人员信息  
void Manager:: mod()
{
	//按编号,按姓名
	int choice1 =1;
	int choice2;
	int idnum;
	char ch;
	char name[20];
	char man[200];
	char confirm;
	int flag=0;
//	connectdatabase();          //连接数据库
	while(choice1)
	{
		cout <<" \033[;31m1: 按编号修改  2: 按姓名修改\n\033[0m";
//		cin>> choice2;
		choice2=inputdigit12(ch);
		switch(choice2)
		{
			case 1:
				cout<<"\033[;31m请输入要修改的编号:\033[0m";
				cin >>idnum;
				sprintf(man,"select id,name,position,department,grade,leader from personinfo where id=%d",idnum);
				cout<<"               \t\033[;31m您想要修改的人员信息如下:\033[0m"<<endl;
				flag=findnumber(man,idnum);//数据库按编号查找
				
				mysql_free_result(res);  //释放结果集使用内存
				if(flag==1)
				{
					cout<<"\033[;31m是否确认修改?  [y/n]:\033[0m";
					while(getchar()!='\n');
						confirm=getchar();
					input3(confirm,idnum);
				}
				if(flag==0)
					printf("\033[;31m没有编号为%d的技术人员的信息!!!\n\033[0m",idnum);
				//mysql_free_result(res);  //释放结果集使用内存
				break;
			case 2:
				cout<<"\033[;31m请输入要修改的姓名:\033[0m";
				cin >>name;
				sprintf(man,"select name,id,position,department,grade,leader from personinfo where name='%s'",name);
				cout<<"               \t\033[;31m您想要修改的人员信息如下:\033[0m"<<endl;
				flag=findname(man,name);//数据库按姓名查找
				mysql_free_result(res);  //释放结果集使用内存
				if(flag ==1)
				{
					cout<<"\033[;31m是否确认修改?  [y/n]:\033[0m";
					while(getchar()!='\n');
						confirm=getchar();
					input4(confirm,name);
				}
				if(flag==0)
					printf("\033[;31m没有姓名为%s的技术人员的信息!!!\n\033[0m",name);
				//mysql_free_result(res);  //释放结果集使用内存
				break;
		}
		cout <<" \033[;31m是否继续修改 ?  1: 继续  0: 退出\n\033[0m";
	//	cin>> choice1;
		choice1=inputdigit01(ch);
	}
}
//经理查找人员信息  
void Manager:: look()
{
		//按编号,按姓名
	int choice1 =1;
	int choice2;
	int idnum;
	char ch;
	char name[40];
	char man[300];
	int flag=0;
	while(choice1)
	{
		cout <<" \033[;31m1: 按编号查询  2: 按姓名查询\n\033[0m";
//		cin>> choice2;
		choice2=inputdigit12(ch);
		switch(choice2)
		{
			case 1:
				cout<<"\033[;31m请输入要查询的编号:\033[0m";
				cin >>idnum;
				cout<<endl;
				sprintf(man,"select id,name,position,department,grade,leader from personinfo where id=%d and position='%s'",idnum,"技术人员");
				cout<<"               \t\033[;31m您想要查找的人员信息如下:\033[0m"<<endl;
				flag=findnumber(man,idnum);//数据库按编号查找
				if(flag==0)
					printf("\033[;31m没有编号为%d的技术人员的信息!!!\n\033[0m",idnum);
				mysql_free_result(res);  //释放结果集使用内存
				break;
			case 2:
				cout<<"\033[;31m请输入要查询的姓名:\033[0m";
				cin >>name;
				cout<<endl;
				sprintf(man,"select name,id,position,department,grade,leader from personinfo where name='%s'and position='%s'",name,"技术人员");
				cout<<"               \t\033[;31m您想要查找的人员信息如下:\033[0m"<<endl;
				flag=findname(man,name);//数据库按姓名查找
				if(flag==0)
					printf("\033[;31m没有姓名为%s的技术人员的信息!!!\n\033[0m",name);
				mysql_free_result(res);  //释放结果集使用内存
				break;
		}
		cout <<" \033[;31m是否继续查询 ? 1: 继续  0: 退出\n\033[0m";
//		cin>> choice1;
		choice1=inputdigit01(ch);
	}
}

//经理显示人员信息按职称  
void Manager::showposition()
{   
    system("clear");
	char man[200];
	sprintf(man,"select id,name,passwd,sex,position,department,grade,leader from personinfo where position='%s'","技术人员");
	if(mysql_query(conn,man))
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		exit(1);
	}
	res=mysql_use_result(conn);//获得结果集， 一个表。
	printf("%-14s%-15s%-15s%-11s%-6s%-12s%-16s%-12s%-17s","\t\033[;31m编号","   姓名","密码","性别","职"," 称","部  门","等级","上级\n\033[0m");
	while((row=mysql_fetch_row(res)) != NULL)
	{
		printf("\t%d\t%-12s%-10s\t%-8s\t%-12s\t%-13s\t%s\t%-10s\n",atoi(row[0]),row[1],row[2],row[3],row[4],row[5],row[6],row[7]);	
	}
    cout<<"\033[;31m按任意键返回上一界面！\033[0m"<<endl;
    while(getchar()=='\n');
	
//	mysql_free_result(res);
}  

//经理显示人员信息按部门  
void Manager::showdepartment()
{    
    system("clear");
	char man[200];
	sprintf(man,"select id,name,passwd,sex,position,department,grade,leader from personinfo where department='%s'","技术部");
	if(mysql_query(conn,man))
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		exit(1);
	}
	res=mysql_use_result(conn);//获得结果集， 一个表。
	printf("%-14s%-14s%-15s%-11s%-6s%-12s%-16s%-12s%-17s","\t\033[;31m编号","   姓名","密码","性别","职"," 称","部  门","等级","上级\n\033[0m");
	while((row=mysql_fetch_row(res)) != NULL)
	{
		printf("\t%d\t%-11s%-11s\t%-8s\t%-12s\t%-13s\t%s\t%-10s\n",atoi(row[0]),row[1],row[2],row[3],row[4],row[5],row[6],row[7]);	
	}
	 cout<<"\033[;31m按任意键返回上一界面！\033[0m"<<endl;
    while(getchar()=='\n');
//	mysql_free_result(res);
}  

 







