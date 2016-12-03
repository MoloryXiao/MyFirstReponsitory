#pragma once
#include "Ranking.h"
#define MAXSIZE 200		//排行榜最大长度

Ranking:: Ranking()
{
	this->rankLen = 0;
	InitLinkList(this->list);
}
Ranking:: ~Ranking()
{
	//cout<<"删除排行榜"<<endl;
	//system("pause");
	deleList(this->list);
	//cout<<"删除成功！"<<endl;
	//system("pause");
}
/*获取属性信息*/
int Ranking::GetRankLen()				//rankLen属性
{
	return this->rankLen;
}

/*一般成员函数*/
int Ranking::InsertRec(ChessBoard &cb , string winName)		//插入一条记录
{
	Record newRec;				//创建一个新纪录
	newRec.winName = winName;		//赋值记录的胜利玩家姓名
	cb.Copy(newRec.chessBoard);			//对棋盘进行拷贝
	InsertLinkList(this->list , newRec);	//插入到链表中
	this->rankLen++;				//排行榜长度加一
	return 1;
}

void Ranking::ShowRank()				//打印排行榜
{
	ShowList(this->list);
}

void Ranking::ShowTheBoard(int count)			//打印排行榜第count个棋盘
{
	cout<<endl;		//美观
	LinkList sTemp = this->list;			//声明遍历指针
	int loc=0;			//声明计数器
	while(sTemp->next != NULL)
	{
		loc++;			//更新计数器
		if(count == loc)		//到达指定位置(在函数外对不规范的输入要进行处理)
		{
			//打印相关信息
			sTemp->next->data.chessBoard.ShowBoard(true);
			cout<<"玩家："<<sTemp->next->data.winName<<" 获得本场游戏的胜利！   "
				<<"位列榜单第【"<<count<<"】名！"<<endl<<endl;
			break;
		}
		else 
			sTemp = sTemp->next;		//递增
	}
}
int Ranking::ReadFromFile()							//从文件中读入排行榜信息 成功返回1 否则返回0
{
	ifstream ifs("RankingData.dat");			//打开文件
	if(ifs == NULL) return 0;						//打开失败则返回0
	
	int fileRankLen=0;								//定义排行榜长度
	ifs>>fileRankLen;									//从文件流入该变量
	this->rankLen = fileRankLen;				//定义当前排行榜的长度
	
	InitLinkList(this->list);							//初始化排行榜链表（清空里边的所有数据）
	for(int i=0;i<this->rankLen;i++)			//循环插入rankLen次
	{
		Record newRec;								//新建一个用于反复插入的新纪录
		int fileChessNum;								//从文件读入该记录的棋子数
		int fileX,fileY,fileColor;						//从文件读入该记录的棋子的坐标及颜色
		Chess newChess;								//创建一个用于反复插入的棋子
		ifs>>newRec.winName>>fileChessNum;			//从文件流入该记录的获胜玩家和该记录的棋子数
		for(int i=0;i<fileChessNum;i++)						//循环插入棋子到该记录的棋盘中
		{
			ifs>>fileX>>fileY>>fileColor;
			newChess.SetAll(fileX,fileY,fileColor);				//更新棋子坐标及颜色
			newRec.chessBoard.AddChess(newChess);		//插入该棋子到棋盘中
		}
		InsertLinkList(this->list , newRec);	//将记录插入到排行榜中
	}
	return 1;
}
int Ranking::WriteToFile()							//将排行榜信息写到文件中 成功返回1 否则返回0
{
	ofstream ofs("RankingData.dat");	//打开文件
	if(ofs == NULL) return 0;					//打开失败则返回0

	LinkList sTemp= this->list;				//声明“遍历指针”
	LinkList nowNode = NULL;				//声明“打印指针”
	ofs<<this->rankLen<<endl;			//将排行榜长度流出到文件第一行
	while(sTemp->next != NULL)			//开始从排行榜上第一个棋盘进行遍历
	{
		nowNode = sTemp->next;			//对“打印指针”进行赋值
		int chessNum = nowNode->data.chessBoard.GetChessNum();		//每个棋盘上的棋子总数
		ofs<<nowNode->data.winName<<" "<<chessNum<<endl;			//流出棋盘获胜玩家名称和棋盘的棋子总数
		for(int j=0;j<chessNum;j++)		//遍历棋盘上的棋子
		{
			//对每个棋子的坐标都进行流出
			ofs<<nowNode->data.chessBoard.GetTheChessX(j)<<" "
				<<nowNode->data.chessBoard.GetTheChessY(j)<<" "
				<<nowNode->data.chessBoard.GetTheChessColor(j)<<endl;
		}
		sTemp = sTemp->next;			//递增
	}
	ofs.close();			//关闭
	return 1;
}