#include "Snake.h"
#include "TheSnakesGame.h"
#include "Point.h"
#include"mission.h"


void Snake::deletebulletFromArr( Point& p) {
	int x, y;
	for (int i = 0; i <= counter_bullet; i++)
	{
		if (bullets_arr[i].getBullet_point().PointCompare(p)) {
			x=bullets_arr[i].getBullet_point().getX();
			y=bullets_arr[i].getBullet_point().getY();
			gotoxy(x,y);
			cout << ' ';
			bullets_arr[i].UpdateBulltPosition(DELETED, DELETED);
		}
	}
}

bool Snake::checkforBullet(const Point& p) {//check if the posision of p is as one of the bullets on the board
	Point temp;
	

	for (int i = 0; i <= this->counter_bullet; i++)
	{
		temp = bullets_arr[i].getBullet_point();
		if ((temp.getX() == p.getX()) && (temp.getY() == p.getY()))
			return (TRUE);//if the next step of the bullet is aposition of another bullet 
	}
	return(FALSE);
}

bool Snake::checkforRowfly(const Point& p) {//check if the posision of p is as one of the bullets on the board
	Point temp;

	for (int i = 0; i <= 2; i++)
	{
		if ((theGame->getRowflyPos(i).getX() == p.getX()) && ((theGame->getRowflyPos(i).getY() == p.getY())))
			return (TRUE);//if the next step of the bullet is aposition of another bullet 
	}
	return(FALSE);
}

bool Snake::checkforColfly(const Point& p) {//check if the posision of p is as one of the bullets on the board
	Point temp;

	for (int i = 0; i <= 2; i++)
	{
		if ((theGame->getColflyPos(i).getX() == p.getX()) && ((theGame->getColflyPos(i).getY() == p.getY())))
			return (TRUE);//if the next step of the bullet is aposition of another bullet 
	}
	return(FALSE);
}

bool Snake::checkforEaterfly(const Point& p) {
	Point temp;

	if ((theGame->getEaterflyPos().getX() == p.getX()) && ((theGame->getEaterflyPos().getY() == p.getY())))
		return (TRUE);//if the next step of the bullet is aposition of another bullet 
	return(FALSE);
}

void Snake::removeDeletedCellFrom_Bullet_Array() {
	int i , size = counter_bullet;
	Point temp;

	for (i = 0; i <= size; i++) {
		temp=bullets_arr[i].getBullet_point();
		if (temp.getX() == DELETED && temp.getY() == DELETED){
			for (int j = i; j < size; j++)
				bullets_arr[j] = bullets_arr[j + 1];
			size=counter_bullet--;
		}
	}
}
void Snake::update_cell_in_bullets_arr(int index, Point&p) {//get index and point than update the bullets_array (used to the matrix-bullets array)
	bullets_arr[index].setbullet(p);


}
void Snake::update_cell_in_snake_body_arr(int index, Point&p) {//get point(x,y) and update the body array

	body[index].set(p.getX(), p.getY());
}

void Snake::moveBullet() {
	int i, remove_snake;
	int time = 0;
	
	while (time < 2) {
		for (i = 0; i <= counter_bullet; i++) {
			remove_snake = 0;
			Point next;
			if (bullets_arr[i].getBullet_point().getX() != DELETED) {
				next = bullets_arr[i].getBullet_point().GetnextPoint(bullets_arr[i].getDirection());
				bullets_arr[i].ChangeBulletPlace(bullets_arr, counter_bullet, injury, remove_snake);
			}
			if (remove_snake == TRUE) {
				removeSnakeFromScreen(next);
				deletebulletFromArr(bullets_arr[i].getBullet_point());
				
			}
			if (injury == 1) {
				OptionalSize--;
				injury = 0;
				
			}
		}
		theGame->vec[theGame->get_vector_index()+time].update_bullet_inMat(*this);
		time++;
	}
	theGame->update_counter_vector();
}

void Snake::removeSnakeFromScreen(Point & p) {
	bool thisSnake=false;
	int i = 0;

	while((i < SnakeLen) && (!thisSnake))
	{
		if (p.PointCompare(body[i]))
		{
			thisSnake = true;
			deleteSnakeBodyFromScreen();
			SetFiveNumbersCountToZero();
			break;
		}
		i++;
	}
	if (!thisSnake) {
		P_toOtherSnake->deleteSnakeBodyFromScreen();
		P_toOtherSnake->SetFiveNumbersCountToZero();
		injury = 1;
	}
}

