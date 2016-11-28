#pragma once
#include "LinkList.h"
#include "ChessBoard.h"
#include <iomanip>

int InitLinkList(LinkList &L)							//��ʼ��������
{
	if ( (L = (Node*)malloc(sizeof(Node)) )==NULL)
	{
		cout<<"����ͷ�������ռ�ʧ�ܣ������˳���"<<endl;
		exit(0);
	}
	L->next = NULL;
	return 1;
}
int InsertLinkList(LinkList &L,Record &newRec)			//��r���뵥������
{
	LinkList sTemp = L;			//�½�ָ��ָ������ ����������� ����������ָ�롱
	Node* newNode;				//����һ���½ڵ�ָ��

	//Ϊ��ָ������ռ�
	if( ( newNode = new Node() ) == NULL )
	{
		cout<<"�������ռ�ʧ�ܣ�"<<endl;
		return 0;
		exit(0);
	}

	//��ֵ������
	CopyRec(newRec , newNode->data );			//����������newRec�������½ڵ����������
	if( IsListEmpty(L) )			//�������Ϊ�գ���ֱ�����
	{
		L->next = newNode;			//ͷָ��ָ��������
		newNode->next = NULL;		//������ָ���
		return 1;
	}	
	//������Ϊ�գ����ҵ��ʺ�����λ�ò��루�������������������У�
	int chessNum = newNode->data.chessBoard.GetChessNum();		//�����̵�������
	while( sTemp->next !=NULL)
	{
		//����ÿ�����а�ÿ����Ŀ�������̵���������
		int _chessNum = sTemp->next->data.chessBoard.GetChessNum();	
		if( chessNum < _chessNum)		//�ҵ������
		{
			newNode->next = sTemp->next;		//��ֵ�½ڵ���
			sTemp->next = newNode;			//����ָ��
			return 1;		//�������
		}else			//��������
		{
			sTemp = sTemp->next;		//����ָ��
		}
	}
	if(sTemp->next == NULL )	//"����ָ��"����ĩβ��Ȼδ����
	{
		sTemp->next = newNode;		//�½ڵ���뵽���
		newNode->next =NULL;		//����ָ��
	}
	return 1;
}
bool IsListEmpty(LinkList &L)						//�жϵ������Ƿ�Ϊ��
{
	if(L->next == NULL) return true;
	else return false;
}

void ShowList(LinkList &L)							//��ӡ������
{
	if( IsListEmpty(L) )
	{
		cout<<endl<<"              ------��------"<<endl<<endl;
		return;
	}else
	{
		cout<<setw(5)<<"����"<<setw(13)<<"���̹��"<<setw(12)<<"��ʤ���"<<setw(10)<<"����"<<endl;			//ͷ��
		LinkList sTemp = L;						//����������ָ�롱
		ChessBoard cbShow;					//����һ�����ڱ�����ʾ������
		Record recShow;							//����һ�����ڱ�����ʾ�ļ�¼
		int count=1;			//����������
		while(sTemp->next != NULL)
		{
			CopyRec(sTemp->next->data,recShow);			//���¡�������¼��
			recShow.chessBoard.Copy(cbShow);				//���¡��������̡�
			//�������Ϣ���д�ӡ
			cout<<setw(5)<<count<<setw(9)<<cbShow.GetHeight()<<"��"<<cbShow.GetWidth()
				<<setw(12)<<recShow.winName
				<<setw(10)<<cbShow.GetChessNum()<<endl;
			sTemp = sTemp->next;			//����
			count++;				//����������
		}
		cout<<endl;
	}
}
void deleList(LinkList &L)			//�ͷ�ָ��
{
	LinkList sTemp = L->next;		//��ͷ������һ����㿪ʼ�ͷţ���Ϊ������ָ�롱
	LinkList t = sTemp;					//���ڼ�¼������ָ�롱����һ�����λ�ã���Ϊ����¼ָ�롱
	while(sTemp->next !=NULL)
	{
		t = sTemp->next;				//���¡���¼ָ�롱
		delete(sTemp);					//ɾ��������ָ�롱ָ���λ��
		sTemp = t;						//���¡�����ָ��"
	}
	delete(sTemp);			//�ͷ�ĩβ���
	free(L);						//�ͷ�ͷ���
}
void CopyRec(Record &rec , Record &copy)		//�������а���Ŀ������
{
	copy.winName = rec.winName;					//������¼rec�Ļ�ʤ�������
	rec.chessBoard.Copy(copy.chessBoard);		//������¼rec������
}