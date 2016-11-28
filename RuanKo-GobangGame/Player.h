#pragma once
#include <iostream>
#include <string>
#include "ChessBoard.h"
#include "Chess.h"
using namespace std;

//玩家类
class Player{
private : 
	string name;				//玩家姓名
	bool win;					//胜负情况
	Chess *chessArr;		//棋路记录
	int chessNum;			//下棋步数
public :
	/*构造函数 析构函数*/
	Player(string name="Unknown");					//构造函数
	~Player();															//析构函数

	int PushChess(Chess c , ChessBoard &cb);			//落子
	int PopChess(Chess *c , ChessBoard &cb);			//悔棋

	/*获取属性信息*/
	bool GetWin();						//属性win
	string GetName();				//属性name
	int GetChessNum();				//属性chessNum

	/*设置属性信息*/
	void SetName(string newName);			//属性name
	void SetWin(bool pd);							//属性win

	/*其他成员函数*/
	void Copy(Player &copy);					//拷贝函数
};