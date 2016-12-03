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
	//cout<<"删除玩家"<<this->name<<endl;
	//system("pause");
	delete(this->chessArr);
	//cout<<"删除成功！"<<endl;
	//system("pause");
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
int Player:: PopChess()				//悔棋
{
	this->chessNum--;		//退棋一格
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

/*其他成员函数*/
void Player:: Copy(Player &copy)					//拷贝函数
{
	copy.name = this->name;						//拷贝姓名
	copy.win = this->win;								//拷贝胜负情况
	copy.chessNum = this->chessNum;		//拷贝棋路棋子数
	for(int i=0;i<this->chessNum;i++)			//拷贝棋路中的棋子
		copy.chessArr[i] = this->chessArr[i];
}