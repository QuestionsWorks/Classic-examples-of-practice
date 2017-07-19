#include"ui.h"

 MYSQL *conn=NULL;
 MYSQL_RES *res=NULL;
 MYSQL_ROW row=NULL;


int BossUI()
{
    int iChoice=1;
	BOSS boss;
	char ch;
	while(iChoice!=0)
	{
	    system("clear");
		cout<<"\t\033[46;31m********************boss界面********************\033[0m"<<endl;
		cout<<"\t\033[46;31m**               1.添加人员信息               **\033[0m"<<endl;
		cout<<"\t\033[46;31m**               2.删除人员信息               **\033[0m"<<endl;
		cout<<"\t\033[46;31m**               3.按 部门 删除               **\033[0m"<<endl;
		cout<<"\t\033[46;31m**               4.修改人员信息               **\033[0m"<<endl;
		cout<<"\t\033[46;31m**               5.修改人员密码               **\033[0m"<<endl;
		cout<<"\t\033[46;31m**               6.查找人员信息               **\033[0m"<<endl;
		cout<<"\t\033[46;31m**               7.显示人员信息               **\033[0m"<<endl;
		cout<<"\t\033[46;31m**               8.一键录入工资               **\033[0m"<<endl;
		cout<<"\t\033[46;31m**               9.查看工资报表               **\033[0m"<<endl;
		cout<<"\t\033[46;31m**               0.返回登录界面               **\033[0m"<<endl;
		cout<<"\t\033[46;31m************************************************\033[0m"<<endl;
		cout<<"\033[;31m 选择要使用的功能(0~9):\033[0m" <<endl;
//		cin>>iChoice;
        iChoice=inputdigit09(ch);
		switch(iChoice)
		{
		        case 1:
				boss.bossadd();
				break;
			case 2:
				boss.bossdel();
				break;
			case 3:
				boss.bossdeldeprt();
				break;
			case 4:
				boss.bossmod();
				break;
			case 5:
				boss.bossmodifypasswd();
				break;
			case 6:
				boss.bosslook();
				break;
			case 7:
				boss.bossshow();
				break;
			case 8:
				boss.bossinputsalary();
				break;
			case 9:
				boss.bossshowtable();
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
//添加人员信息
void BOSS:: bossadd()
{
	char man[300];
	char ch;
	employee e;
	int choice=1;
	while(choice)
	{
		cout<<"\033[;31m               请输入要添加的人员信息:\033[0m"<<endl;
		cout <<"\033[;31m姓名:\033[0m";
		cin>>e.name;
		cout <<"\033[;31m密码:\033[0m";
		cin>>e.passwd;
		cout <<"\033[;31m性别: (男:女 )\033[0m";
		cin>>e.sex;
		cout <<"\033[;31m职称:\033[0m";
		cin >>e.position;           				//职称
    	strcpy(e.department,depart(e).department);	//部门  
		strcpy(e.grade,gradechoice(e).grade);		//等级
		strcpy(e.leader,leaderchoice(e).leader); 	//上级
		e.stablesalary=stablesal(e).stablesalary;	//固定工资
		e.worktime=wtime(e,e.worktime);        		//工作时间
		e.timereward=treward(e);    //单位时间报酬
		e.ticheng=tic(e);                //提成
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
		cout <<"\033[;31m是否继续添加? 1:是,0:否\033[0m ";
        choice=inputdigit01(ch);
	//	cin>> choice;
	}
		//mysql_free_result(res);  //释放结果集使用内存
		//mysql_close(conn);  // 关闭数据库连接	
} 
//删除人员信息  
void BOSS::bossdel()
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
		cout <<"\033[;31m 1: 按编号删除  2: 按姓名删除\n\033[0m";
//		cin>> choice2;
		choice2=inputdigit09(ch);
		switch(choice2)
		{
			case 1:
				cout<<"\033[;31m请输入要删除的编号:\033[0m";
				cin >>idnum;
				sprintf(man,"select id,name,position,department,grade,leader from personinfo where id=%d",idnum);
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
					cout<<"   \033[;31m 没有编号为\033[0m"<< idnum <<"\033[;31m的人员信息!!!\n\033[0m"<<endl;
				//mysql_free_result(res);  //释放结果集使用内存
				break;
			case 2:
				cout<<"\033[;31m请输入要删除的姓名:\033[0m";
				cin >>name;
				sprintf(man,"select name,id,position,department,grade,leader from personinfo where name='%s'",name);
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
					cout<<"   \033[;31m 没有姓名为\033[0m"<< name <<"\033[;31m的人员信息!!!\n\033[0m"<<endl;
				//mysql_free_result(res);  //释放结果集使用内存
				break;
		}
		cout <<" \033[;31m是否继续删除 ?  1: 继续  0: 退出\n\033[0m";
		cin>> choice1;
	}
} 

//按部门删除人员信息  
void BOSS::bossdeldeprt()
{
	//按编号,按姓名
	int choice1 =1;
	char chodep[30];
	int idnum;
	char name[20];
	char man[200];
	char confirm;
	int flag=0;
	while(choice1)
	{
		showfordep();
		cout <<"\033[;31m 请输入您想要删除的部门:\033[0m";
		cin>> chodep;
		sprintf(man,"delete from personinfo where department='%s'",chodep);
		cout<<"\033[;31m是否确认删除?  [y/n] :\033[0m";
		while(getchar()!='\n');
			confirm=getchar();
		if(confirm=='y')
		{
			if(mysql_query(conn,man))
			{
				fprintf(stderr,"%s\n",mysql_error(conn));	
				exit(1);
			}
		}
		if(confirm=='n')
		{
			cout <<"\033[;31m您选择不删除这个部门!!!\n\033[0m";
		}
		cout <<" \033[;31m是否继续删除 ?  1: 继续  0: 退出\n\033[0m";
		cin>> choice1;
	}
}
 
//boss修改密码
void BOSS::bossmodifypasswd()
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
		printf("%-10s%-12s%-17s%-15s  %-13s%-10s","\t编号","  姓名","职   称","  部  门","等级","上 级\n");
		printf("\t%-6d\t %-10s%-18s %-17s%-10s%-10s\n\n",atoi(row[0]),row[1],row[2],row[3],row[4],row[5]);
		mysql_free_result(res);
		modifypasswd(chonum);
		//sleep(3);	
		
	}
	else
		cout<<" \033[;31m   没有编号为\033[0m"<< chonum <<"\033[;31m 的人员信息!!!\n\033[0m"<<endl;
	cout<<"\033[;31m按任意键返回上一界面！\033[0m"<<endl;
    while(getchar()=='\n');
}
//修改人员信息  
void BOSS:: bossmod()
{
	//按编号,按姓名
	int choice1 =1;
	int choice2;
	char ch;
	int idnum;
	char name[20];
	char man[200];
	char confirm;
	int flag=0;
//	connectdatabase();          //连接数据库
	while(choice1)
	{
		cout <<" \033[;31m1: 按编号修改  2: 按姓名修改\n\033[0m";
		choice2=inputdigit12(ch);
		switch(choice2)
		{
			case 1:
				cout<<"\033[;31m请输入要修改的编号:\033[0m";
				cin >>idnum;
				sprintf(man,"select id,name,position,department,grade,leader from personinfo where id=%d",idnum);
				cout<<"               \t\033[;31m您想要修改的人员信息如下:\033[0m"<<endl;
				flag=findnumber(man,idnum);//数据库按编号查找
				if(flag==0)
					cout<<"    \033[;31m没有编号为"<< idnum <<"\033[;31m的人员信息!!!\n\033[0m"<<endl;
				mysql_free_result(res);  //释放结果集使用内存
				if(flag==1)
				{
					cout<<"\033[;31m是否确认修改?  [y/n]:\033[0m";
					while(getchar()!='\n');
						confirm=getchar();
					input1(confirm,idnum);
				}
//				if(flag==0)
//					cout<<"   \033[;31m 没有编号为"<< idnum <<"\033[;31m的人员信息!!!\n\033[0m"<<endl;
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
					input2(confirm,name);
				}
				if(flag==0)
					cout<<"    \033[;31m没有姓名为"<< name <<"\033[;31m的人员信息!!!\n\033[0m"<<endl;
				//mysql_free_result(res);  //释放结果集使用内存
				break;
		}
		cout <<" \033[;31m是否继续修改 ?  1: 继续  0: 退出\n\033[0m";
		choice1=inputdigit01(ch);
	}
}
//查找人员信息  
void BOSS:: bosslook()
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
		cout <<"\033[;31m 1: 按编号查询  2: 按姓名查询\n\033[0m";
		choice2=inputdigit12(ch);
	//	cin>> choice2;
		switch(choice2)
		{
			case 1:
				cout<<"\033[;31m请输入要查询的编号:\033[0m";
				cin >>idnum;
				cout<<endl;
				sprintf(man,"select id,name,position,department,grade,leader from personinfo where id=%d",idnum);
				cout<<"               \t\033[;31m您想要查找的人员信息如下:\033[0m"<<endl;
				flag=findnumber(man,idnum);//数据库按编号查找
				if(flag==0)
					cout<<"  \033[;31m  没有编号为"<< idnum <<"的人员信息!!!\n\033[0m"<<endl;
				mysql_free_result(res);  //释放结果集使用内存
				break;
			case 2:
				cout<<"\033[;31m请输入要查询的姓名:";
				cin >>name;
				cout<<endl;
				sprintf(man,"select name,id,position,department,grade,leader from personinfo where name='%s'",name);
				cout<<"               \t\033[;31m您想要查找的人员信息如下:\033[0m"<<endl;
				flag=findname(man,name);//数据库按姓名查找
				if(flag==0)
					cout<<"    \033[;31m没有姓名为"<< name <<"\033[;31m的人员信息!!!\n"<<endl;
				mysql_free_result(res);  //释放结果集使用内存
				break;
		}
		cout <<" \033[;31m是否继续查询 ? 1: 继续  0: 退出\n\033[0m";
		choice1=inputdigit01(ch);
