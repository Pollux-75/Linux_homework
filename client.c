#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#define message_key 75

/*结点，保存状态*/
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

/*消息格式*/
struct msgform
{
	long mtype;
	Node node;
}msg;

int numA, numB, numC;
char comm[4][10] = { "good", "normal", "soso", "bad" };  

/*主界面UI*/
void call_MAIN_GUI() 
{	
	puts("==================================================");
	puts("==================================================");
	puts("                        /|\                       ");
	puts("                       //|\\                      ");
	puts("             ________/// | \\\________            ");
	puts("           //*********** | ***********\\          ");
	puts("          //***********  |  ***********\\         ");
	puts("         //***********   |   ***********\\        ");
	puts("        //***********    |    ***********\\       ");
	puts("       //***********   | | |   ***********\\      ");
	puts("      //*********** \\ | | | // ***********\\     ");
	puts("     \\***********     | | |    ************//    ");
	puts("      \\    ...... <<.........>> ......    //     ");
	puts("       \\     *****  .........  *****     //      ");
	puts("        \\    *****  .........  *****    //       ");
	puts("         \\   ***** ........... *****   //        ");
	puts("          \\  ***  .           .  ***  //         ");
	puts("           \\ **  .    GOOD     .  ** //          ");
	puts("            \\*   .    JUICE    .   *//           ");
	puts("             \\   .             .   //            ");
	puts("              \\    ...........    //             ");
	puts("               \\    .........    //              ");
	puts("                \\    .......    //               ");
	puts("                 \\   .......   //                ");
	puts("                  ===.........===                 ");
	puts("                    ===========                   ");
	puts("==================================================");
	puts("    Enter '1' : 开始购物	 Enter '2' : 帮助       ");
	puts("	           Enter '3' 管理员登录                 ");
	puts("==================================================");
};

/*商品页面*/
void callShopping()
{					                   

	struct msgform msg;					//向服务器发送信息
	int msgqid;
	msgqid = msgget(message_key, 0777);
	msg.node.flag = 3;
	msg.mtype = 1;
	msgsnd(msgqid, &msg, sizeof(msg.node), 0);
	msgrcv(msgqid, &msg, sizeof(msg.node), 1, 0);		//接收number数量

	numA = msg.node.na;
	numB = msg.node.nb;
	numC = msg.node.nc;

	puts("=============================================================");
	printf("                   美味饮品   欢迎品尝                     ");
	printf("\n");
	puts("=============================================================");
	printf("\n");
	printf("  a : 可可               单价  2.5$   Number : %d\n\n", numA);
	printf("  b : 橙汁               单价  2.5$   Number : %d\n\n", numB);
	printf("  c : 热牛奶             单价  4.0$   Number : %d\n\n", numC);
	puts("=============================================================");
}

/*结束界面*/
void callLastPrint() 
{					                                  
	puts("                                                                                 ");
	puts("                        *                      *                                 ");
	puts("                      *   *                  *  *                                ");
	puts("                     *     *                *    *                               ");
	puts("                    *       *              *      *                              ");
	puts("              ********************************************                       ");
	puts("       \     |                                            |     /                ");
	puts("        \    |       ******                   ******      |    /                 ");
	puts("         \   |       ******                   ******      |   /                  ");
	puts("          \  |       ******                   ******      |  /                   ");
	puts("           \ |       ******                   ******      | /                    ");
	puts("            \|                                            |/                     ");
	puts("             |                     ***                    |                      ");
	puts("             |                     * *                    |                      ");
	puts("             |        *                           *       |                      ");
	puts("-------------|        *****                   *****       |-----------------     ");
	puts("             |        *****                   *****       |                      ");
	puts("             |        *****                   *****       |                      ");
	puts("             |        *****************************       |                      ");
	puts("            /|        *****************************       |\                     ");
	puts("           / |        *****************************       | \                    ");
	puts("          /  |                                            |  \                   ");
	puts("         /   **********************************************   \                  ");
	puts("        /                                                      \                 ");
	puts("================================================================================");
	puts("                      谢谢惠顾 欢迎您的下次光临！！！                           ");
	puts("================================================================================");
}

