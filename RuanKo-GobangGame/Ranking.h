#include <iostream>
#include "ChessBoard.h"
using namespace std;

class Ranking{
private:
	int rankLen;					//���а񳤶�
	ChessBoard *list;			//���а�����
public:
	/*���캯��*/
	Ranking(int rankLen=0);
	/*
	int PushBoard(ChessBoard cb);			//����ѹ�뷵��1�����򷵻�0
	int PopBoard();									//�����صĵ�����������������1�����򷵻�0
	int PopBoard(ChessBoard *cb);			//���صĵ�����������������1�����򷵻�0
	*/
};
