#pragma once
#include <iostream>
#include "ChessBoard.h"
#include "LinkList.h"
using namespace std;

class Ranking{
private:
	int rankLen;					//���а񳤶�
	LinkList list;					//���а�����
public:
	/*���캯��*/
	Ranking();
	~Ranking();

	/*��ȡ������Ϣ*/
	int GetRankLen();				//rankLen����

	/*һ���Ա����*/
	int InsertRec(ChessBoard &cb , string winName);	//����һ����¼
	void ShowRank();														//��ӡ���а�
	void ShowTheBoard(int count);								//��ӡ���а��count������
};