void Snake::deleteSnakeBodyFromScreen(){
	for (int i = 0; i <SnakeLen; i++) {
		body[i].draw(' ');
		body[i].set(-1,-1);
	}
	gotoxy(0,24);
	disapear = TRUE;
}

void Snake::replaceSnakeInRandomPlace() {
	bool printed = FALSE;
	Point p;


	while (!printed) {
		p.set((rand() % 76) + 1, (rand() % 19) + 4);
		if (theGame->checkDotInTheBoard(p, 1)) {
			
			gotoxy(p.getX(), p.getY());
			ResetPlaceForSnake(p.getX(), p.getY(), direction);

			printed = true;
		}

	}
}

void Snake::printMyarray(int type) {//print the bullets array and the snake shap

	Point p;
	if (type == BULLET) {
		for (int i = 0; i < counter_bullet; i++)
		{
			p = bullets_arr[i].getBullet_point();
			gotoxy(p.getX(), p.getY());
			setTextColor(Color::WHITE);
			cout << '*';
		}
	}
	if (type == SNAKE)
	{
		for (int i = 0; i < SnakeLen; i++)
		{
			gotoxy(body[i].getX() , body[i].getY());
			setTextColor(color);
			cout << sign;
			setTextColor(Color::WHITE);
		}
	}
	gotoxy(0, 0);
}

void Snake::move() {

	int Selection;
	body[SnakeLen - 1].draw(' ');
	for (int i = SnakeLen - 1; i > 0; --i) {
		body[i] = body[i - 1];
		setTextColor(color);
		body[0].draw(sign);
	}

	if (Selection = theGame->checkNextMove(body[0].GetnextPoint(direction)))//return 2-for digit ; 1- for ' ' ; 0- for snake 
	{  
		body[0].move(direction);
		setTextColor(color);
		body[0].draw(sign);
		setTextColor(Color::WHITE);
		
		theGame->vec[theGame->get_vector_index()].update_snake_location_len(*this);

		if (Selection == DIGIT) {//if the snake eat anumber
			theGame->DeleteNumFromScreen(body[0].getX(), body[0].getY());
			if (theGame->IsAnswerCorrect(theGame->GetNumFromBoard(body[0]))) {//if the snake ate a right answer 
				this->setIfSnackWon(1);
				Sleep(1000);
			}
			else// if  the answer is false  
			{
				this->setIfSnackWon(0);
				Sleep(1000);
			}
			theGame->deleteCharFromBoard(body[0].getX(), body[0].getY());
		}
		else if(Selection==SNAKE)//if the next move is another snake
		{   
			body[0].move(4);
			setTextColor(color);
			body[0].draw(sign);
			theGame->vec[theGame->get_vector_index()].update_snake_location_len(*this);

			setTextColor(Color::WHITE);
		}
		else if ((Selection == NUMEATER) || (Selection == BULLET) || (Selection == ROWFLY) || (Selection == COLFLY)) {
			removeSnakeFromScreen(body[0]);
		}
	}
	gotoxy(0, 24);
}

bool Snake::checkForSnakes(const Point& p) {//return true if the position of p is the same of the body of one of the snakes
	int x = p.getX(), y = p.getY();
	for (int i = 0; i < SnakeLen; i++){
		if ((x == body[i].getX()) && (y == body[i].getY()))
			return true;
	}
	return false;
}

int Snake::getDirection(char key) {//check if the key that the user insert is part of arrowkeys array
	for (int i = 0; i < 5; ++i) {
		if (key == arrowKeys[i]) {
			return i;
		}
	}
	return -1;
}

void Snake::setbulletArray() {

	if (OptionalSize < 5) {
		this->counter_bullet++;
		if (counter_bullet == 5) {
			for (int i = 0; i < 5; i++) {
				if (bullets_arr[i].getBullet_point().getX() == DELETED) {
					bullets_arr[i].setbullet(this->body[0]);
					bullets_arr[i].setDirectionOfBullet(this->direction);
					bullets_arr[i].setGamePointer(theGame, this);
				}
			}
			counter_bullet = 4;
		}
		else {
			bullets_arr[this->counter_bullet].setbullet(this->body[0]);
			bullets_arr[this->counter_bullet].setDirectionOfBullet(this->direction);
			bullets_arr[this->counter_bullet].setGamePointer(theGame, this);
		}
		OptionalSize++;
	}
	

}