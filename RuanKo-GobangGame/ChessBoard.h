#pragma once
#include <iostream>
#include "Chess.h"
using namespace std;
#define WIDTH 15		//���̿�Ĭ��ֵ
#define HEIGHT 15		//���̸�Ĭ��ֵ

//����������
class ChessBoard{
private :
	int width;							//���̿�
	int height;							//���̸�
	Chess *chessAll;				//�����ϵ�����
	int chessNum;					//�����ϵ�������
public :
	/*���캯�� ��������*/
	ChessBoard(int width=WIDTH,int height=HEIGHT);	
	~ChessBoard();						

	/*������Ա����*/
	void ShowBoard(bool win);			//��ʾ���̣�win��ʾʤ�������
	void Init2DArray(int **board);		//��ʼ���������̣�����ά������ʽ������
	bool IsBoardFull();						//�ж������Ƿ�Ϊ��
	void Copy(ChessBoard &copy);	//�������� ��this������copy��

	/*������Ӻ���*/
	int AddChess(Chess c);					//�������	������������0 ��ӳɹ�����1
	bool CheckChessXY(Chess c);		//�������XY�����Ƿ����	������true Խ�緵��false

	/*��ȡ������Ϣ����*/
	int GetWidth();				//��ȡ���̿��
	int GetHeight();			//��ȡ���̸߶�
	int GetChessNum();		//��ȡ����������

	/*ʤ���жϺ���*/
	bool IsHorizonWin(Chess c , int **board);						//�ж��Ƿ�ˮƽ�����ʤ
	bool IsVerticalWin(Chess c , int **board);						//�ж��Ƿ�ֱ�����ʤ
	bool IsLeftDiagonalWin(Chess c , int **board);				//�ж��Ƿ���Խ��߻�ʤ
	bool IsRightDiagonalWin(Chess c , int **board);				//�ж��Ƿ��ҶԽ��߻�ʤ
	bool IsBoardWin(Chess c);												//�ж��������Ƿ��Ѿ���ʤ��
};