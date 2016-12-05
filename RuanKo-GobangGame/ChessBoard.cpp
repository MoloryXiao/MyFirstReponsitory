#pragma once
#include "ChessBoard.h"
#include "Chess.h"
#include <iomanip>
#include <string>
#define MAXBOARD 250			//棋盘结点数组长度

/*构造函数 析构函数*/
ChessBoard:: ChessBoard(int width,int height)					//构造函数
{
	this->width = width;
	this->height = height;
	this->chessAll = new Chess[width*height];
	this->chessNum = 0;
}
ChessBoard:: ~ChessBoard()				//析构函数
{
	//cout<<"删除棋盘"<<endl;
	//system("pause");
	delete(this->chessAll);
	//cout<<"删除成功！"<<endl;
	//system("pause");
}
ChessBoard:: ChessBoard(const ChessBoard &c)
{
	this->width = c.width;
	this->height = c.height;
	this->chessNum = c.chessNum;
	this->chessAll = new Chess[width*height];
	for(int i=0;i<c.chessNum;i++)
		this->chessAll[i] = c.chessAll[i];
}

/*基本成员函数*/
void ChessBoard:: ShowBoard(bool gameWin)			//显示棋盘 gameWin表示棋盘胜负情况
{
	/*创建一个用于显示棋面的二维数组*/
	int **board;
	board = new int*[this->height];		//根据棋盘高度设定行数
	for(int i=0;i<this->width;i++)
		board[i] = new int[this->width];		//根据棋盘宽度设置列数
	Init2DArray(board);
	
	/*根据二维数组情况画出棋盘*/
	string str[20]={"０","１","２","３","４","５","６","７","８","９","10","11","12","13","14","15"};
	//列标识打印
	for(int i=0;i<=this->width;i++)
	{
		if(i==0) cout<<"  ";
		else cout<<setw(2)<<str[i-1];
	}
	cout<<endl;
	char c='A';
	for(int i=0 ; i<this->height ; i++)
	{
		cout<<char(c+i)<<" ";		//行标识打印
		for(int j=0 ; j<this->width ; j++)
		{
			if(board[i][j] == 0)		//无棋
			{
				//边界点判断┻ ┫ ┣  ┏ ┗ ┛ ┳
				if(i==0 && j==0) cout<<"┏";
				else if(i==0 && j==this->width-1) cout<<"┓";
				else if(i==this->height-1 && j==0) cout<<"┗";
				else if(i==this->height-1 && j==this->width-1) cout<<"┛";
				else if(i==0) cout<<"┳";
				else if(i==this->height-1) cout<<"┻";
				else if(j==0) cout<<"┣";
				else if(j==this->width-1) cout<<"┫";
				else cout<<"╋";		
			}		
			else if(board[i][j]== -1) cout<<"○";			//黑棋
			else if(board[i][j] == 1) cout<<"●";			//白棋
		}
		if(i == 3) cout<<"    棋盘规格："<<this->width<<"×"<<this->height;
		if(i == 5) 
		{
			if(gameWin == false)
				cout<<"    当前全盘棋子数："<<this->chessNum;
			else
				cout<<"    游戏全盘棋子数："<<this->chessNum;
		}
		if(i == 4) 
		{
			if(gameWin == false)
				cout<<"    前一子落点处：";
			else 
				cout<<"    最终落子处：";
			if( this->chessNum == 0) cout<<"无";
			else
				cout<<char(this->chessAll[this->chessNum-1].GetX()+'A')
				<<this->chessAll[this->chessNum-1].GetY();
		} 
		if(i == 12)
		{
			if(gameWin == false)		//游戏未分胜负
			{
				if(this->chessNum == 0)				//开局为黑方先手
					cout<<"    当前为黑方执子：○";
				else if(this->chessAll[this->chessNum-1].GetColor() == -1)//若棋子数组中顶部为黑棋，则下手为白棋
					cout<<"    当前为白方执子：●";
				else
					cout<<"    当前为黑方执子：○";
			}else			//游戏已分胜负
			{
				if(this->chessAll[this->chessNum-1].GetColor() == -1)		//若棋子数组中顶部为黑棋，则赢家为黑棋
					cout<<"    游戏赢家：黑方 ○";
				else
					cout<<"    游戏赢家：白方 ●";
			}
		}
		cout<<endl;
	}
	cout<<endl;
	//手动删除指针，未写
}
void ChessBoard::Init2DArray(int **board)		//初始化虚拟棋盘，即二维数组形式的棋盘
{
	/*初始化棋盘*/
	for(int i=0;i<this->height;i++)
		for(int j=0;j<this->width;j++)
			board[i][j] = 0;
	/*根据棋盘上的棋子对该二维数组进行赋值*/
	for(int i=0;i<this->chessNum;i++)
	{
		Chess chess=this->chessAll[i];
		int x = chess.GetX();
		int y = chess.GetY();
		int color = chess.GetColor();
		board[x][y]=color;
	}
}
bool ChessBoard::IsBoardFull()			//判断棋盘是否为满
{
	if( this->chessNum >= (this->width * this->height) )			//棋盘上的棋子数大于等于棋盘结点数
		return true;
	else 
		return false;
}
void ChessBoard::Copy(ChessBoard &copy)	//复制棋盘 将this拷贝到copy中
{
	copy.width = this->width;						//复制棋盘宽度
	copy.height = this->height;						//复制棋盘高度
	copy.chessNum = this->chessNum;		//复制棋盘棋子数
	for(int i=0;i<chessNum ; i++)					//复制棋盘上的棋子
		copy.chessAll[i] = this->chessAll[i];
}

