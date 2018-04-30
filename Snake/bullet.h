#ifndef _BULLET_H_
#define _BULLET_H_
#include <cstring>
#include "Point.h"


class TheSnakesGame;
class Snake;
enum { DELETED = -1 };

class bullet {
	int dir;//direction
	char sign='*';//the shap of the bullet
	Point bullet_body;// position of the bulet
	TheSnakesGame* MyGame;
	Snake* My_snake;//pointer to the snack that shot the bullet

public:
	~bullet() {}
	int getDirection () {
		return(dir);
	}
	void UpdateBulltPosition(int x, int y) {//update the x and y in the bullet_body parameter
		bullet_body.set(x, y);

	}
	Point getBullet_point() {//return the posision of the bullet 
		return(bullet_body);
	}
	bool IsTheBulletBelongTo_thisSnake(const Point& next, bullet* bullets_arr,  const int& size);
	void ChangeBulletPlace(bullet* bullets_arr, int& size, int &injury, int &remove_snake);//move the bullets array
	void setbullet(const Point& head);//update the bullet x,y
	void setDirectionOfBullet(const int& snake_direction)//update the diraction of the bullet base on the snake direction
	{
		dir = snake_direction;
	}

	void setGamePointer (TheSnakesGame* _theGame, Snake* _My_snake) {
		MyGame = _theGame;
		My_snake = _My_snake;
	}
};

#endif