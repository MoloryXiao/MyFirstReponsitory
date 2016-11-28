#pragma once
#include <iostream>
#include <string>
#include "ChessBoard.h"
#include "Chess.h"
using namespace std;

//�����
class Player{
private : 
	string name;				//�������
	bool win;					//ʤ�����
	Chess *chessArr;		//��·��¼
	int chessNum;			//���岽��
public :
	/*���캯�� ��������*/
	Player(string name="Unknown");					//���캯��
	~Player();															//��������

	int PushChess(Chess c , ChessBoard &cb);			//����
	int PopChess(Chess *c , ChessBoard &cb);			//����

	/*��ȡ������Ϣ*/
	bool GetWin();						//����win
	string GetName();				//����name
	int GetChessNum();				//����chessNum

	/*����������Ϣ*/
	void SetName(string newName);			//����name
	void SetWin(bool pd);							//����win

	/*������Ա����*/
	void Copy(Player &copy);					//��������
};