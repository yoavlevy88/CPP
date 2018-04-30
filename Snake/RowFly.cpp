#include "RowFly.h"
#include "Point.h"
#include "Snake.h"
#include "TheSnakesGame.h"

void Rowfly::moveRowfly() {
	int i, remove_snake, injury;
	int time = 0;

	while (time < 2) {
		remove_snake = 0;
		Point next;
		if (strcmp(name, "second") == 0) {
			if (RowFly_body.getX() == 1)
				changeRowflyDirection(RIGHT);
			else if (RowFly_body.getX() == 78)
				changeRowflyDirection(LEFT);
		}
		RowFly_body.draw(' ');
		ChangeRowflyPlace(RowFly_body, remove_snake);
		next = RowFly_body.GetnextPoint(dir);
		RowFly_body.set(next.getX(), next.getY());
		//����� ��� �� ��� �� ���� �� ���� ���
		setTextColor(Color::WHITE);
		RowFly_body.draw('!');
		if (remove_snake == TRUE) {
			removeSnakeFromScreen(RowFly_body);
		}
		time++;
	}
}

void Rowfly::removeSnakeFromScreen(Point & p) {
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

void Rowfly::ChangeRowflyPlace(Point RowFly_body, int &remove_snake) {//move a RowFly
	int selection;
	Point next_p;

	next_p = RowFly_body.GetnextPoint(dir);
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
		RowFly_body.draw(' ');
		RowFly_body.move(dir);
		RowFly_body.draw(sign);
	}

}