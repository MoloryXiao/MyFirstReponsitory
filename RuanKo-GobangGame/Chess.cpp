#pragma once
#include "Chess.h"

Chess::Chess(int x,int y, int color)			//���ӵĳ�ʼ�� xy�����꣬color��1�� -1��
{
	this->x = x;
	this->y = y;
	this->color = color;
}	

/*��ȡ������Ϣ*/
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

/*����������Ϣ*/
void Chess:: SetX(int x)						//����x����
{
	this->x = x;
}
void Chess:: SetY(int y)						//����y����
{
	this->y = y;
}
void Chess:: SetColor(int color)		//������ɫ
{
	this->color = color;
}
void Chess:: SetAll(int x,int y,int color)		//��������������Ϣ
{
	this->x = x;
	this->y = y;
	this->color = color;
}