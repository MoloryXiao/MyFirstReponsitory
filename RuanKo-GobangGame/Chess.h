#pragma once

//�������ӽṹ��
class Chess {
private :
	int x;				//���ӵĺ�����
	int y;				//���ӵ�������
	int color;		//���ӵ���ɫ		-1Ϊ��ɫ 1Ϊ��ɫ
public :
	Chess(int x=0,int y=0, int color=0);			//���ӵĳ�ʼ�� xy�����꣬color��1�� -1��
	int GetX();				//��ȡx����
	int GetY();				//��ȡy����
	int GetColor();		//��ȡ������ɫ
};