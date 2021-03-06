#pragma once
#include <iostream>
#include <fstream>
#include "ChessBoard.h"
#include "LinkList.h"
using namespace std;

class Ranking{
private:
	int rankLen;					//排行榜长度
	LinkList list;					//排行榜内容
public:
	/*构造函数*/
	Ranking();
	~Ranking();

	/*获取属性信息*/
	int GetRankLen();				//rankLen属性

	/*一般成员函数*/
	int InsertRec(ChessBoard &cb , string winName);	//插入一条记录
	void ShowRank();								//打印排行榜
	void ShowTheBoard(int count);		//打印排行榜第count个棋盘
	int ReadFromFile();							//从文件中读入排行榜信息 成功返回1 否则返回0
	int WriteToFile();								//将排行榜信息写到文件中 成功返回1 否则返回0
};
