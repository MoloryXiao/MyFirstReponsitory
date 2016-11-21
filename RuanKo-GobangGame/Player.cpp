#include "Player.h"
#include "Chess.h"
#define MAXSIZE 250			//��·���鳤��

Player::Player(string name)						//���캯��
{
	this->name = name ;
	this->win = false;
	this->chessArr = new Chess[MAXSIZE];
	this->chessNum = 0;
}
Player::~Player()										//��������
{
	delete(this->chessArr);
}

int Player:: PushChess(Chess c , ChessBoard &cb)					//���ӣ��ɹ�����1 ʧ�ܷ���0
{
	// ����λ�ò�����
	if( ! cb.CheckChessXY(c) ) return 0;
	
	//λ�ú��������
	cb.AddChess(c);				//�洢������
	this->chessArr[this->chessNum] = c;			//�洢����·
	this->chessNum++;
	return 1;
}
int Player:: PopChess(Chess *c , ChessBoard &cb)				//����
{
	return 1;
}

/*��ȡ������Ϣ*/
bool Player:: GetWin()					//����win
{
	return this->win;
}
string Player:: GetName()				//����name
{
	return this->name;
}
int Player:: GetChessNum()			//����chessNum
{
	return this->chessNum;
}

/*����������Ϣ*/
void Player:: SetName(string newName)		//����name
{
	this->name = newName;
}
void Player:: SetWin(bool pd)									//����win
{
	this->win = pd;
}