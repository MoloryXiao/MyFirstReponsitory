#pragma once
#include "Chess.h"

Chess::Chess(int x,int y, int color)			//���ӵĳ�ʼ�� xy�����꣬color��1�� -1��
{
	this->x = x;
	this->y = y;
	this->color = color;
}	

int Chess:: GetX()				//��ȡx����
{
	return this->x;
}
int Chess:: GetY()				//��ȡy����
{
	return this->y;
}
int Chess:: GetColor()		//��ȡ������ɫ
{
	return this->color;
}