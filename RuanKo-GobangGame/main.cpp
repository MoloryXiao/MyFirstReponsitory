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

/*游戏入口 并对是否存档进行处理*/
void StartGame(HistoryRec &newRec);
/*游戏开始 返回值为1则某方获胜 为0则和棋 返回-1表示需要存盘 -9表示不需要存盘*/
int GamesGo(Player &p1, Player &p2, ChessBoard &cb);	
/*加载游戏*/
int GamesLoad();
/*排行榜操作*/
int GamesRanking();	
/*读取游戏存档*/
void LoadGameRec();
/*上传游戏存档*/
void UploadGameRec();

Ranking rankBoard;									//创建一个排行榜对象
vector<HistoryRec> loadGameVec;		//创建一个加载游戏的vector

int main()
{
	rankBoard.ReadFromFile();		//从文件流中读入历史记录
	LoadGameRec();						//加载游戏保存的记录

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
				HistoryRec newRec;
				string pName1,pName2;			//player name
				system("cls");
				cout<<"请输入玩家Player1的昵称(不含空格)：";
				cin>>pName1;
				cout<<"请输入玩家Player2的昵称(不含空格)：";
				cin>>pName2;
				newRec.p1.SetName(pName1);
				newRec.p2.SetName(pName2);	
				StartGame(newRec);
			break;
			}
		case '2':			//加载游戏
			GamesLoad();
			break;
		case '3':			//排行榜
			GamesRanking();
			break;
		case '4':			//游戏规则
			system("cls");
			SayGameRules();
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
/*游戏入口 并对是否存档进行处理*/
void StartGame(HistoryRec &newRec)
{
	int res = GamesGo(newRec.p1,newRec.p2,newRec.cb);		//游戏开始
	if(res == -1) 
	{
		/*获取当前时间*/
		time_t timeGet;
		time(&timeGet);
		struct tm *now=localtime(&timeGet);
		newRec.saveTime = asctime(now);
		/*对获取的时间进行处理*/
		int pos = newRec.saveTime.find(" ",0);
		newRec.saveTime.erase(0,pos+1);		//去除星期
		newRec.saveTime.erase(newRec.saveTime.length()-6,newRec.saveTime.length());		//去除年份

		loadGameVec.push_back(newRec);		//存盘	
		UploadGameRec();								//存档
		cout<<endl<<"存档成功！正在返回主菜单...."<<endl;
	}
}
/*游戏主体 返回值为1则某方获胜 为0则和棋 返回-1表示需要存盘 -9表示不需要存盘*/
int GamesGo(Player &p1, Player &p2, ChessBoard &cb)		
{
	int status = -1;		//棋子状态 1为白棋，-1为黑棋，五子棋为黑棋先手
	bool isPopChess = false;			//是否可以悔棋
	if(cb.GetChessNum()!=0)			//假如是回档进来的游戏 可以悔棋
		isPopChess = true;
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
		if(cb.GetChessNum()!=0)				//还没落子前，不输出这句话
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
			int isAnswerTrue = 0;		//判断输入是否规范
			do{
				char answer[20];
				cout<<"是否存档该游戏？Y/N"<<endl;
				cin>>answer;
				if( (answer[0]!='Y' && answer[0]!='N') || answer[1]!='\0' )		//输入不规范的情况
				{
					isAnswerTrue = 0;
					cout<<"您的输入有误！请重新输入！"<<endl<<endl;
				}else		//输入规范的情况
				{
					if( answer[0] == 'Y') isAnswerTrue = 1;
					else if(answer[0] == 'N') isAnswerTrue = 2;
				}
			}while( ! isAnswerTrue);
			if(isAnswerTrue == 1)		//如果输入的是yes 则返回-1进行存档
				return -1;
			else			//输入的是no
			{
				cout<<endl<<"游戏结束！正在返回主菜单..."<<endl;
				return -9;
			}
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

/*排行榜操作*/
int GamesRanking()						//排行榜内的操作
{
	system("cls");
	ShowRankTitle();					//显示排行榜头部
	rankBoard.ShowRank();		//打印排行榜内容
	char numCharIn[20];			//创建字符数组接收输入 
	cout<<"输入排名编号可显示该编号棋盘的最后战况（输入0返回主界面）：";
	cin>>numCharIn;				
	for(unsigned int i=0;i<strlen(numCharIn);i++)			//如果输入包含除数字的其他字符，则提示错误并返回
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

/*加载游戏*/
int GamesLoad()
{
	system("cls");
	LoadGameTitle();
	int vecLen = loadGameVec.size();
	if(vecLen == 0 )		//没有任何记录
	{
		cout<<"\t\t    无"<<endl<<endl;
		return 1;
	}else
	{
		cout<<setw(5)<<"序号"<<setw(10)<<"黑方"<<setw(8)<<"对战"<<setw(10)<<"白方"<<setw(18)<<"存档时间"<<endl;
		cout<<"---------------------------------------------------"<<endl;
		for(unsigned int i=0;i<vecLen;i++)
		{
			HistoryRec theRec = loadGameVec[i];
			cout<<setw(5)<<i+1<<setw(10)<<theRec.p1.GetName()<<setw(8)<<" VS "<<setw(10)<<
				theRec.p2.GetName()<<setw(18)<<theRec.saveTime<<endl;
		}
		cout<<endl;
		char choice_char[20];
		cout<<"请输入对应序号，继续游戏（输入0返回）：";
		cin>>choice_char;

		int choice_int = atoi(choice_char);
		if(choice_int == 0) return 1;
		if(choice_int <1 || choice_int >loadGameVec.size() )
		{
			cout<<"您的输入有误！请检查输入！"<<endl;
			return 1;
		}
		cout<<endl;
		
		HistoryRec newRec = loadGameVec[choice_int-1];		//必须要新创建一个记录，因为下一句语句为引用
		StartGame(newRec);			//继续游戏
		return 1;
	}
}

/*读取游戏存档*/
void LoadGameRec()
{
	ifstream ifs("HistoryRec.data");
	int recNum =0;		//加载游戏的项目数
	ifs>>recNum;			//流入数据

	for(int i=0;i<recNum;i++)			//循环插入新纪录到 loadGameVec中
	{
		HistoryRec newRec;					//创建一条历史记录
		string p1Name,p2Name;			//每条记录的两个玩家名
		int p1ChessNum=0 , p2ChessNum = 0;			//棋子数
		
		ifs>>p1Name>>p1ChessNum;		//流入玩家1名字和其所下的棋子数
		ifs>>p2Name>>p2ChessNum;		//流入玩家2名字和其所下的棋子数
		newRec.p1.SetName(p1Name);		//设置好玩家的姓名
		newRec.p2.SetName(p2Name);		
		for(int j=0;j<p1ChessNum+p2ChessNum;j++)		//循环插入棋子
		{
			int chessX,chessY,chessColor;		
			ifs>>chessX>>chessY>>chessColor;
			Chess newChess(chessX,chessY,chessColor);		//根据坐标和颜色构建一个棋子
			if(j%2==0)			//偶数轮则p1插入棋子
				newRec.p1.PushChess(newChess,newRec.cb);
			else						//奇数轮则p2插入棋子
				newRec.p2.PushChess(newChess,newRec.cb);
		}
		ifs.get();		//舍弃一个换行符
		getline(ifs,newRec.saveTime);		//读入时间
		loadGameVec.push_back(newRec);			//将新纪录压入vector中
	}
	ifs.close();
}

/*上传游戏存档*/
void UploadGameRec()			//写入文件中
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
			Chess c = loadGameVec[i].cb.GetTheChess(j);		//获取棋盘中的第j个棋子
			ofs<<c.GetX()<<" "<<c.GetY()<<" "<<c.GetColor()<<endl;
		}
		ofs<<loadGameVec[i].saveTime<<endl;
	}
	ofs.close();
}