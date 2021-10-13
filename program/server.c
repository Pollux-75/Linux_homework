#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/msg.h>
#define message_key 75

// 管理员账号密码
char username[] = "abcdefg";
char password[] = "1234567";

// 结点，保存状态
typedef struct Node
{
	int flag;
	char mtext[5001];
	char chg[200];
	char username[20];
	char password[20];
	double clientMoney, sumPrice;
	int na, nb, nc;
	int isRight;
	int comment;
	int comArray[5];
}Node;

// 消息格式
struct msgform
{
	long mtype;
	Node node;
}msg;

int numA = 100;
int numB = 100;
int numC = 100;
int comment[5] = {0};
int msgqid;
char helpPage[5001];
char res[100] = "";

// 从帮助页面读取帮助（文件操作）
void getHelp()
{
	FILE *file_pointer;
	file_pointer = fopen("help.dat", "r");
	if(file_pointer == NULL)
	{
		printf("文件不存在!\n");
	}
	else
	{
	    int i = fread(helpPage,1,5001,file_pointer);
	    helpPage[i] = 0;
	    fclose(file_pointer);
	}
	return;
} 

// 计算找零（负担得起的最大金额不能超过100）
void change(double a,double b)
{
	strcpy(res, "");
	int i;
	a=a-b;
	int j=a,k=j;

	if(a==0)
		strcat(res, "0");

	if(j-50>0)				
	{
		strcat(res, "1*50");
		j=j-50;
	}

	i=j/10;
	if(i>0)
	{
		char s1[20];
		s1[0] = i+'0';
		s1[1] = '\0';
		strcat(res, " ");
		strcat(res,strcat(s1,"*10"));
		j=j-i*10;
	}

	i=j/5;
	if(i>0)
	{
		char s1[20];
		s1[0] = i+'0';
		s1[1] = '\0';
		strcat(res, " ");
		strcat(res,strcat(s1,"*5"));
		j=j-i*5;
	}

	i=j/1;
	if(i>0)
	{
		char s1[20];
		s1[0] = i+'0';
		s1[1] = '\0';
		strcat(res, " ");
		strcat(res,strcat(s1,"*1"));
		j=j-i*1;
	}

	if((a-k)!=0)
	   strcat(res, " 1*0.5");
}

void cleanup()
{
	msgctl(msgqid, IPC_RMID, 0);	
}

int main()
{
	int i;
	for(i = 0; i < 20; ++i)
	{
		signal(i, cleanup);
	}
	
	msgqid = msgget(message_key, 0777|IPC_CREAT);
	while(1)
	{
		// 从客户端接收信息
		msgrcv(msgqid, &msg, sizeof(msg.node), 1, 0);
		// 分辨信息类型
		if(msg.node.flag == 1)
		{					
			// 帮助信息
			puts("客户端请求帮助信息");
			getHelp();
			strcpy(msg.node.mtext,helpPage);
			msg.mtype = 1;
			msgsnd(msgqid, &msg, sizeof(msg.node), 0);
		}
		else if(msg.node.flag ==2)
		{				
			// 购物信息
			puts("客户端结束购物，挑选的物品:");

			printf("coke : 	%d\n", msg.node.na);
			printf("orange : %d\n", msg.node.nb);
			printf("milk juice : %d\n",msg.node.nc);

			numA -=msg.node.na;
			numB -=msg.node.nb;
			numC -=msg.node.nc;
			
			double aa = msg.node.clientMoney;
			double bb = msg.node.sumPrice;
			change(aa, bb);
			strcpy(msg.node.chg,res);
			msg.mtype = 1;
			
			msg.node.na = numA;
			msg.node.nb = numB;
			msg.node.nc = numC;

			msgsnd(msgqid, &msg, sizeof(msg.node), 0);
		}
		else if(msg.node.flag == 3)
		{
			puts("客户端开始购物，询问饮料数量");
			msg.mtype = 1;
			msg.node.na = numA;
			msg.node.nb = numB;
			msg.node.nc = numC;	
			msgsnd(msgqid, &msg, sizeof(msg.node), 0);		
		}
		else if(msg.node.flag == 4)
		{
 			puts("客户端尝试登录");
			msg.mtype = 1;			
			if(strcmp(msg.node.username, username) != 0)
			{
				msg.node.isRight = 0;
				puts("登陆失败！");
			}
			else if(strcmp(msg.node.password, password) != 0)
			{
				msg.node.isRight = 0;
				puts("登陆失败！");
			}
			else msg.node.isRight = 1;
			msgsnd(msgqid, &msg, sizeof(msg.node), 0);
			if(msg.node.isRight == 1) puts("登陆成功！");
		}
		else if(msg.node.flag == 5)
		{
			puts("客户端给出了评价");
			comment[0]++;
			comment[msg.node.comment]++;	
		}
		else if(msg.node.flag == 6)
		{
			puts("管理员请求添加饮料");
			numA = 100;
			numB = 100;
			numC = 100;
			printf(" numA = %d\n numB = %d\n numC = %d\n", numA, numB, numC);
			msg.mtype = 1;
			msg.node.isRight = 1;
			msgsnd(msgqid, &msg, sizeof(msg.node), 0);
		}
		else if(msg.node.flag ==7)
		{
			puts("管理员检查评论");
			msg.mtype = 1;
			int ii;
			for(ii = 0; ii < 5; ++ii)
			{
				msg.node.comArray[ii] = comment[ii];
			}
			msgsnd(msgqid, &msg, sizeof(msg.node), 0);
		}
	}
}
