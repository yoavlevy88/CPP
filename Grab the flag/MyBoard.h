#ifndef _MYBOARD_H_
#define _MYBOARD_H_

#include "BoardData.h"

class MyBoard : public BoardData {
	char board[rows][cols];
public:
	~MyBoard() { }
	char charAt(int x, int y) const { return board[y][x]; }
	MyBoard& operator=(const BoardData& k) {
		for (int i = 0; i < cols; i++)
			for (int j = 0; j < rows; j++)
				board[j][i] = k.charAt(j+1, i+1);
	}
	void setSquare(int x, int y, char ch) { board[x][y] = ch; }
};

#endif