/*添加棋子函数*/
int ChessBoard:: AddChess(Chess c)				//添加棋子	棋盘已满返回0 添加成功返回1
{
	if( IsBoardFull() ) return 0;			//如果棋盘已满则返回0

	this->chessAll[this->chessNum] = c;		//把棋子加进棋盘中,（下标从0开始）
	this->chessNum++;									//棋子数+1
	return 1;
}
int ChessBoard:: PopChess()
{
	this->chessNum -- ;
	return 1;
}
bool ChessBoard::CheckChessXY( Chess c )					//检查棋子XY坐标是否合理	合理返回true 否则返回false
{
	//越界判断
	if( c.GetX() > this->width-1 || c.GetY() > this->height-1 || c.GetX()<0 || c.GetY()<0 ) 
		return false;	
	//原位置查空
	for(int i=0;i<this->chessNum;i++)		//遍历棋盘上的每一个棋子
	{
		Chess cs = this->chessAll[i];			//取出
		if( cs.GetX()==c.GetX() && cs.GetY()==c.GetY() )		//比较，若存在位置相同的棋子
			return false;			//则说明该子位置上已经存在棋子，也不合理
	}

	return true;
}

/*获取属性信息函数*/
int ChessBoard::GetWidth()				//获取棋盘宽度
{
	return this->width;
}
int ChessBoard::GetHeight()				//获取棋盘高度
{
	return this->height;
}
int ChessBoard::GetChessNum()		//获取棋盘棋子数
{
	return this->chessNum;
}
Chess ChessBoard::GetTheChess(int count)		//获取棋盘中第count个棋子存于c中
{
	return this->chessAll[count];
}
int ChessBoard::GetTheChessX(int count)		//获取棋盘中第count个棋子的X坐标
{
	return this->chessAll[count].GetX();
}
int ChessBoard::GetTheChessY(int count)			//获取棋盘中第count个棋子的Y坐标
{
	return this->chessAll[count].GetY();
}
int ChessBoard::GetTheChessColor(int count)		//获取棋盘中第count个棋子的color颜色
{
	return this->chessAll[count].GetColor();
}

/*胜负判断函数*/
bool ChessBoard:: IsHorizonWin(Chess c , int **board)						//判断是否水平方向获胜
{
	int num=1;				//初始化计数器
	int x = c.GetX();
	int y = c.GetY();
	int color = c.GetColor();
	for(int i=y-1;i>=0;i--)			//向左遍历
	{
		if( board[x][i] == color ) num++;		//颜色一致，加1
		else break;
	}
	for(int i=y+1;i<this->width;i++)			//向右遍历
	{
		if(board[x][i] == color) num++;			//颜色一致，加1
		else break;
	}
	if(num>=5) return true;			//满五个以上的，返回true
	else return false;
}
bool ChessBoard:: IsVerticalWin(Chess c , int **board)						//判断是否垂直方向获胜
{
	int num=1;				//初始化计数器
	int x = c.GetX();
	int y = c.GetY();
	int color = c.GetColor();
	for(int i=x-1 ; i>=0;i--)			//向上遍历
	{
		if( board[i][y] == color ) num++;		//颜色一致，加1
		else break;
	}
	for(int i=x+1 ; i<this->height;i++)			//向下遍历
	{
		if(board[i][y] == color) num++;			//颜色一致，加1
		else break;
	}
	if(num>=5) return true;			//满五个以上的，返回true
	else return false;
}
bool ChessBoard:: IsLeftDiagonalWin(Chess c , int **board)				//判断是否左对角线获胜
{
	int num=1;				//初始化计数器
	int x = c.GetX();
	int y = c.GetY();
	int color = c.GetColor();
	for(int i=x-1, j=y-1 ; i>=0 && y>=0 ; i--,j--)			//向左上遍历
	{
		if( board[i][j] == color ) num++;		//颜色一致，加1
		else break;
	}
	for(int i=x+1 , j=y+1 ; i<this->height && y<this->width ; i++,j++)			//向右下遍历
	{
		if(board[i][j] == color) num++;			//颜色一致，加1
		else break;
	}
	if(num>=5) return true;			//满五个以上的，返回true
	else return false;
}
bool ChessBoard:: IsRightDiagonalWin(Chess c , int **board)				//判断是否右对角线获胜
{
	int num=1;				//初始化计数器
	int x = c.GetX();
	int y = c.GetY();
	int color = c.GetColor();
	for(int i=x-1, j=y+1 ; i>=0 && y<this->width ; i--,j++)			//向右上遍历
	{
		if( board[i][j] == color ) num++;		//颜色一致，加1
		else break;
	}
	for(int i=x+1 , j=y-1 ; i<this->height && y>=0 ; i++,j--)			//向左下遍历
	{
		if(board[i][j] == color) num++;			//颜色一致，加1
		else break;
	}
	if(num>=5) return true;			//满五个以上的，返回true
	else return false;
}
bool ChessBoard:: IsBoardWin(Chess c)									//判断棋盘上是否已经有胜负
{
	int **board;
	board = new int*[this->height];		//根据棋盘高度设定行数
	for(int i=0;i<this->width;i++)
		board[i] = new int[this->width];		//根据棋盘宽度设置列数
	Init2DArray(board);
	if(this->IsHorizonWin(c,board) || this->IsVerticalWin(c,board) 
		|| this->IsLeftDiagonalWin(c,board) || this->IsRightDiagonalWin(c,board) )
	{
		return true;
	}else
	{
		return false;
	}
}