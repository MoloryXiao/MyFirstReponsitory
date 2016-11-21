#include <iostream>
#include <stdio.h>
#include <string>
#include "Menu.h"
#include "ChessBoard.h"
#include "Player.h"
#include "Chess.h"
using namespace std;

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
	while( ! cb.IsBoardFull() )
	{
		system("cls");
		char x;				//字符型行坐标
		int chessX=0 , chessY=0;					//初始化棋子位置
		cb.ShowBoard();								//展示棋盘

		//提示输入
		cout<<"请";
		if(status == -1) cout<<"黑方输入落子位置(例-C5)：";				
		else cout<<"白方输入落子位置(例-C5)：";

		cin>>x>>chessY;			
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
			if( cb.IsBoardWin(c) )
			{
				system("cls");
				cb.ShowBoard();			//再打印一次最后棋盘
				if(status == -1)			//当前状态为黑子，则p1获胜
					p1.SetWin(true);
				else 
					p2.SetWin(true);
				cout<<"游戏结束！";
				if(p1.GetWin()) cout<<p1.GetName()<<"获胜！"<<endl<<endl;
				else cout<<p2.GetName()<<"获胜！"<<endl<<endl;
				return 1;			//游戏结束
			}else
				status = -status;		//若还没决出胜负，则变换棋色继续游戏
		}
	}
	cout<<"<< 和棋 >>"<<endl;		//若棋盘已满则和棋
	return 0;
}
int main()
{

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
			running = false;
			SayGoodbye();
			break;
		case '1':			//新建游戏
			{
			Player p1;
			Player p2;
			ChessBoard cb(15,15);
			GamesGo(p1,p2,cb);		//游戏开始
			break;
			}
		case '2':			//加载游戏
			cout<<"暂未开放！"<<endl;
			break;
		case '3':			//排行榜
			cout<<"暂未开放！"<<endl;
			break;
		case '4':			//游戏规则
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