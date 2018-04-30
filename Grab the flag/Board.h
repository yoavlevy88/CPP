#ifndef _BOARD_
#define _BOARD_
//#include "BattleTool.h"
#include "square.h"
#include "Point.h"
#include "io_utils.h"
#include "MyBoard.h"


class Board {
	Square board[13][13];
public:
	char getTool(Point p);
	int getType(Point p) const;
	void printToScreen(Point p);//this prints the point to the screen in the right place and clear it if there is nothing in it
	Board(){};
	~Board() {};
	void updateSquare(Point p,int type, char tool);// to change the content of the square
	void setBoardProperties(Point* points, int len, int type);// this will put the types of the squares in the board with the array of points
	bool isEmpty(Point p);
	//bool checkNextStep(Point p, Point nextP);
	bool isCaptureFlag(Point p) const;
	void blinkTool(Point p);
	void clean();//remove all the squares properties
	bool checkIfGoodPoint(Point p, Point q);
	MyBoard makeMyBoard(int playerNum);
	char getChar(Point p);
};

#endif