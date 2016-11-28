#pragma once
#include "Ranking.h"
#define MAXSIZE 200		//���а���󳤶�

Ranking:: Ranking()
{
	this->rankLen = 0;
	InitLinkList(this->list);
}
Ranking:: ~Ranking()
{
	//cout<<"ɾ�����а�"<<endl;
	//system("pause");
	deleList(this->list);
	//cout<<"ɾ���ɹ���"<<endl;
	//system("pause");
}
/*��ȡ������Ϣ*/
int Ranking::GetRankLen()				//rankLen����
{
	return this->rankLen;
}

/*һ���Ա����*/
int Ranking::InsertRec(ChessBoard &cb , string winName)		//����һ����¼
{
	Record newRec;				//����һ���¼�¼
	newRec.winName = winName;		//��ֵ��¼��ʤ���������
	cb.Copy(newRec.chessBoard);			//�����̽��п���
	InsertLinkList(this->list , newRec);	//���뵽������
	this->rankLen++;				//���а񳤶ȼ�һ
	return 1;
}

void Ranking::ShowRank()				//��ӡ���а�
{
	ShowList(this->list);
}

void Ranking::ShowTheBoard(int count)			//��ӡ���а��count������
{
	cout<<endl;
	LinkList sTemp = this->list;
	int loc=0;
	while(sTemp->next != NULL)
	{
		loc++;
		if(count == loc)
		{
			sTemp->next->data.chessBoard.ShowBoard(true);
			cout<<"��ң�"<<sTemp->next->data.winName<<" ��ñ�����Ϸ��ʤ����   "
				<<"λ�а񵥵ڡ�"<<count<<"������"<<endl<<endl;
			break;
		}
		else 
			sTemp = sTemp->next;
	}
}