#include <iostream>
#include "ChessBoard.h"
using namespace std;

class Ranking{
private:
	int rankLen;					//排行榜长度
	ChessBoard *list;			//排行榜内容
public:
	/*构造函数*/
	Ranking(int rankLen=0);
	/*
	int PushBoard(ChessBoard cb);			//正常压入返回1，否则返回0
	int PopBoard();									//不带回的弹出，正常弹出返回1，否则返回0
	int PopBoard(ChessBoard *cb);			//带回的弹出，正常弹出返回1，否则返回0
	*/
};