//		cin>> choice1;
	}
}  

//显示人员信息  
void BOSS::bossshow()
{
    system("clear");
	char man[200];
	if(mysql_query(conn,"select id,name,passwd,sex,position,department,grade,leader from personinfo"))
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		exit(1);
	}
	res=mysql_use_result(conn);//获得结果集，一个表。
	printf("%-8s%-15s%-15s%-11s%-6s%-12s%-16s%-12s%-s","\t编号","   姓名","密码","性别","职"," 称","部  门","等级","上级\n\n");
	while((row=mysql_fetch_row(res)) != NULL)
	{
		printf("\t%d\t%-12s%-10s\t%-8s\t%-14s\t%-13s\t%s\t%-10s\n",atoi(row[0]),row[1],row[2],row[3],row[4],row[5],row[6],row[7]);	
	}
	cout<<"\033[;31m按任意键返回上一界面！\033[0m"<<endl;
    while(getchar()=='\n');
	mysql_free_result(res);
}  

//boss录入工资
void BOSS::bossinputsalary()
{
	double zonge;
	char man[200];
	list<employee> Link;
	employee p;
	cout <<"\033[;31m请先录入销售总额:\033[0m";
	cin>>zonge;
	sprintf(man,"update personinfo set zonge=%.0lf",zonge);
	if(mysql_query(conn,man))//从数据库中读取信息为计算工资做准备
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		exit(1);
	}
	cout<<"\033[;31m销售总额录入成功!!!\n\033[0m";
	cout<<"\033[;31m正在进行一键录入工资操作,请稍后\033[0m";
	printdot();
	cout<<"\033[;31m一键录入工资操作已完成,正在跳转操作界面,请稍后\033[0m";
	printdot();
	mysql_query(conn,"select *from personinfo"); //从数据库中读取信息为计算工资做准备
	res = mysql_use_result(conn);  //获得结果集， 一个表

	while((row = mysql_fetch_row(res))!=NULL)
	{
		p.id=atoi(row[0]);
		strcpy(p.position,row[4]);
		p.stablesalary=atof(row[8]);
		p.worktime = atoi(row[9]);
		p.timereward = atoi(row[10]);
		p.ticheng=atof(row[11]);
		p.zonge=atof(row[12]);
		strcpy(p.performance,row[13]);
		p.latertimes=atoi(row[14]);
		Link.push_back(p);
	}
	list<employee>::iterator p1=Link.begin(); //定义一个迭代器p1指向链表开头
	while(p1!=Link.end())
	{
		judgesalary(*p1,p1->id);//工资按照职称,表现,迟到次数计算最终工资
		p1++;
	}
	sleep(1);
}
//boss查看工资报表
void BOSS::bossshowtable()
{
     system("clear");
	char man[200];
	if(mysql_query(conn,"select id,name,position,stablesalary,zonge,salary,beizhu from personinfo"))
	{
		fprintf(stderr,"%s\n",mysql_error(conn));
		exit(1);
	}

	res = mysql_use_result(conn);  //获得结果集， 一个表
	printf("%-100s","----------------------------------------------------------------------------------------------------------------\n");
	printf("|\t\t\t\t\t\t**人员工资报表**\t\t\t\t\t       |\n");
	printf("%-100s","----------------------------------------------------------------------------------------------------------------\n");
	printf("%-9s%-13s%-15s%-15s%-18s%-16s%-50s","|编号|","|姓名  |", "|职    称 |","|固定工资|","|销 售 总 额|","|最终 工资|","|工    资    备     注     信     息       |\n");printf("%-100s","----------------------------------------------------------------------------------------------------------------\n");
	while((row = mysql_fetch_row(res))!=NULL)
	
	{	printf("|%-4d| |%-8s|   | %-10s|  |%-8.0lf| |%-10.0lf | |%-9.0lf| |%-53s|\n",atoi(row[0]),row[1],row[2],atof(row[3]),atof(row[4]),atof(row[5]),row[6]);
	
	}
	printf("%-100s","----------------------------------------------------------------------------------------------------------------\n");
	cout<<"\033[;31m按任意键返回上一界面！\033[0m"<<endl;
    while(getchar()=='\n');
}

















