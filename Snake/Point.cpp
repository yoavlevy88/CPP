#include "Point.h"

void Point::draw(char ch) {
	gotoxy(x, y);
	cout << ch << endl;
}

void Point::move(int dir) {
	switch (dir) {
	case UP: // UP
		--y;
		if (y < 4) {
			y = 22;
		}
		break;
	case DOWN: // DOWN
		++y;
		if (y > 22) {
			y = 4;
		}
		break;
	case LEFT: // LEFT
		--x;
		if (x < 1) {
			x = 78;
		}
		break;
	case RIGHT: // RIGHT
		++x;
		if (x > 78) {
			x = 1;
		}
		break;
	case NO: //not move
		break;
	break;
	}
}

Point Point::GetnextPoint(const int &direction) {
	Point next = *this;
	next.move(direction);
	return next;
}

bool Point::PointCompare(Point& OterP) {
	return ((x == OterP.getX()) && (y == OterP.getY()));
}
