#include "ColFly.h"
#include "Point.h"
#include "Snake.h"
#include "TheSnakesGame.h"

void Colfly::moveColfly() {
	int i, remove_snake;
	int time = 0;

	remove_snake = 0;
	Point next;
	if (strcmp(name, "second") == 0) {
		if (ColFly_body.getY() == 4)
			changeColflyDirection(DOWN);
		else if (ColFly_body.getY() == 22)
			changeColflyDirection(UP);
	}
	ColFly_body.draw(' ');
	ChangeColflyPlace(ColFly_body, remove_snake);
	next = ColFly_body.GetnextPoint(dir);
	ColFly_body.set(next.getX(), next.getY());
	//����� ��� �� ��� �� ���� �� ���� ���
	setTextColor(Color::WHITE);
	ColFly_body.draw('$');
	if (remove_snake == TRUE) {
		removeSnakeFromScreen(ColFly_body);
	}
}

void Colfly::removeSnakeFromScreen(Point & p) {
	bool thisSnake = false;
	int i = 0;

	while ((i < pToSnake1->getLen()) && (!thisSnake))
	{
		if (p.PointCompare(pToSnake1->get_body_cell(i)));
		{
			thisSnake = true;
			pToSnake1->deleteSnakeBodyFromScreen();
			pToSnake1->SetFiveNumbersCountToZero();
			break;
		}
		i++;
	}
	if (!thisSnake) {
		pToSnake1->getPtosnack()->deleteSnakeBodyFromScreen();
		pToSnake1->getPtosnack()->SetFiveNumbersCountToZero();
	}
}

void Colfly::ChangeColflyPlace(Point ColFly_body, int &remove_snake) {//move a ColFly
	int selection;
	Point next_p;

	next_p = ColFly_body.GetnextPoint(dir);
	selection = MyGame->checkNextMove(next_p);
	if (selection == DIGIT) {
		MyGame->DeleteNumFromScreen(next_p.getX(), next_p.getY());
		MyGame->deleteCharFromBoard(next_p.getX(), next_p.getY());
	}

	else if (selection == SNAKE) {
		remove_snake = true;
	}

	else if (selection == BULLET) {
		
	}

	else {//if selection == TRUE-empty place 
		ColFly_body.draw(' ');
		ColFly_body.move(dir);
		ColFly_body.draw(sign);
	}
}