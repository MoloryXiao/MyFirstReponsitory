#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "ChessBoard.h"
using namespace std;

/*加载游戏的记录*/
typedef struct HistoryRec
{
	Player p1;					//棋手1
	Player p2;					//棋手2
	ChessBoard cb;		//未完的棋盘			
	string saveTime;		//存储时间
}HistoryRec;