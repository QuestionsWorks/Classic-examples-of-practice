#ifndef CLIENT_H  
#define CLIENT_H  

#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <signal.h>  
#include <sys/ipc.h>  
#include <sys/msg.h>  
#include <string.h>  
#include <errno.h>  
#include <pthread.h>  
#include <sys/types.h>  
#include <fcntl.h>  
#include <sys/stat.h>   
#define MAXLEN 1000   
  
struct message                  //消息结构体  
{  
	char flag[15];              //标志位 
	char name[20];              //用户名
	char msg[MAXLEN];           //消息内容
	char addressee[20];         //传输文件目的用户 
	int size;                   //传输内容字节数 
};  
extern int qid,fd;  
extern int sockfd;              //套接字描述符 
extern int savefilefd;          //保存文件描述符 
extern char filefromname[20];   //文件来源名
extern char chat_log[100];      //聊天记录名
extern pthread_mutex_t lock ;   //线程锁
char filefromuser[20];          //文件发送者用户名
char locname[20];               //本客户端用户名

int MenuUI();                //登录界面 
//模拟与服务器连接函数,打印点
void printdot();
void cutStr(char str[],char left[], int n, char right[],int m, char c);  //将字符串str在字符c处分割，前后两段 
int help(char str[]);                            //帮助
void handlerecvmsg(int *sockfd);                 //消息接收
int login_success(struct message *a);            //登录成功进入聊天模式
int Register(struct message *a);                 //注册
void log_user(struct message *a);                //用户登录

#endif //CLIENT_H



