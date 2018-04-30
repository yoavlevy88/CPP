#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utils.h"

using namespace std;

class Point {
	enum { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3, NO = 10};
	int x, y;
public:
	~Point() {
	}
	int getX() const {
		return x;
	}
	int getY() const {
		return y;
	}
	void set(int _x, int _y) {
		x = _x;
		y = _y;
	}
	void draw(char ch);
	void move(int direction);
	Point GetnextPoint(const int &direction);//the next point of the head of the snack 
	bool PointCompare(Point& OterP);
};

#endif