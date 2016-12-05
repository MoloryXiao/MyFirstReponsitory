#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <iomanip>
#include "Menu.h"
#include "ChessBoard.h"
#include "Player.h"
#include "Chess.h"
#include "Ranking.h"
#include "History.h"
using namespace std;

/*��Ϸ��� �����Ƿ�浵���д���*/
void StartGame(HistoryRec &newRec);
/*��Ϸ��ʼ ����ֵΪ1��ĳ����ʤ Ϊ0����� ����-1��ʾ��Ҫ���� -9��ʾ����Ҫ����*/
int GamesGo(Player &p1, Player &p2, ChessBoard &cb);	
/*������Ϸ*/
int GamesLoad();
/*���а����*/
int GamesRanking();	
/*��ȡ��Ϸ�浵*/
void LoadGameRec();
/*�ϴ���Ϸ�浵*/
void UploadGameRec();

Ranking rankBoard;									//����һ�����а����
vector<HistoryRec> loadGameVec;		//����һ��������Ϸ��vector

int main()
{
	rankBoard.ReadFromFile();		//���ļ����ж�����ʷ��¼
	LoadGameRec();						//������Ϸ����ļ�¼

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
				HistoryRec newRec;
				string pName1,pName2;			//player name
				system("cls");
				cout<<"���������Player1���ǳ�(�����ո�)��";
				cin>>pName1;
				cout<<"���������Player2���ǳ�(�����ո�)��";
				cin>>pName2;
				newRec.p1.SetName(pName1);
				newRec.p2.SetName(pName2);	
				StartGame(newRec);
			break;
			}
		case '2':			//������Ϸ
			GamesLoad();
			break;
		case '3':			//���а�
			GamesRanking();
			break;
		case '4':			//��Ϸ����
			system("cls");
			SayGameRules();
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
/*��Ϸ��� �����Ƿ�浵���д���*/
void StartGame(HistoryRec &newRec)
{
	int res = GamesGo(newRec.p1,newRec.p2,newRec.cb);		//��Ϸ��ʼ
	if(res == -1) 
	{
		/*��ȡ��ǰʱ��*/
		time_t timeGet;
		time(&timeGet);
		struct tm *now=localtime(&timeGet);
		newRec.saveTime = asctime(now);
		/*�Ի�ȡ��ʱ����д���*/
		int pos = newRec.saveTime.find(" ",0);
		newRec.saveTime.erase(0,pos+1);		//ȥ������
		newRec.saveTime.erase(newRec.saveTime.length()-6,newRec.saveTime.length());		//ȥ�����

		loadGameVec.push_back(newRec);		//����	
		UploadGameRec();								//�浵
		cout<<endl<<"�浵�ɹ������ڷ������˵�...."<<endl;
	}
}
/*��Ϸ���� ����ֵΪ1��ĳ����ʤ Ϊ0����� ����-1��ʾ��Ҫ���� -9��ʾ����Ҫ����*/
int GamesGo(Player &p1, Player &p2, ChessBoard &cb)		
{
	int status = -1;		//����״̬ 1Ϊ���壬-1Ϊ���壬������Ϊ��������
	bool isPopChess = false;			//�Ƿ���Ի���
	if(cb.GetChessNum()!=0)			//�����ǻص���������Ϸ ���Ի���
		isPopChess = true;
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
		if(cb.GetChessNum()!=0)				//��û����ǰ���������仰
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
			int isAnswerTrue = 0;		//�ж������Ƿ�淶
			do{
				char answer[20];
				cout<<"�Ƿ�浵����Ϸ��Y/N"<<endl;
				cin>>answer;
				if( (answer[0]!='Y' && answer[0]!='N') || answer[1]!='\0' )		//���벻�淶�����
				{
					isAnswerTrue = 0;
					cout<<"���������������������룡"<<endl<<endl;
				}else		//����淶�����
				{
					if( answer[0] == 'Y') isAnswerTrue = 1;
					else if(answer[0] == 'N') isAnswerTrue = 2;
				}
			}while( ! isAnswerTrue);
			if(isAnswerTrue == 1)		//����������yes �򷵻�-1���д浵
				return -1;
			else			//�������no
			{
				cout<<endl<<"��Ϸ���������ڷ������˵�..."<<endl;
				return -9;
			}
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

/*���а����*/
int GamesRanking()						//���а��ڵĲ���
{
	system("cls");
	ShowRankTitle();					//��ʾ���а�ͷ��
	rankBoard.ShowRank();		//��ӡ���а�����
	char numCharIn[20];			//�����ַ������������ 
	cout<<"����������ſ���ʾ�ñ�����̵����ս��������0���������棩��";
	cin>>numCharIn;				
	for(unsigned int i=0;i<strlen(numCharIn);i++)			//���������������ֵ������ַ�������ʾ���󲢷���
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

/*������Ϸ*/
int GamesLoad()
{
	system("cls");
	LoadGameTitle();
	int vecLen = loadGameVec.size();
	if(vecLen == 0 )		//û���κμ�¼
	{
		cout<<"\t\t    ��"<<endl<<endl;
		return 1;
	}else
	{
		cout<<setw(5)<<"���"<<setw(10)<<"�ڷ�"<<setw(8)<<"��ս"<<setw(10)<<"�׷�"<<setw(18)<<"�浵ʱ��"<<endl;
		cout<<"---------------------------------------------------"<<endl;
		for(unsigned int i=0;i<vecLen;i++)
		{
			HistoryRec theRec = loadGameVec[i];
			cout<<setw(5)<<i+1<<setw(10)<<theRec.p1.GetName()<<setw(8)<<" VS "<<setw(10)<<
				theRec.p2.GetName()<<setw(18)<<theRec.saveTime<<endl;
		}
		cout<<endl;
		char choice_char[20];
		cout<<"�������Ӧ��ţ�������Ϸ������0���أ���";
		cin>>choice_char;

		int choice_int = atoi(choice_char);
		if(choice_int == 0) return 1;
		if(choice_int <1 || choice_int >loadGameVec.size() )
		{
			cout<<"�������������������룡"<<endl;
			return 1;
		}
		cout<<endl;
		
		HistoryRec newRec = loadGameVec[choice_int-1];		//����Ҫ�´���һ����¼����Ϊ��һ�����Ϊ����
		StartGame(newRec);			//������Ϸ
		return 1;
	}
}

/*��ȡ��Ϸ�浵*/
void LoadGameRec()
{
	ifstream ifs("HistoryRec.data");
	int recNum =0;		//������Ϸ����Ŀ��
	ifs>>recNum;			//��������

	for(int i=0;i<recNum;i++)			//ѭ�������¼�¼�� loadGameVec��
	{
		HistoryRec newRec;					//����һ����ʷ��¼
		string p1Name,p2Name;			//ÿ����¼�����������
		int p1ChessNum=0 , p2ChessNum = 0;			//������
		
		ifs>>p1Name>>p1ChessNum;		//�������1���ֺ������µ�������
		ifs>>p2Name>>p2ChessNum;		//�������2���ֺ������µ�������
		newRec.p1.SetName(p1Name);		//���ú���ҵ�����
		newRec.p2.SetName(p2Name);		
		for(int j=0;j<p1ChessNum+p2ChessNum;j++)		//ѭ����������
		{
			int chessX,chessY,chessColor;		
			ifs>>chessX>>chessY>>chessColor;
			Chess newChess(chessX,chessY,chessColor);		//�����������ɫ����һ������
			if(j%2==0)			//ż������p1��������
				newRec.p1.PushChess(newChess,newRec.cb);
			else						//��������p2��������
				newRec.p2.PushChess(newChess,newRec.cb);
		}
		ifs.get();		//����һ�����з�
		getline(ifs,newRec.saveTime);		//����ʱ��
		loadGameVec.push_back(newRec);			//���¼�¼ѹ��vector��
	}
	ifs.close();
}

/*�ϴ���Ϸ�浵*/
void UploadGameRec()			//д���ļ���
{
	ofstream ofs("HistoryRec.data");
	ofs<<loadGameVec.size()<<endl;
	int loadLen = loadGameVec.size();
	for(int i=0;i<loadLen;i++)
	{
		ofs<<loadGameVec[i].p1.GetName()<<" "<<loadGameVec[i].p1.GetChessNum()<<endl
			<<loadGameVec[i].p2.GetName()<<" "<<loadGameVec[i].p2.GetChessNum()<<endl;
		int chessNum = loadGameVec[i].cb.GetChessNum();
		for(int j=0 ; j<chessNum ; j++)
		{
			Chess c = loadGameVec[i].cb.GetTheChess(j);		//��ȡ�����еĵ�j������
			ofs<<c.GetX()<<" "<<c.GetY()<<" "<<c.GetColor()<<endl;
		}
		ofs<<loadGameVec[i].saveTime<<endl;
	}
	ofs.close();
}