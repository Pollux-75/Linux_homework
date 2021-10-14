#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#define message_key 75

/*��㣬����״̬*/
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

/*��Ϣ��ʽ*/
struct msgform
{
	long mtype;
	Node node;
}msg;

int numA, numB, numC;
char comm[4][10] = { "good", "normal", "soso", "bad" };  

/*������UI*/
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
	puts("    Enter '1' : ��ʼ����	 Enter '2' : ����       ");
	puts("	           Enter '3' ����Ա��¼                 ");
	puts("==================================================");
};

void callShopping()
{					                     //��Ʒ����

	struct msgform msg;					//�������������Ϣ
	int msgqid;
	msgqid = msgget(message_key, 0777);
	msg.node.flag = 3;
	msg.mtype = 1;
	msgsnd(msgqid, &msg, sizeof(msg.node), 0);
	msgrcv(msgqid, &msg, sizeof(msg.node), 1, 0);		//����number����

	numA = msg.node.na;
	numB = msg.node.nb;
	numC = msg.node.nc;

	puts("=============================================================");
	printf("                   ��ζ��Ʒ   ��ӭƷ��                     ");
	printf("\n");
	puts("=============================================================");
	printf("\n");
	printf("  a : �ɿ�               ����  2.5$   Number : %d\n\n", numA);
	printf("  b : ��֭               ����  2.5$   Number : %d\n\n", numB);
	printf("  c : ��ţ��             ����  4.0$   Number : %d\n\n", numC);
	puts("=============================================================");
}

/*��������*/
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
	puts("                      лл�ݹ� ��ӭ�����´ι��٣�����                           ");
	puts("================================================================================");
}