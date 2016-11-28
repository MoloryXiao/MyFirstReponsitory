#pragma once
#include "ChessBoard.h"
#include <iostream>
#include <string>
using namespace std;
#define DATATYPE Record

//定义排行榜的一个项目条
typedef struct {
	ChessBoard chessBoard;			//保存一个棋盘
	string winName;			//保存一个赢家姓名
}Record;

//定义排行榜链表结点Node和头结点指针LinkList
typedef struct Node{
	DATATYPE data;			//数据域
	Node *next;					//指针域
}Node,*LinkList;

int InitLinkList(LinkList &L);							//初始化单链表
int InsertLinkList(LinkList &L,Record &r);		//将r插入单链表中

bool IsListEmpty(LinkList &L);						//判断单链表是否为空

void ShowList(LinkList &L);							//打印单链表
void CopyRec(Record &rec , Record &copy);		//拷贝排行榜项目条函数
void deleList(LinkList &L);						//释放指针