#pragma once
#include "Ranking.h"
#define MAXSIZE 200		//排行榜最大长度

Ranking:: Ranking()
{
	this->rankLen = 0;
	InitLinkList(this->list);
}
Ranking:: ~Ranking()
{
	//cout<<"删除排行榜"<<endl;
	//system("pause");
	deleList(this->list);
	//cout<<"删除成功！"<<endl;
	//system("pause");
}
/*获取属性信息*/
int Ranking::GetRankLen()				//rankLen属性
{
	return this->rankLen;
}

/*一般成员函数*/
int Ranking::InsertRec(ChessBoard &cb , string winName)		//插入一条记录
{
	Record newRec;				//创建一个新纪录
	newRec.winName = winName;		//赋值记录的胜利玩家姓名
	cb.Copy(newRec.chessBoard);			//对棋盘进行拷贝
	InsertLinkList(this->list , newRec);	//插入到链表中
	this->rankLen++;				//排行榜长度加一
	return 1;
}

void Ranking::ShowRank()				//打印排行榜
{
	ShowList(this->list);
}

void Ranking::ShowTheBoard(int count)			//打印排行榜第count个棋盘
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
			cout<<"玩家："<<sTemp->next->data.winName<<" 获得本场游戏的胜利！   "
				<<"位列榜单第【"<<count<<"】名！"<<endl<<endl;
			break;
		}
		else 
			sTemp = sTemp->next;
	}
}