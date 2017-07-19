
#include "CliUI.h"

//进入选择界面  101
int CliMainUI()
{
	int ichoice;
	printf("\t===============================\t\n");
	printf("\t=          1.用户登录         =\t\n");
	printf("\t=          2.用户注册         =\t\n");
	printf("\t=          3.找回密码         =\t\n");
	printf("\t=          4.退出             =\t\n");
	printf("请输入选择的编号：");
	scanf("%d",&ichoice);
	if(ichoice < 5 && ichoice > 0)
	{
		ichoice += 200;
		return ichoice;
	}
	printf("输入错误！\n返回本次开头！\n");
	return 101;
}

//进入用户登录界面  201
int CliLoginUI(USER *Cliuser)
{
	Cliuser->iNum = 201;//标识是登录
	system("clear");
	printf("\t=====用户登录====\t\n");
	printf("\t=               =\t\n");
	printf("\t=    用户ID:");
	scanf("%d",&Cliuser->iID);
	printf("\t=    用户密码：");
	scanf("%s",Cliuser->szPass);
    if ( getlocalip( Cliuser->szip ) == 0 )
	{
		printf("本次登录的IP地址是：%s\n",Cliuser->szip);
	}
	systemtime(Cliuser);
	CliSend(Cliuser);
	//将Cliuser 传到服务器端 进行验证  Clidata.c
	//判断
	system("clear");
	printf("上次登录的IP：%s\n",Cliuser->szipend);
	printf("上次登录的时间: %s\n",Cliuser->timeend);
	//上次登录的时间
	 if (strcmp(Cliuser->szipend,Cliuser->szip) != 0)
    {
        printf("上次登录的IP与您本次登录的IP不同，您的帐号安全有风险！建议修改密码！\n");         
    }
	//若不相符请修改密码
	return 102;
}


//登录成功界面  102
int CliSeccesUI(USER *Cliuser)
{
	int ichoice;
	printf("\t===============================\t\n");
	printf("\t=          1.单人聊天         =\t\n");
	printf("\t=          2.群组聊天         =\t\n");
	printf("\t=          3.修改密码         =\t\n");
	printf("\t=          4.删除聊天记录     =\t\n");
	printf("\t=          5.上传下载文件     =\t\n");
	printf("\t=          6.退出登录         =\t\n");
	printf("请输入选择的编号：");
	scanf("%d",&ichoice);
	if(ichoice < 7 && ichoice > 0)
	{
		ichoice += 50;
		return ichoice;
	}
	printf("输入错误！\n返回本次开头！\n");
	return 102;
}

//单人聊天  51
int CliOneChatUI(USER *Cliuser)
{
	Cliuser->iNum = 51;//标识是单聊
	//1.显示当前好友
	//2.选择一个好友
	//3.调用聊天界面
	printf("单人聊天\n");
	return 102;
}
//聊天界面  单发
//退出单人聊天 回到102


//群组聊天  52
int CliGroupChatUI(USER *Cliuser)
{
	Cliuser->iNum = 52;//标识是群聊
	//1.查看当前群组
	//2.选择一个群组  
	//3.调用聊天界面
	printf("群组聊天\n");
	return 102;
}
//聊天界面 群发
//退出群组聊天  回到102


//修改密码   53
int CliChangePassUI(USER *Cliuser)
{
	Cliuser->iNum = 53;//标识是修改密码
	char oldpass[20];
    char newpass1[20];
    char newpass2[20];

    printf("请输入初始密码:\n");
    scanf("%s",oldpass);
    if (strcmp(oldpass,Cliuser->szPass) != 0)
    {
        printf("初始密码与原登录密码不符！修改密码失败！\n");
        exit(-1);
    }
    //1.输入新密码
    printf("请输入新密码：\n");
    scanf("%s",newpass1);	   
	//2.再次输入新密码
    printf("请再次输入新密码：\n");
    scanf("%s",newpass2);	
    if (strcmp(newpass1,newpass2) != 0)   
    {
        printf("两次输入的密码不同，修改密码失败！\n");
        return 53;
    }
    strcpy(Cliuser->szPass,newpass2);
    //3.向服务器发送信息 修改密码
    printf("修改密码成功！\n");
    //4.返回到  102
	return 102;
}

//删除聊天记录  54
int CliDelUI(USER *Cliuser)
{
	Cliuser->iNum = 54;//标识是删除聊天记录
	//1.显示  聊天记录
	//   只能操作服务器给自己建立的文件夹   文件夹名为ID号
	//2.选择某项删除  输入文件名删除
	//3.退出   102
	printf("删除聊天记录\n");
	return 102;
}

//上传下载文件  55
int CliUpDownUI(USER *Cliuser)
{
	Cliuser->iNum = 55;//标识是上传下载文件
	// 2个界面 一个上传 一个下载
	//1.上传  上传到群组文件夹中
	//2.下载  显示当前共享的文件名
	//下载到当前目录下
	//3.返回上个界面 102
	printf("上传下载文件\n");
	return 102;
}
//退出登录   56
int CliReturnUI()
{
//	Cliuser->iNum = 56; //标识是退出登录
	
	return 101;
}

//用户注册  202
int CliRegisterUI(USER *Cliuser)
{
	Cliuser->iNum = 202; //标识是注册	
	//1.输入用户名 密码 备注  自动获取时间
	printf("\t=====用户注册=======\n");
    printf("\t=请输入用户名：\n");
    scanf("%s",Cliuser->szName);
    printf("\t=请输入密码：  \n");
    scanf("%s",Cliuser->szPass);
    printf("\t=请输入备注信息：\n");
    scanf("%s",Cliuser->szNote);
	systemtime(Cliuser); //获取注册时的时间
	//2.向服务器发送申请 写入服务器端的用户文件中
	//3.服务器返回一个生成的 ID
	
	CliSend(Cliuser);
	printf("请记住你的登录ID：%d \n",Cliuser->iID);
	
	return 101;
}

//找回密码 203
int CliForgotUI(USER *Cliuser)
{
	Cliuser->iNum = 203; //标识是找回密码
	//1.输入用户名 备注信息
	printf("请输入用户ID：\n");
    scanf("%d",&Cliuser->iID);
    printf("请输入备注信息：\n");
    scanf("%s",Cliuser->szNote);
	//2.将信息发送给服务器端  
	CliSend(Cliuser);
	//3.服务器验证成功后返回 该用户密码
	printf("\t您的密码是：%s\n\t请牢记！！\n",Cliuser->szPass);
	return 101;
	
}

//退出
