#ifndef _POINT_H_
#define _POINT_H_

#include <iostream>
#include "io_utils.h"

using namespace std;

class Point {
	enum { UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3 };
	int x, y;
public:
	~Point() {}
	Point():x(0),y(0){}
	Point(int _x, int _y):x(_x), y(_y) {};

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
	//void draw(char ch);
	//void move(int dir);
	//Point getNextPointInBoard(int dir) const;
	friend ostream& operator<<(ostream& out, const Point& p) { 
		out << '(' << p.getX() << ',' << p.getY() << ')'; 
		return out;
	}
};

#endif