#pragma once
#include "Menu.h"

void SayHello()						//显示欢迎界面
{
	//┓╋┗┗
	cout<<"┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓"<<endl
		<<"○●○●○●欢迎进入五子棋游戏●○●○●○"<<endl
		<<"┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗"<<endl;
}
void ShowMainMenu()			//显示主菜单
{
	cout<<"\t  ●○  1. 新建游戏"<<endl
		<<"\t  ●○  2. 加载棋局"<<endl
		<<"\t  ●○  3. 排行榜"<<endl
		<<"\t  ●○  4. 游戏规则"<<endl
		<<"\t  ●○  5. 关于我们"<<endl
		<<"\t  ●○  0. 退出"<<endl;
}
void SayGoodbye()					//显示结束界面
{
	cout<<"┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓"<<endl
		<<"○●○●○● G A M E  O V E R ●○●○●○"<<endl
		<<"┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗"<<endl;
}
void ShowGameRules()			//显示游戏规则界面
{

}
void ShowAboutUs()				//显示关于我们
{
	cout<<"\t ○●  游戏编号：GB"<<endl<<endl
		<<"\t ○●  作者：Xiao Molory"<<endl<<endl
		<<"\t ○●  版本：version 2.0"<<endl<<endl;		
}
void ShowRankTitle()				//显示排行榜头部
{
	cout<<"┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓"<<endl
		<<"○●○●○●  五子棋  排行榜  ●○●○●○"<<endl
		<<"┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗"<<endl;
}
void ShowGameGoTitle()			//显示正在游戏头部
{
	cout<<"\t ┏━━━━━━┓"<<endl
		<<"\t ┃  游戏开始  ┃"<<endl
		<<"\t ┗━━━━━━┛"<<endl;
}
void ShowGameEndTitle()		//显示游戏结束头部
{
	cout<<"\t ┏━━━━━━┓"<<endl
		<<"\t ┃  游戏结束  ┃"<<endl
		<<"\t ┗━━━━━━┛"<<endl;
}
void BoardReappearTitle()		//显示棋盘重现的头部
{
	cout<<"┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓┓"<<endl
		<<"○●○●○● 排行榜  棋盘重现 ●○●○●○"<<endl
		<<"┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗┗"<<endl;
}