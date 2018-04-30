#include "bullet.h"
#include "Point.h"
#include "Snake.h"
#include "TheSnakesGame.h"


void bullet::setbullet(const Point& head) {//the bullet position is the same as the potision of the snake head
	bullet_body.set(head.getX(), head.getY());
}

void bullet::ChangeBulletPlace(bullet* bullets_arr, int& size, int &injury, int &remove_snake) {//move a singel bullet
	int selection;
	Point next_p;

	next_p = bullet_body.GetnextPoint(dir);
	selection = MyGame->checkNextMove(next_p);
	bullet_body.draw(' ');
	bullet_body.move(dir);
	bullet_body.draw(sign);
	if (selection == DIGIT) {
		MyGame->DeleteNumFromScreen(next_p.getX(), next_p.getY());
		MyGame->deleteCharFromBoard(next_p.getX(), next_p.getY());
		My_snake->deletebulletFromArr(bullet_body);
	}

	else if (selection == SNAKE) {
		if ((IsTheBulletBelongTo_thisSnake(bullet_body, bullets_arr, size)) == FALSE) {//if the snake shoot by his own bullet we will delete the bullet and update size--
			injury = 1;
		}	
		remove_snake = true;
	}

	else if (selection == BULLET) {
		if (IsTheBulletBelongTo_thisSnake(next_p, bullets_arr, size)) {//if the snake shoot by his own bullet we will delete the bullet and update size--
			My_snake->deletebulletFromArr(bullet_body);
		}
		else {
			My_snake->getPtosnack()->deletebulletFromArr(next_p);
			My_snake->deletebulletFromArr(bullet_body);
		}
	}
	else if (selection == ROWFLY)
	{
		if (IsTheBulletBelongTo_thisSnake(next_p, bullets_arr, size)) {//if the snake shoot by his own bullet we will delete the bullet and update size--
			My_snake->deletebulletFromArr(bullet_body);
		}
		else {
			My_snake->getPtosnack()->deletebulletFromArr(next_p);
			My_snake->deletebulletFromArr(bullet_body);
		}
	}
	else if ((selection == NUMEATER) || (selection == COLFLY)) {
		if ((MyGame->getColflyPos(0).getX() == bullet_body.getX()) && (MyGame->getColflyPos(0).getY() == bullet_body.getY()))
		{
			Point z;
			z.set(1,24);
			MyGame->setColflyPos(z, 0);
		}
		if ((MyGame->getColflyPos(1).getX() == bullet_body.getX()) && (MyGame->getColflyPos(1).getY() == bullet_body.getY()))
		{
			Point z;
			z.set(1, 24);
			MyGame->setColflyPos(z, 1);
		}
	}
}

bool bullet::IsTheBulletBelongTo_thisSnake(const Point& next, bullet* bullets_arr, const int& size) {//check if the bullet is in the bullets array of one of the snacks
	int x = next.getX(), y = next.getY();
	int x_, y_;
	for (int i = 0; i <= size; i++)
	{
		x_ = bullets_arr[i].getBullet_point().getX();
		y_ = bullets_arr[i].getBullet_point().getY();
		//if the snake shoot by his own bullet 
		
		if (x == x_ && y == y_) {//if the next move of the bullet is as the position of one of the bullet in  bullet array 
			gotoxy(x_, y_);
			cout << ' ';
			//bullets_arr[i].UpdateBulltPosition(DELETED, DELETED);
			return TRUE;
			//insert the last bullet in index=size to the bullet_arr in index=i-->than we delete the last cell from the bullet_array
		}
	}
	//if the snake shoot by the other snake
	return FALSE;
}