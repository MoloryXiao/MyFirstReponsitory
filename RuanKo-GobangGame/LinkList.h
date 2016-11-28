#pragma once
#include "ChessBoard.h"
#include <iostream>
#include <string>
using namespace std;
#define DATATYPE Record

//�������а��һ����Ŀ��
typedef struct {
	ChessBoard chessBoard;			//����һ������
	string winName;			//����һ��Ӯ������
}Record;

//�������а�������Node��ͷ���ָ��LinkList
typedef struct Node{
	DATATYPE data;			//������
	Node *next;					//ָ����
}Node,*LinkList;

int InitLinkList(LinkList &L);							//��ʼ��������
int InsertLinkList(LinkList &L,Record &r);		//��r���뵥������

bool IsListEmpty(LinkList &L);						//�жϵ������Ƿ�Ϊ��

void ShowList(LinkList &L);							//��ӡ������
void CopyRec(Record &rec , Record &copy);		//�������а���Ŀ������
void deleList(LinkList &L);						//�ͷ�ָ��