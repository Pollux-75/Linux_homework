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

void callShopping()
{					                     //商品界面

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
	puts("                         *         *          *                                  ");
	puts("                          *        *         *                                   ");
	puts("                           *       *        *                                    ");
	puts("                            *      *       *                                     ");
	puts("              ********************************************                       ");
	puts("             |                                            |                      ");
	puts("             |                                            |                      ");
	puts("             |           *                   *            |                      ");
	puts("             |          * *                 * *           |                      ");
	puts("     ********|         *   *               *   *          |*********             ");
	puts("     *       |        *     *             *     *         |        *             ");
	puts("     *       |                                            |        *             ");
	puts("     *       |                                            |        *             ");
	puts("     *       |                                            |        *             ");
	puts("     *       |           ********************             |        *             ");
	puts("     ********|            *  *  *    *  *  *              |*********             ");
	puts("             |             * *  *    *  * *               |                      ");
	puts("             |              **  *    *  **                |                      ");
	puts("             |               ************                 |                      ");
	puts("             |                                            |                      ");
	puts("             |                                            |                      ");
	puts("             **********************************************                      ");
	puts("                                                                                 ");
	puts("================================================================================");
	puts("                      谢谢惠顾 欢迎您的下次光临！！！                           ");
	puts("================================================================================");
}