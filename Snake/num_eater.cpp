#include "num_eater.h"
#include "TheSnakesGame.h"

void num_eater::moveEater() {
	Point next;
	int selection;

	if (getSidesMoves() > 0)
	{
		body.draw(' ');
		next = body.GetnextPoint(getSidesKind());
		selection = MyGame->checkNextMove(next);//return 2-for digit ; 1- for ' ' ; 0- for snake 
		body.set(next.getX(), next.getY());
		setTextColor(Color::WHITE);
		body.draw(sign);
		setSidesMoves(getSidesMoves() - 1);
		if (selection == DIGIT) {//if the snake eat anumber
			MyGame->DeleteNumFromScreen(body.getX(), body.getY());
			MyGame->deleteCharFromBoard(body.getX(), body.getY());
		}
		else if (selection == SNAKE)//if the next move is another snake
		{
			pToSnake1->removeSnakeFromScreen(next);
		}
		else if (selection == BULLET) {
			body.set(-1, -1);
		}
	}

	if (getUpDownMoves() > 0)
	{
		body.draw(' ');
		next = body.GetnextPoint(getUpDownKind());
		selection = MyGame->checkNextMove(next);//return 2-for digit ; 1- for ' ' ; 0- for snake 
		body.set(next.getX(), next.getY());
		setTextColor(Color::WHITE);
		body.draw(sign);
		setUpDownMoves(getUpDownMoves() - 1);
		if (selection == DIGIT) {//if the snake eat anumber
			MyGame->DeleteNumFromScreen(body.getX(), body.getY());
			MyGame->deleteCharFromBoard(body.getX(), body.getY());
		}
		else if (selection == SNAKE)//if the next move is another snake
		{
			pToSnake1->removeSnakeFromScreen(next);
		}
		else if (selection == BULLET) {
			body.set(-1, -1);
		}
	}
}


void num_eater::checkWhereToGo() {
	int res_x1, res_y1, res_x2, res_y2, res_x3, res_y3, rightA_x, leftA_x, rightB_x, leftB_x;
	int upA_y, downA_y, upB_y, downB_y, shorterX, shorterY;
	Point P_answer = vec_answers[0];

	res_x1 = P_answer.getX() - body.getX();
	res_y1 = P_answer.getY() - body.getY();

	rightA_x = 79 - P_answer.getX();
	leftA_x = P_answer.getX() - 1;
	rightB_x = 79 - body.getX();
	leftB_x = body.getX() - 1;

	upA_y = P_answer.getY() - 4;
	downA_y = 23 - P_answer.getY();
	upB_y = body.getY() - 4;
	downB_y = 23 - body.getY();

	res_x2 = rightA_x + leftB_x;
	res_x3 = leftA_x + rightB_x;

	res_y2 = upA_y + downB_y;
	res_y3 = downA_y + upB_y;

	shorterX = whoIsTheShorter(abs(res_x1), res_x2, res_x3);
	shorterY = whoIsTheShorter(abs(res_y1), res_y2, res_y3);

	//=======LEFT or RIGHT
	if (shorterX == 1)
	{
		if (res_x1 < 0)
		{
			setSidesMoves(abs(res_x1));
			setSidesKind(LEFT);
		}
		else if (res_x1 > 0) {
			setSidesMoves(abs(res_x1));
			setSidesKind(RIGHT);
		}
		else
		{
			setSidesMoves(0);
			setSidesKind(LEFT); //not exists
		}
	}
	else if (shorterX == 2)
	{
		setSidesMoves(res_x2);
		setSidesKind(LEFT);
	}
	else
	{
		setSidesMoves(res_x3);
		setSidesKind(RIGHT);
	}

	//=======UP or DOWN
	if (shorterY == 1)
	{
		if (res_y1 < 0)
		{
			setUpDownMoves(abs(res_y1));
			setUpDownKind(UP);
		}
		else if (res_y1 > 0) {
			setUpDownMoves(abs(res_y1));
			setUpDownKind(DOWN);
		}
		else
		{
			setUpDownMoves(0);
			setUpDownKind(LEFT); //not exists
		}
	}
	else if (shorterY == 2)
	{
		setUpDownMoves(res_y2);
		setUpDownKind(DOWN);
	}
	else
	{
		setUpDownMoves(res_y3);
		setUpDownKind(UP);
	}
}

int num_eater::whoIsTheShorter(int res1, int res2, int res3) {
	if ((res1 <= res2) && (res1 <= res3))
		return 1;
	else if ((res2 <= res1) && (res2 <= res3))
		return 2;
	else if ((res3 <= res1) && (res3 <= res2))
		return 3;
}

