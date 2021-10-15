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

/*��Ʒҳ��*/
void callShopping()
{					                   

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
	puts("                      лл�ݹ� ��ӭ�����´ι��٣�����                           ");
	puts("================================================================================");
}

/*����Ա����UI*/
void adminGUI() {
	puts("**********************************************");
	puts("*                                            *");
	puts("*           1 : �����̵�ҳ��                 *");
	puts("*                                            *");
	puts("*           2 : ���������Ϣ                 *");
	puts("*                                            *");
	puts("*          ����������˳���ҳ��	           *");
	puts("**********************************************");
	puts("��������������1��2��");
}

void callManage() {
	adminGUI();
	int order;
	while (scanf("%d", &order))
	{
		struct msgform msg;					//��������Ϣ���������
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
				puts("�ɹ����£�");
			}
			else puts("����ʧ��!");

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

/*��¼ϵͳ*/
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
		puts("�����������û����� ");
		scanf("%s", name);
		puts("��������������: ");
		scanf("%s", pwd);
		strcpy(msg.node.username, name);
		strcpy(msg.node.password, pwd);
		msgsnd(msgqid, &msg, sizeof(msg.node), 0);
		msgrcv(msgqid, &msg, sizeof(msg.node), 1, 0);
		int isRight;
		isRight = msg.node.isRight;
		if (isRight == 0) 
		{
			puts("�û����������������������");
		 	if (++count >= 3)	return;                //�������κ���ֹ����      
		}
		else break;
	}
	callManage();
}

/*����ҳ��*/
void callComment() {
	puts("===========================================================");
	puts("===========================================================");
	puts("|          ���������Դ�ϵͳ�����ۣ���                     |");
	puts("|                                                         |");
	puts("|            *                                            |");
	puts("|           * *                                           |");
	puts("|          *****                  1 : ������              |");
	puts("|  * *   * *O O* *    * *                                 |");
	puts("| *   *    | W |     *   *        2 : ����              |");
	puts("|   \ \     ---      / /                                  |");
	puts("|    \ \   *....*   / /           3 : һ�㣡              |");
	puts("|     \ \ *......* / /                                    |");
	puts("|       \*........*/              4 : ������              |");
	puts("|       *..........*                                      |");
	puts("|      *............*                                     |");
	puts("|     *..............*                                    |");
	puts("|    ******      ******                                   |");
	puts("|         / /  \ \                                        |");
	puts("|         | |  | |                                        |");
	puts("|         | |  | |                  лл��������!!!       |");
	puts("===========================================================");
	puts("===========================================================");
	puts("���ڴ�ҳ�������������ۣ�0��4��������");

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
	if (str[0] == '2') {					//�������
		struct msgform msg;
		int msgqid;
		msgqid = msgget(message_key, 0777);			//������Ϣ����
		msg.node.flag = 1;
		strcpy(msg.node.mtext, str);
		msg.mtype = 1;
		msgsnd(msgqid, &msg, sizeof(msg.node), 0);	//�������ݵ���������

		msgrcv(msgqid, &msg, sizeof(msg.node), 1, 0);  //�ӷ������˽�������
		printf("%s\n", msg.node.mtext);

		puts("Enter 3 return to the main page");
		int num = 1;
		while (num != 3) {
			scanf("%d", &num);
		}

		goto MPAGE;
	}

	else if (str[0] == '1')
	{					                    //����
	CALLSHOP:	callShopping();
		char op[3][3];
		int number[3];
		int kind = 0;			       		//����ѡ������
//		double _price;					
		double clientMoney;				    //the consumer pay money
		double sumPrice = 0;     			//�ܼ�Ǯ

		struct msgform msg;					//����������Ϣǰ�������
		int msgqid;
		msgqid = msgget(MSGKEY, 0777);
		msg.node.flag = 2;

		msg.node.na = 0;
		msg.node.nb = 0;
		msg.node.nc = 0;

		while (1) {					//���򻷽�
			puts("����������Ҫ����Ʒ�ı�ţ�����q���˳���:");
		SCANFKIND:			scanf("%s", op[kind]);
			if (op[kind][0] != 'a' && op[kind][0] != 'b' && op[kind][0] != 'c' && op[kind][0] != 'q') {
				puts("���޴�������������");
				goto SCANFKIND;
			}

			if (op[kind][0] == 'q')	break;
			puts("����������Ҫ���������:");
			scanf("%d", &number[kind]);
			if (op[kind][0] == 'a') {			//�ɿ�	
				clientMoney = 2.5;
				msg.node.na = number[kind];
			}
			else if (op[kind][0] == 'b') {		//��֭
				clientMoney = 2.5;
				msg.node.nb = number[kind];
			}
			else {					//��ţ��
				clientMoney = 4.0;
				msg.node.nc = number[kind];
			}
			sumPrice += clientMoney * number[kind];	//�����ܼ�ֵ
			kind++;
		}

		int ii;
		puts("��������Ҫ���������: ");					//��ʾ������Ϣ
		for (ii = 0; ii < kind; ++ii) {
			if (op[ii][0] == 'a')	printf("�ɿ�:	");
			else if (op[ii][0] == 'b')	printf("��֭:	");
			else printf("��ţ��:	");
			printf("%d\n", number[ii]);
		}
		printf("���ܹ���Ҫ�� %.1lf Ԫ\n", sumPrice);

		puts("���¡�e����ȷ�����Ķ����������������޸����Ķ���:");//����ȷ��
		char ensure[5];
		scanf("%s", ensure);
		if (ensure[0] == 'e' || ensure[0] == 'E');
		else goto CALLSHOP;

		puts("��֧��:");	//֧��
		scanf("%lf", &clientMoney);
		while (clientMoney < sumPrice) {
			puts("��Ǹ���ʽ��㣬����������");
			double temp;
			scanf("%lf", &temp);
			clientMoney += temp;
		}

		msg.node.sumPrice = sumPrice;
		msg.node.clientMoney = clientMoney;
		msg.mtype = 1;
		msgsnd(msgqid, &msg, sizeof(msg.node), 0);

		msgrcv(msgqid, &msg, sizeof(msg.node), 1, 0);		//����
		numA = msg.node.na;
		numB = msg.node.nb;
		numC = msg.node.nc;

		printf("���� %s Ԫ\n", msg.node.chg);

		puts("�����롰y��ȷ�����Ķ���");		//�ȴ�ȷ��
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