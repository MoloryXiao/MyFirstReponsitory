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
	cout<<endl;		//����
	LinkList sTemp = this->list;			//��������ָ��
	int loc=0;			//����������
	while(sTemp->next != NULL)
	{
		loc++;			//���¼�����
		if(count == loc)		//����ָ��λ��(�ں�����Բ��淶������Ҫ���д���)
		{
			//��ӡ�����Ϣ
			sTemp->next->data.chessBoard.ShowBoard(true);
			cout<<"��ң�"<<sTemp->next->data.winName<<" ��ñ�����Ϸ��ʤ����   "
				<<"λ�а񵥵ڡ�"<<count<<"������"<<endl<<endl;
			break;
		}
		else 
			sTemp = sTemp->next;		//����
	}
}
int Ranking::ReadFromFile()							//���ļ��ж������а���Ϣ �ɹ�����1 ���򷵻�0
{
	ifstream ifs("RankingData.dat");			//���ļ�
	if(ifs == NULL) return 0;						//��ʧ���򷵻�0
	
	int fileRankLen=0;								//�������а񳤶�
	ifs>>fileRankLen;									//���ļ�����ñ���
	this->rankLen = fileRankLen;				//���嵱ǰ���а�ĳ���
	
	InitLinkList(this->list);							//��ʼ�����а����������ߵ��������ݣ�
	for(int i=0;i<this->rankLen;i++)			//ѭ������rankLen��
	{
		Record newRec;								//�½�һ�����ڷ���������¼�¼
		int fileChessNum;								//���ļ�����ü�¼��������
		int fileX,fileY,fileColor;						//���ļ�����ü�¼�����ӵ����꼰��ɫ
		Chess newChess;								//����һ�����ڷ������������
		ifs>>newRec.winName>>fileChessNum;			//���ļ�����ü�¼�Ļ�ʤ��Һ͸ü�¼��������
		for(int i=0;i<fileChessNum;i++)						//ѭ���������ӵ��ü�¼��������
		{
			ifs>>fileX>>fileY>>fileColor;
			newChess.SetAll(fileX,fileY,fileColor);				//�����������꼰��ɫ
			newRec.chessBoard.AddChess(newChess);		//��������ӵ�������
		}
		InsertLinkList(this->list , newRec);	//����¼���뵽���а���
	}
	return 1;
}
int Ranking::WriteToFile()							//�����а���Ϣд���ļ��� �ɹ�����1 ���򷵻�0
{
	ofstream ofs("RankingData.dat");	//���ļ�
	if(ofs == NULL) return 0;					//��ʧ���򷵻�0

	LinkList sTemp= this->list;				//����������ָ�롱
	LinkList nowNode = NULL;				//��������ӡָ�롱
	ofs<<this->rankLen<<endl;			//�����а񳤶��������ļ���һ��
	while(sTemp->next != NULL)			//��ʼ�����а��ϵ�һ�����̽��б���
	{
		nowNode = sTemp->next;			//�ԡ���ӡָ�롱���и�ֵ
		int chessNum = nowNode->data.chessBoard.GetChessNum();		//ÿ�������ϵ���������
		ofs<<nowNode->data.winName<<" "<<chessNum<<endl;			//�������̻�ʤ������ƺ����̵���������
		for(int j=0;j<chessNum;j++)		//���������ϵ�����
		{
			//��ÿ�����ӵ����궼��������
			ofs<<nowNode->data.chessBoard.GetTheChessX(j)<<" "
				<<nowNode->data.chessBoard.GetTheChessY(j)<<" "
				<<nowNode->data.chessBoard.GetTheChessColor(j)<<endl;
		}
		sTemp = sTemp->next;			//����
	}
	ofs.close();			//�ر�
	return 1;
}