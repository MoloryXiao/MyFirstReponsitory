#pragma once
#include <iostream>
#include <fstream>
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
	void ShowRank();								//��ӡ���а�
	void ShowTheBoard(int count);		//��ӡ���а��count������
	int ReadFromFile();							//���ļ��ж������а���Ϣ �ɹ�����1 ���򷵻�0
	int WriteToFile();								//�����а���Ϣд���ļ��� �ɹ�����1 ���򷵻�0
};