/*管理员操作UI*/
void adminGUI() {
	puts("**********************************************");
	puts("*                                            *");
	puts("*           1 : 更新商店页面                 *");
	puts("*                                            *");
	puts("*           2 : 检查评论信息                 *");
	puts("*                                            *");
	puts("*          任意输入后退出此页面	           *");
	puts("**********************************************");
	puts("请输入您的需求（1—2）");
}

void callManage() {
	adminGUI();
	int order;
	while (scanf("%d", &order))
	{
		struct msgform msg;					//将销售信息送往服务端
		int msgqid;
		msg.mtype = 1;
		msgqid = msgget(message_key, 0777);
		if (order == 1) 
		{
			msg.node.flag = 6;
			msgsnd(msgqid, &msg, sizeof(msg.node), 0);
			msgrcv(msgqid, &msg, sizeof(msg.node), 1, 0);
			if (msg.node.isRight == 1)
			{
				puts("成功更新！");
			}
			else puts("更新失败!");

		}
		else if (order == 2) 
		{
			msg.node.flag = 7;
			msgsnd(msgqid, &msg, sizeof(msg.node), 0);
			msgrcv(msgqid, &msg, sizeof(msg.node), 1, 0);
			printf("There %d people's comment\n", msg.node.comArray[0]);
			int ii;
			for (ii = 1; ii < 5; ++ii) 
			{
				printf("%s :		%d\n", comm[ii - 1], msg.node.comArray[ii]);
			}
		}
		else return;
	}
}

/*登录系统*/
void callLogin() {
	char name[20], pwd[20];

	int count = 0;
	struct msgform msg;
	int msgqid;
	msgqid = msgget(message_key, 0777);
	msg.node.flag = 4;
	msg.mtype = 1;
	while (1)
	{
		puts("请输入您的用户名： ");
		scanf("%s", name);
		puts("请输入您的密码: ");
		scanf("%s", pwd);
		strcpy(msg.node.username, name);
		strcpy(msg.node.password, pwd);
		msgsnd(msgqid, &msg, sizeof(msg.node), 0);
		msgrcv(msgqid, &msg, sizeof(msg.node), 1, 0);
		int isRight;
		isRight = msg.node.isRight;
		if (isRight == 0) 
		{
			puts("用户名或密码错误，请重新输入");
		 	if (++count >= 3)	return;                //错误三次后终止任务      
		}
		else break;
	}
	callManage();
}

/*评论页面*/
void callComment() {
	puts("===========================================================");
	puts("===========================================================");
	puts("|          请输入您对此系统的评价！！                     |");
	puts("|                                                         |");
	puts("|            *                                            |");
	puts("|           * *                                           |");
	puts("|          *****                  1 : 好评！              |");
	puts("|  * *   * *O O* *    * *                                 |");
	puts("| *   *    | W |     *   *        2 : 不错！              |");
	puts("|   \ \     ---      / /                                  |");
	puts("|    \ \   *....*   / /           3 : 一般！              |");
	puts("|     \ \ *......* / /                                    |");
	puts("|       \*........*/              4 : 差评！              |");
	puts("|       *..........*                                      |");
	puts("|      *............*                                     |");
	puts("|     *..............*                                    |");
	puts("|    ******      ******                                   |");
	puts("|         / /  \ \                                        |");
	puts("|         | |  | |                                        |");
	puts("|         | |  | |                  谢谢您的评价!!!       |");
	puts("===========================================================");
	puts("===========================================================");
	puts("请在此页面输入您的评价（0—4）！！！");

	int comment;
	scanf("%d", &comment);
	struct msgform msg;
	int msgqid;
	msgqid = msgget(message_key, 0777);
	msg.node.flag = 5;
	msg.mtype = 1;
	msg.node.comment = comment;
	msgsnd(msgqid, &msg, sizeof(msg.node), 0);
}

