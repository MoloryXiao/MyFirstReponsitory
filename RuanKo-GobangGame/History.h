#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "ChessBoard.h"
using namespace std;

/*������Ϸ�ļ�¼*/
typedef struct HistoryRec
{
	Player p1;					//����1
	Player p2;					//����2
	ChessBoard cb;		//δ�������			
	string saveTime;		//�洢ʱ��
}HistoryRec;