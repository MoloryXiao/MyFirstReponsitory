#pragma once
#include "Chess.h"

Chess::Chess(int x,int y, int color)			//棋子的初始化 xy：坐标，color：1白 -1黑
{
	this->x = x;
	this->y = y;
	this->color = color;
}	

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