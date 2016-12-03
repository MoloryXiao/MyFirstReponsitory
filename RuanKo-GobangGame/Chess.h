#pragma once

//定义棋子结构体
class Chess {
private :
	int x;				//棋子的横坐标
	int y;				//棋子的纵坐标
	int color;		//棋子的颜色		-1为黑色 1为白色
public :
	Chess(int x=0,int y=0, int color=0);			//棋子的初始化 xy：坐标，color：白1  黑-1

	/*获取属性信息*/
	int GetX();				//获取x坐标
	int GetY();				//获取y坐标
	int GetColor();		//获取该子颜色

	/*修改属性信息*/
	void SetX(int x);							//设置x坐标
	void SetY(int y);							//设置y坐标
	void SetColor(int color);				//设置颜色
	void SetAll(int x,int y,int color);	//设置所有信息
};