#pragma once
#include "Chess.h"

Chess::Chess(int x,int y, int color)			//棋子的初始化 xy：坐标，color：1白 -1黑
{
	this->x = x;
	this->y = y;
	this->color = color;
}	

/*获取属性信息*/
int Chess:: GetX()				//获取x坐标
{
	return this->x;
}
int Chess:: GetY()				//获取y坐标
{
	return this->y;
}
int Chess:: GetColor()		//获取该子颜色
{
	return this->color;
}

/*设置属性信息*/
void Chess:: SetX(int x)						//设置x坐标
{
	this->x = x;
}
void Chess:: SetY(int y)						//设置y坐标
{
	this->y = y;
}
void Chess:: SetColor(int color)		//设置颜色
{
	this->color = color;
}
void Chess:: SetAll(int x,int y,int color)		//设置所有属性信息
{
	this->x = x;
	this->y = y;
	this->color = color;
}