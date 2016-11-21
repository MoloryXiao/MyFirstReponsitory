#pragma once
#include <iostream>
#include "Chess.h"
using namespace std;

//����������
class ChessBoard{
private :
	int width;							//���̿�
	int height;							//���̸�
	Chess *chessAll;				//�����ϵ�����
	int chessNum;					//�����ϵ�������
public :
	/*���캯�� ��������*/
	ChessBoard(int width=15,int height=15);			
	~ChessBoard();						

	/*������Ա����*/
	void ShowBoard();						//��ʾ����
	void Init2DArray(int **board);		//��ʼ���������̣�����ά������ʽ������
	bool IsBoardFull();						//�ж������Ƿ�Ϊ��

	/*������Ӻ���*/
	int AddChess(Chess c);					//�������	������������0 ��ӳɹ�����1
	bool CheckChessXY(Chess c);		//�������XY�����Ƿ����	������true Խ�緵��false

	/*��ȡ������Ϣ����*/
	int GetWidth();				//��ȡ���̿��
	int GetHeight();			//��ȡ���̸߶�

	/*ʤ���жϺ���*/
	bool IsHorizonWin(Chess c , int **board);						//�ж��Ƿ�ˮƽ�����ʤ
	bool IsVerticalWin(Chess c , int **board);						//�ж��Ƿ�ֱ�����ʤ
	bool IsLeftDiagonalWin(Chess c , int **board);				//�ж��Ƿ���Խ��߻�ʤ
	bool IsRightDiagonalWin(Chess c , int **board);				//�ж��Ƿ��ҶԽ��߻�ʤ
	bool IsBoardWin(Chess c);												//�ж��������Ƿ��Ѿ���ʤ��
};