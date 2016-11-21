#include "Player.h"
#include "Chess.h"
#define MAXSIZE 250			//棋路数组长度

Player::Player(string name)						//构造函数
{
	this->name = name ;
	this->win = false;
	this->chessArr = new Chess[MAXSIZE];
	this->chessNum = 0;
}
Player::~Player()										//析构函数
{
	delete(this->chessArr);
}

int Player:: PushChess(Chess c , ChessBoard &cb)					//落子，成功返回1 失败返回0
{
	// 棋子位置不允许
	if( ! cb.CheckChessXY(c) ) return 0;
	
	//位置合理则继续
	cb.AddChess(c);				//存储至棋盘
	this->chessArr[this->chessNum] = c;			//存储至棋路
	this->chessNum++;
	return 1;
}
int Player:: PopChess(Chess *c , ChessBoard &cb)				//悔棋
{
	return 1;
}

/*获取属性信息*/
bool Player:: GetWin()					//属性win
{
	return this->win;
}
string Player:: GetName()				//属性name
{
	return this->name;
}
int Player:: GetChessNum()			//属性chessNum
{
	return this->chessNum;
}

/*设置属性信息*/
void Player:: SetName(string newName)		//属性name
{
	this->name = newName;
}
void Player:: SetWin(bool pd)									//属性win
{
	this->win = pd;
}