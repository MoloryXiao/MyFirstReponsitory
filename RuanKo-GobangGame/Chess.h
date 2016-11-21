#pragma once

//定义棋子结构体
class Chess {
private :
	int x;				//棋子的横坐标
	int y;				//棋子的纵坐标
	int color;		//棋子的颜色		-1为黑色 1为白色
public :
	Chess(int x=0,int y=0, int color=0);			//棋子的初始化 xy：坐标，color：1白 -1黑
	int GetX();				//获取x坐标
	int GetY();				//获取y坐标
	int GetColor();		//获取该子颜色
};