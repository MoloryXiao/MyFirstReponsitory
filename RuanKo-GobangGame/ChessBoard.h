#pragma once
#include <iostream>
#include "Chess.h"
using namespace std;
#define WIDTH 15		//棋盘宽默认值
#define HEIGHT 15		//棋盘高默认值

//定义棋盘类
class ChessBoard{
private :
	int width;							//棋盘宽
	int height;							//棋盘高
	Chess *chessAll;				//棋盘上的棋子
	int chessNum;					//棋盘上的棋子数
public :
	/*构造函数 析构函数*/
	ChessBoard(int width=WIDTH,int height=HEIGHT);	
	~ChessBoard();						

	/*基本成员函数*/
	void ShowBoard(bool win);			//显示棋盘（win表示胜负情况）
	void Init2DArray(int **board);		//初始化虚拟棋盘，即二维数组形式的棋盘
	bool IsBoardFull();						//判断棋盘是否为满
	void Copy(ChessBoard &copy);	//复制棋盘 将this拷贝到copy中

	/*添加棋子函数*/
	int AddChess(Chess c);					//添加棋子	棋盘已满返回0 添加成功返回1
	bool CheckChessXY(Chess c);		//检查棋子XY坐标是否合理	合理返回true 越界返回false

	/*获取属性信息函数*/
	int GetWidth();				//获取棋盘宽度
	int GetHeight();			//获取棋盘高度
	int GetChessNum();		//获取棋盘棋子数

	/*胜负判断函数*/
	bool IsHorizonWin(Chess c , int **board);						//判断是否水平方向获胜
	bool IsVerticalWin(Chess c , int **board);						//判断是否垂直方向获胜
	bool IsLeftDiagonalWin(Chess c , int **board);				//判断是否左对角线获胜
	bool IsRightDiagonalWin(Chess c , int **board);				//判断是否右对角线获胜
	bool IsBoardWin(Chess c);												//判断棋盘上是否已经有胜负
};