#include"data.h"

//主界面
int  MainUI();

//添加字典信息
STNODE * AdddicinfoUI(STNODE *head);

//删除字典信息
STNODE * deletedicinfo(STNODE *head);

//修改字典信息函数
STNODE * Modifydicinfo(STNODE *head);

//按名字或编号查找的函数
void searchnameorID(STNODE *head);

//读文件并且打印数据的函数
void showdicinfo(STNODE *head);

//退出前保存操作
void confirmsave(STNODE *head);

