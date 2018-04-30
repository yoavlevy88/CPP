#ifndef _CREATURES_H_
#define _CREATURES_H_
#include <cstring>
#include "Point.h"


class TheSnakesGame;

class Creature {
	int dir;//direction
	char sign;//the shap of the bullet
	Point place;
	TheSnakesGame* MyGame;

public:
	Creature(Point _place, char _sign, int _dir) {
		place = _place;
		sign = _sign;
		dir = _dir;
	}
	~Creature() {
	}
	int getDirection() {
		return(dir);
	}

	Point getCreature_point() {//return the posision of the bullet 
		return(place);
	}
	Point setCreature_point(int x, int y) {
		place.set(x, y);
	}

	void setGamePointer(TheSnakesGame* _theGame) {
		MyGame = _theGame;
	}
};

#endif