#pragma once
#include "LinkList.h"
#include "ChessBoard.h"
#include <iomanip>

int InitLinkList(LinkList &L)							//初始化单链表
{
	if ( (L = (Node*)malloc(sizeof(Node)) )==NULL)
	{
		cout<<"链表头结点申请空间失败！即将退出！"<<endl;
		exit(0);
	}
	L->next = NULL;
	return 1;
}
int InsertLinkList(LinkList &L,Record &newRec)			//将r插入单链表中
{
	LinkList sTemp = L;			//新建指针指向单链表 方便后续操作 称作“遍历指针”
	Node* newNode;				//创建一个新节点指针

	//为新指针申请空间
	if( ( newNode = new Node() ) == NULL )
	{
		cout<<"结点申请空间失败！"<<endl;
		return 0;
		exit(0);
	}

	//赋值数据域
	CopyRec(newRec , newNode->data );			//将传进来的newRec拷贝到新节点的数据域中
	if( IsListEmpty(L) )			//如果链表为空，则直接入队
	{
		L->next = newNode;			//头指针指向新数据
		newNode->next = NULL;		//新数据指向空
		return 1;
	}	
	//若链表不为空，则找到适合他的位置插入（按棋盘棋子数升序排列）
	int chessNum = newNode->data.chessBoard.GetChessNum();		//新棋盘的棋子数
	while( sTemp->next !=NULL)
	{
		//遍历每个排行榜每个项目条的棋盘的棋子总数
		int _chessNum = sTemp->next->data.chessBoard.GetChessNum();	
		if( chessNum < _chessNum)		//找到插入点
		{
			newNode->next = sTemp->next;		//赋值新节点后继
			sTemp->next = newNode;			//更新指针
			return 1;		//完成任务
		}else			//继续遍历
		{
			sTemp = sTemp->next;		//更新指针
		}
	}
	if(sTemp->next == NULL )	//"遍历指针"到达末尾仍然未插入
	{
		sTemp->next = newNode;		//新节点插入到最后
		newNode->next =NULL;		//更新指针
	}
	return 1;
}
bool IsListEmpty(LinkList &L)						//判断单链表是否为空
{
	if(L->next == NULL) return true;
	else return false;
}

void ShowList(LinkList &L)							//打印单链表
{
	if( IsListEmpty(L) )
	{
		cout<<endl<<"              ------空------"<<endl<<endl;
		return;
	}else
	{
		cout<<setw(5)<<"排行"<<setw(13)<<"棋盘规格"<<setw(12)<<"获胜玩家"<<setw(10)<<"步数"<<endl;			//头部
		LinkList sTemp = L;						//创建“遍历指针”
		ChessBoard cbShow;					//创建一个用于遍历显示的棋盘
		Record recShow;							//创建一条用于遍历显示的记录
		int count=1;			//声明计数器
		while(sTemp->next != NULL)
		{
			CopyRec(sTemp->next->data,recShow);			//更新“遍历记录”
			recShow.chessBoard.Copy(cbShow);				//更新“遍历棋盘”
			//对相关信息进行打印
			cout<<setw(5)<<count<<setw(9)<<cbShow.GetHeight()<<"×"<<cbShow.GetWidth()
				<<setw(12)<<recShow.winName
				<<setw(10)<<cbShow.GetChessNum()<<endl;
			sTemp = sTemp->next;			//递增
			count++;				//计数器更新
		}
		cout<<endl;
	}
}
void deleList(LinkList &L)			//释放指针
{
	LinkList sTemp = L->next;		//从头结点的下一个结点开始释放，称为“遍历指针”
	LinkList t = sTemp;					//用于记录“遍历指针”的下一个结点位置，称为“记录指针”
	while(sTemp->next !=NULL)
	{
		t = sTemp->next;				//更新“记录指针”
		delete(sTemp);					//删除“遍历指针”指向的位置
		sTemp = t;						//更新“遍历指针"
	}
	delete(sTemp);			//释放末尾结点
	free(L);						//释放头结点
}
void CopyRec(Record &rec , Record &copy)		//拷贝排行榜项目条函数
{
	copy.winName = rec.winName;					//拷贝记录rec的获胜玩家姓名
	rec.chessBoard.Copy(copy.chessBoard);		//拷贝记录rec的棋盘
}