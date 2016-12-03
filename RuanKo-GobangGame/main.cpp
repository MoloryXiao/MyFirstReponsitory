#include <iostream>
#include <stdio.h>
#include <string>
#include "Menu.h"
#include "ChessBoard.h"
#include "Player.h"
#include "Chess.h"
#include "Ranking.h"
using namespace std;

int GamesGo(Player &p1, Player &p2, ChessBoard &cb);		//游戏开始 返回值为1则某方获胜 为0则和棋
int GamesRanking();						//排行榜内的操作

Ranking rankBoard;			//创建一个排行榜对象

int main()
{
	rankBoard.ReadFromFile();		//从文件流中读入历史记录

	char choice;
	bool running = true;
	while(running)
	{
		system("cls");
		SayHello();
		ShowMainMenu();
		cout<<endl<<"请输入选项（1/2/3/4/5/0）：";
		cin>>choice;
		cin.ignore(1024,'\n');
		switch ( choice )
		{
		case '0':			//退出
			system("cls");
			running = false;		//循环标识置否
			SayGoodbye();			//打印结束
			break;
		case '1':			//新建游戏
			{
			Player p1;			//创建玩家1
			Player p2;			//创建玩家2
			ChessBoard cb(15,15);		//创建棋盘
			GamesGo(p1,p2,cb);		//游戏开始
			break;
			}
		case '2':			//加载游戏
			cout<<"暂未开放！"<<endl;
			break;
		case '3':			//排行榜
			GamesRanking();
			break;
		case '4':			//游戏规则
			SayHello();
			cout<<"4"<<endl;
			break;
		case '5':			//关于我们
			system("cls");
			SayHello();
			ShowAboutUs();
			break;
		default:
			cout<<"您的输入有误！请检查输入！"<<endl;
			break;
		}
		system("pause");
	}
	return 0;
}
int GamesGo(Player &p1, Player &p2, ChessBoard &cb)		//游戏开始 返回值为1则某方获胜 为0则和棋
{
	string pName1,pName2;			//player name
	system("cls");
	cout<<"请输入玩家Player1的昵称(不含空格)：";
	cin>>pName1;
	cout<<"请输入玩家Player2的昵称(不含空格)：";
	cin>>pName2;
	p1.SetName(pName1);
	p2.SetName(pName2);

	int status = -1;		//棋子状态 1为白棋，-1为黑棋，五子棋为黑棋先手
	bool isPopChess = false;			//是否可以悔棋
	while( ! cb.IsBoardFull() )
	{
		system("cls");
		char x;				//字符型行坐标
		int chessX=0 , chessY=0;					//初始化棋子位置
		bool gameWin = false;					//初始化棋盘胜负
		ShowGameGoTitle();						//显示游戏开始头部
		cb.ShowBoard(gameWin);				//展示棋盘

		cout<<"【黑方："<<p1.GetName()<<"】VS【白方："<<p2.GetName()<<"】"<<endl
			<<"【注】输入' 00 '：退出游戏\t";
		if(cb.GetChessNum()!=0)			//还没落子前，不输出这句话
			cout<<"输入' -1 '：悔棋"<<endl<<endl;
		else cout<<endl<<endl;

		//提示输入
		cout<<"请";
		if(status == -1) cout<<"黑方输入落子位置(例-C5)：";
		else cout<<"白方输入落子位置(例-C5)：";
		cin>>x>>chessY;		

		//退出游戏判断
		if(x == '0' && chessY == 0)			
		{
			cout<<"退出游戏~返回主菜单..."<<endl;
			return 1;
		}
		//悔棋判断（棋盘初始时不可以悔棋，已经悔棋一次的不可以再次悔棋）
		if(x == '-' && chessY == 1 && cb.GetChessNum()!=0 )			
		{
			if(isPopChess == true)
			{
				status = -status;			//执子方重置
				if(status == -1)			//棋手的棋路中弹出该棋子
					p1.PopChess();
				else 
					p2.PopChess();
				cb.PopChess();				//棋盘也弹出该棋子
				isPopChess = false;		//悔棋状态改为false
			}
			else
			{
				cout<<"操作失败！只允许悔棋一次！"<<endl;	
				system("pause");
			}
		}else			//正常落子
		{
			if(x>='a' && x<='z')			//小写输入的转换
				chessX = x-'a';
			else if(x>='A' && x<='Z')	//大写输入的转换
				chessX = x-'A';			
			else chessX = -1;			//其他错误输入，置于-1

			Chess c (chessX,chessY,status) ;			//创建棋子

			//将棋子添加到棋盘中并保存至棋手的棋路谱中
			int res = 0;				//初始化落子情况 0为落子失败 1为落子成功
			if(status == -1) 
				res = p1.PushChess(c,cb);							
			else if(status == 1)
				res = p2.PushChess(c,cb);

			if(res == 0)			//落子失败
			{
				cout<<"落子位置有误！请检查您的输入！"<<endl;
				system("pause");
			}else						//落子成功
			{
				isPopChess = true;			//正确落子，悔棋状态置为真
				if( cb.IsBoardWin(c) )
				{
					gameWin = true;
					Record newRec;
					system("cls");
					ShowGameEndTitle();					//显示游戏结束头部
					cb.ShowBoard(gameWin);			//再打印一次最后棋盘
					if(status == -1)			//当前状态为黑子，则p1获胜
					{
						rankBoard.InsertRec(cb,p1.GetName());		//插入新纪录
						p1.SetWin(true);
					}
					else 
					{
						rankBoard.InsertRec(cb,p2.GetName());		//插入新纪录
						p2.SetWin(true);
					}
					cout<<"游戏结束！";
					if(p1.GetWin()) cout<<p1.GetName()<<"获胜！"<<endl<<endl;
					else cout<<p2.GetName()<<"获胜！"<<endl<<endl;
					rankBoard.WriteToFile();			//保存记录
					return 1;			//游戏结束
				}else
					status = -status;		//若还没决出胜负，则变换棋色继续游戏
			}
		}
	}
	cout<<"<< 和棋 >>"<<endl;		//若棋盘已满则和棋
	return 0;
}
int GamesRanking()						//排行榜内的操作
{
	system("cls");
	ShowRankTitle();					//显示排行榜头部
	rankBoard.ShowRank();		//打印排行榜内容
	char numCharIn[20];			//创建字符数组接收输入 
	cout<<"输入排名编号可显示该编号棋盘的最后战况（输入0返回主界面）：";
	cin>>numCharIn;				
	for(int i=0;i<strlen(numCharIn);i++)			//如果输入包含除数字的其他字符，则提示错误并返回
	{
		if( ! (numCharIn[i]>='0' && numCharIn[i]<='9') )
		{
			cout<<endl<<"您的输入有误！即将返回主页面！"<<endl<<endl;
			return 0;
		}
	}
	int numIntIn = atoi(numCharIn);			//将输入转化为int
	if(numIntIn>rankBoard.GetRankLen() || numIntIn<0)			//如果输入的数字大于排行榜的项目数或小于0
	{
		cout<<endl<<"您的输入有误！即将返回主页面！"<<endl<<endl;
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