int main() {
MPAGE:	call_MAIN_GUI();
	char str[10];
	scanf("%s", str);
	if (str[0] == '2') {					//请求帮助
		struct msgform msg;
		int msgqid;
		msgqid = msgget(message_key, 0777);			//创建消息队列
		msg.node.flag = 1;
		strcpy(msg.node.mtext, str);
		msg.mtype = 1;
		msgsnd(msgqid, &msg, sizeof(msg.node), 0);	//发送数据到服务器端

		msgrcv(msgqid, &msg, sizeof(msg.node), 1, 0);  //从服务器端接收数据
		printf("%s\n", msg.node.mtext);

		puts("Enter 3 return to the main page");
		int num = 1;
		while (num != 3) {
			scanf("%d", &num);
		}

		goto MPAGE;
	}

	else if (str[0] == '1')
	{					                    //销售
	CALLSHOP:	callShopping();
		char op[3][3];
		int number[3];
		int kind = 0;			       		//用于选择饮料
//		double _price;					
		double clientMoney;				    //the consumer pay money
		double sumPrice = 0;     			//总价钱

		struct msgform msg;					//发送售卖信息前往服务端
		int msgqid;
		msgqid = msgget(MSGKEY, 0777);
		msg.node.flag = 2;

		msg.node.na = 0;
		msg.node.nb = 0;
		msg.node.nc = 0;

		while (1) {					//购买环节
			puts("请输入您想要的商品的编号（按“q”退出）:");
		SCANFKIND:			scanf("%s", op[kind]);
			if (op[kind][0] != 'a' && op[kind][0] != 'b' && op[kind][0] != 'c' && op[kind][0] != 'q') {
				puts("查无此命令，请检查后输入");
				goto SCANFKIND;
			}

			if (op[kind][0] == 'q')	break;
			puts("请输入您想要购买的数量:");
			scanf("%d", &number[kind]);
			if (op[kind][0] == 'a') {			//可可	
				clientMoney = 2.5;
				msg.node.na = number[kind];
			}
			else if (op[kind][0] == 'b') {		//橙汁
				clientMoney = 2.5;
				msg.node.nb = number[kind];
			}
			else {					//热牛奶
				clientMoney = 4.0;
				msg.node.nc = number[kind];
			}
			sumPrice += clientMoney * number[kind];	//计算总价值
			kind++;
		}

		int ii;
		puts("这是您想要购买的饮料: ");					//显示购买信息
		for (ii = 0; ii < kind; ++ii) {
			if (op[ii][0] == 'a')	printf("可可:	");
			else if (op[ii][0] == 'b')	printf("橙汁:	");
			else printf("热牛奶:	");
			printf("%d\n", number[ii]);
		}
		printf("您总共需要付 %.1lf 元\n", sumPrice);

		puts("按下“e”键确认您的订单。按下其他键修改您的订单:");//订单确认
		char ensure[5];
		scanf("%s", ensure);
		if (ensure[0] == 'e' || ensure[0] == 'E');
		else goto CALLSHOP;

		puts("请支付:");	//支付
		scanf("%lf", &clientMoney);
		while (clientMoney < sumPrice) {
			puts("抱歉，资金不足，请重新输入");
			double temp;
			scanf("%lf", &temp);
			clientMoney += temp;
		}

		msg.node.sumPrice = sumPrice;
		msg.node.clientMoney = clientMoney;
		msg.mtype = 1;
		msgsnd(msgqid, &msg, sizeof(msg.node), 0);

		msgrcv(msgqid, &msg, sizeof(msg.node), 1, 0);		//找零
		numA = msg.node.na;
		numB = msg.node.nb;
		numC = msg.node.nc;

		printf("找零 %s 元\n", msg.node.chg);

		puts("请输入“y”确认您的订单");		//等待确认
		char last[2] = "a";
		while (1) {
			scanf("%s", last);
			if (last[0] == 'y' || last[0] == 'Y') {
				callComment();
				callLastPrint();
				sleep(3);
				goto MPAGE;
			}
		}
	}
	else if (str[0] == '3') {
		callLogin();
		goto MPAGE;
	}
	else goto MPAGE;
}