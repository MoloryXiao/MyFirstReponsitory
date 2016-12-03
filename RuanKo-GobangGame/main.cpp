#include <iostream>
#include <stdio.h>
#include <string>
#include "Menu.h"
#include "ChessBoard.h"
#include "Player.h"
#include "Chess.h"
#include "Ranking.h"
using namespace std;

int GamesGo(Player &p1, Player &p2, ChessBoard &cb);		//��Ϸ��ʼ ����ֵΪ1��ĳ����ʤ Ϊ0�����
int GamesRanking();						//���а��ڵĲ���

Ranking rankBoard;			//����һ�����а����

int main()
{
	rankBoard.ReadFromFile();		//���ļ����ж�����ʷ��¼

	char choice;
	bool running = true;
	while(running)
	{
		system("cls");
		SayHello();
		ShowMainMenu();
		cout<<endl<<"������ѡ�1/2/3/4/5/0����";
		cin>>choice;
		cin.ignore(1024,'\n');
		switch ( choice )
		{
		case '0':			//�˳�
			system("cls");
			running = false;		//ѭ����ʶ�÷�
			SayGoodbye();			//��ӡ����
			break;
		case '1':			//�½���Ϸ
			{
			Player p1;			//�������1
			Player p2;			//�������2
			ChessBoard cb(15,15);		//��������
			GamesGo(p1,p2,cb);		//��Ϸ��ʼ
			break;
			}
		case '2':			//������Ϸ
			cout<<"��δ���ţ�"<<endl;
			break;
		case '3':			//���а�
			GamesRanking();
			break;
		case '4':			//��Ϸ����
			SayHello();
			cout<<"4"<<endl;
			break;
		case '5':			//��������
			system("cls");
			SayHello();
			ShowAboutUs();
			break;
		default:
			cout<<"�������������������룡"<<endl;
			break;
		}
		system("pause");
	}
	return 0;
}
int GamesGo(Player &p1, Player &p2, ChessBoard &cb)		//��Ϸ��ʼ ����ֵΪ1��ĳ����ʤ Ϊ0�����
{
	string pName1,pName2;			//player name
	system("cls");
	cout<<"���������Player1���ǳ�(�����ո�)��";
	cin>>pName1;
	cout<<"���������Player2���ǳ�(�����ո�)��";
	cin>>pName2;
	p1.SetName(pName1);
	p2.SetName(pName2);

	int status = -1;		//����״̬ 1Ϊ���壬-1Ϊ���壬������Ϊ��������
	bool isPopChess = false;			//�Ƿ���Ի���
	while( ! cb.IsBoardFull() )
	{
		system("cls");
		char x;				//�ַ���������
		int chessX=0 , chessY=0;					//��ʼ������λ��
		bool gameWin = false;					//��ʼ������ʤ��
		ShowGameGoTitle();						//��ʾ��Ϸ��ʼͷ��
		cb.ShowBoard(gameWin);				//չʾ����

		cout<<"���ڷ���"<<p1.GetName()<<"��VS���׷���"<<p2.GetName()<<"��"<<endl
			<<"��ע������' 00 '���˳���Ϸ\t";
		if(cb.GetChessNum()!=0)			//��û����ǰ���������仰
			cout<<"����' -1 '������"<<endl<<endl;
		else cout<<endl<<endl;

		//��ʾ����
		cout<<"��";
		if(status == -1) cout<<"�ڷ���������λ��(��-C5)��";
		else cout<<"�׷���������λ��(��-C5)��";
		cin>>x>>chessY;		

		//�˳���Ϸ�ж�
		if(x == '0' && chessY == 0)			
		{
			cout<<"�˳���Ϸ~�������˵�..."<<endl;
			return 1;
		}
		//�����жϣ����̳�ʼʱ�����Ի��壬�Ѿ�����һ�εĲ������ٴλ��壩
		if(x == '-' && chessY == 1 && cb.GetChessNum()!=0 )			
		{
			if(isPopChess == true)
			{
				status = -status;			//ִ�ӷ�����
				if(status == -1)			//���ֵ���·�е���������
					p1.PopChess();
				else 
					p2.PopChess();
				cb.PopChess();				//����Ҳ����������
				isPopChess = false;		//����״̬��Ϊfalse
			}
			else
			{
				cout<<"����ʧ�ܣ�ֻ�������һ�Σ�"<<endl;	
				system("pause");
			}
		}else			//��������
		{
			if(x>='a' && x<='z')			//Сд�����ת��
				chessX = x-'a';
			else if(x>='A' && x<='Z')	//��д�����ת��
				chessX = x-'A';			
			else chessX = -1;			//�����������룬����-1

			Chess c (chessX,chessY,status) ;			//��������

			//��������ӵ������в����������ֵ���·����
			int res = 0;				//��ʼ��������� 0Ϊ����ʧ�� 1Ϊ���ӳɹ�
			if(status == -1) 
				res = p1.PushChess(c,cb);							
			else if(status == 1)
				res = p2.PushChess(c,cb);

			if(res == 0)			//����ʧ��
			{
				cout<<"����λ�����������������룡"<<endl;
				system("pause");
			}else						//���ӳɹ�
			{
				isPopChess = true;			//��ȷ���ӣ�����״̬��Ϊ��
				if( cb.IsBoardWin(c) )
				{
					gameWin = true;
					Record newRec;
					system("cls");
					ShowGameEndTitle();					//��ʾ��Ϸ����ͷ��
					cb.ShowBoard(gameWin);			//�ٴ�ӡһ���������
					if(status == -1)			//��ǰ״̬Ϊ���ӣ���p1��ʤ
					{
						rankBoard.InsertRec(cb,p1.GetName());		//�����¼�¼
						p1.SetWin(true);
					}
					else 
					{
						rankBoard.InsertRec(cb,p2.GetName());		//�����¼�¼
						p2.SetWin(true);
					}
					cout<<"��Ϸ������";
					if(p1.GetWin()) cout<<p1.GetName()<<"��ʤ��"<<endl<<endl;
					else cout<<p2.GetName()<<"��ʤ��"<<endl<<endl;
					rankBoard.WriteToFile();			//�����¼
					return 1;			//��Ϸ����
				}else
					status = -status;		//����û����ʤ������任��ɫ������Ϸ
			}
		}
	}
	cout<<"<< ���� >>"<<endl;		//���������������
	return 0;
}
int GamesRanking()						//���а��ڵĲ���
{
	system("cls");
	ShowRankTitle();					//��ʾ���а�ͷ��
	rankBoard.ShowRank();		//��ӡ���а�����
	char numCharIn[20];			//�����ַ������������ 
	cout<<"����������ſ���ʾ�ñ�����̵����ս��������0���������棩��";
	cin>>numCharIn;				
	for(int i=0;i<strlen(numCharIn);i++)			//���������������ֵ������ַ�������ʾ���󲢷���
	{
		if( ! (numCharIn[i]>='0' && numCharIn[i]<='9') )
		{
			cout<<endl<<"�����������󣡼���������ҳ�棡"<<endl<<endl;
			return 0;
		}
	}
	int numIntIn = atoi(numCharIn);			//������ת��Ϊint
	if(numIntIn>rankBoard.GetRankLen() || numIntIn<0)			//�����������ִ������а����Ŀ����С��0
	{
		cout<<endl<<"�����������󣡼���������ҳ�棡"<<endl<<endl;
		return 0;
	}else
	{
		switch(numIntIn)
		{
		case 0:
			return 1;
		default:
			system("cls");
			BoardReappearTitle();
			rankBoard.ShowTheBoard(numIntIn);
			return 1;	
		}
	}
}