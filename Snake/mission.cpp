#define _CRT_SECURE_NO_WARNINGS
#include "mission.h"
#include <iostream>
#include <math.h>
#include "TheSnakesGame.h"
#include <sstream>
#include <fstream>
#include <string>

void mission::set_currMission_after_rendom() {

	 if (vec_mission_index == 8)
		currMission = 7;
	else if (mission_vec[vec_mission_index].text.find("prime") != std::string::npos)
		currMission = 1;
	else if (mission_vec[vec_mission_index].text.find("squert") != std::string::npos)
		currMission = 2;
	else if (mission_vec[vec_mission_index].text.find("Palindrom") != std::string::npos)
		currMission = 4;
	else if (mission_vec[vec_mission_index].text.find("month") != std::string::npos)
		currMission = 6;
	else if (mission_vec[vec_mission_index].text.find("Catch") != std::string::npos)
		currMission = 0;
	else if (mission_vec[vec_mission_index].text.find("digit") != std::string::npos)
		currMission = 5;
	else if (mission_vec[vec_mission_index].text.find("curry") != std::string::npos)
		currMission = 3;
	else if (mission_vec[vec_mission_index].text.find("$ and $") != std::string::npos)
		currMission = 8;
	
}


void mission::load_mission_from_file() {
	int counter = 0;
	stringstream ss;
	mission_code res;
	ifstream myFile("mission_bank.txt", ios_base::in);
	bool efo = false;
	if (myFile.is_open()) {
		myFile.seekg(0, myFile.beg);
		while (!efo) {
			res.type = myFile.get();
			getline(myFile, res.text);
			if (res.type == 'A' || res.type == 'B' || res.type == 'C')
				counter++;
			if (res.type == 'B') {
				string temp;
				//int i = res.text.find("$");

				getline(myFile, temp);
				ss << temp;
				ss >> res.rand1;
				ss.clear();
				res.rand2 = (-1);
				

			}
			if (res.type == 'C') {
				stringstream ss1;
				string temp, temp2;
				getline(myFile, temp2);
				ss1 << temp2;
				ss1 >> res.rand2;
				ss1.clear();
				getline(myFile, temp);
				ss1 << temp;
				ss1 >> res.rand1;
				ss1.clear();
				

			}
			if (myFile.eof()) {
				efo = TRUE;
			}
			mission_vec.push_back(res);
		}
	}
}

void mission::SetRandNumberForMissions() {
	srand(time(0));
	vec_mission_index =  rand() % mission_vec.size()+1;
	
	set_currMission_after_rendom();
	point_to_eater->update_mission_number(currMission);//update the number of the misiion in the eater class
	if (vec_mission_index != 8) {
		if (mission_vec[vec_mission_index].type == 'C')
			SetRandom_currNum_currNum2(mission_vec[vec_mission_index].rand1, mission_vec[vec_mission_index].rand2, TRUE);
		if (mission_vec[vec_mission_index].type != 'A')
			SetRandom_currNum_currNum2(mission_vec[vec_mission_index].rand1, mission_vec[vec_mission_index].rand2, FALSE);
	}
}

void mission::SetRandom_currNum_currNum2(int num, int num2, bool type) {// return random index for the mission array and random number for the mission   

	srand(time(0));
	currNum = rand() % num;
	if (currNum == 0)
		currNum++;
	if (type == TRUE) {
		srand(time(0));
		currNum2 = rand() % minimum(num2, currNum);
	}

}

int mission::minimum(int num, int curr) {
	if (num > curr)
		return curr;
	return num;
}
//________________________________________________________________________________________________________________

void mission::SetAnswer(char Operator1, char Operator2, int Num1, int Num2, int Num3) {//this function calculate the right answer and insert it to  integer rightanswer (D.M of mision class) 
	switch (Operator1) {
	case('-'):
		switch (Operator2) {
		case('*'):
			RightAnswer = Num1 - (Num2 * Num3);
			break;
		case('/'):
			RightAnswer = Num1 - (Num2 / Num3);
			break;
		case('-'):
			RightAnswer = Num1 - Num2 - Num3;
			break;
		default:
			RightAnswer = Num1 - Num2 + Num3;
			break;

		}
		break;
	case('*'):
		switch (Operator2) {
		case('+'):
			RightAnswer = (Num1 * Num2) + Num3;
			break;
		case('/'):
			RightAnswer = Num1 * Num2 / Num3;
			break;
		case('-'):
			RightAnswer = (Num1 * Num2) - Num3;
			break;
		default:
			RightAnswer = (Num1 * Num2) + Num3;
			break;
		}
		break;
	case('/'):
		switch (Operator2)
		{
		case('*'):
			RightAnswer = Num1 / Num2 * Num3;
			break;
		case('/'):
			RightAnswer = Num1 / Num2 / Num3;
			break;
		case('-'):
			RightAnswer = (Num1 / Num2) - Num3;
			break;
		default:
			RightAnswer = (Num1 / Num2) + Num3;
			break;
		}
		break;
	default:
		switch (Operator2)
		{
		case('*'):
			RightAnswer = Num1 + (Num2 * Num3);
			break;
		case('/'):
			RightAnswer = Num1 + (Num2 / Num3);
			break;
		case('-'):
			RightAnswer = Num1 + Num2 - Num3;
			break;
		default:
			RightAnswer = Num1 + Num2 + Num3;
			break;
		}
		break;
	}
}


void mission::printMission7NotRandomNUM() {
	gotoxy(10, 2);
	cout << arrForMission7[0] << " " << arrForMission7[3] << " " << arrForMission7[1] << " " << arrForMission7[4] << " " << arrForMission7[2] << " " << "= _______";
}
void mission::ShowTherightAnswers() {
	int num;
	int m;
	bool flag = false;
	if (currMission == 7)
		printMission7NotRandomNUM();
	else
		PrintMission();

	for (m = 0; m < 10; m++) {

		for (int i = 0; i < log_size; i++) {
			num = theGame_Mission->GetNumFromBoard(NumArray[i]);
			if (theGame_Mission->IsAnswerCorrect(num)) {
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), m);
					gotoxy(NumArray[i].getX(), NumArray[i].getY());
					cout << num;
					Sleep(100);

					setTextColor(Color::BLACK);
					gotoxy(NumArray[i].getX(), NumArray[i].getY());
					cout << num;
					Sleep(50);

					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), m);
					gotoxy(NumArray[i].getX(), NumArray[i].getY());
					cout << num;
					Sleep(50);

					flag = true;
				}
				setTextColor(Color::WHITE);
			}

		}
		if (!flag)
		{
			gotoxy(15, 20);
			cout << "There is NOT a correct answer on the board!!!" << endl;
			Sleep(400);
		}



	}
}

void mission::deleteRandomNumbersFromArr() {// delete half  of the numbers form the point array randomly 
	int halfSize = log_size / 2;
	int index, count = 0;
	int x, y;
	while (count < halfSize) {
		srand(time(0));
		index = rand() % (halfSize - count);
		//we need to delete a number from the board 
		x = NumArray[index].getX();
		y = NumArray[index].getY();
		theGame_Mission->deleteCharFromBoard(x, y);// delete  the number from board 
		for (int i = index; i < log_size - 1; i++) {

			NumArray[i] = NumArray[i + 1];
		}
		count++;
		log_size--;
	}
}

void mission::InsertNumToArray(int x, int y) {//inserts the numbers that appears on the board to Point array (save the places of the digit only ) 
	NumArray[log_size].set(x, y);
	log_size++;
}


void mission::printOnlyMision7() {
	int num[3];

	char Operator1, Operator2;

	char opArr[4] = { '*','/','+','-' };

	Operator1 = opArr[rand() % 4];//get random  operators 
	srand(time(0));
	Operator2 = opArr[rand() % 4];

	for (int i = 0; i < 3; i++) {//get random numbers 
		num[i] = rand() % (10 - i);
		if (num[i] == 0)// aviod division in zero 
			num[i]++;
		arrForMission7[i] = (char)'0' + num[i];
		srand(time(0));
	}
	arrForMission7[3] = Operator1;
	arrForMission7[4] = Operator2;
	SetAnswer(Operator1, Operator2, num[0], num[1], num[2]);// this function calculate the right answer and insert it to  integer rightanswer (D.M of mision class) 

	cout << num[0] << " " << Operator1 << " " << num[1] << " " << Operator2 << " " << num[2] << " " << "= _______";

}

void mission::PrintMission() {
	int i;
	gotoxy(10, 2);
	setTextColor(Color::WHITE);
	string temp;

	if (currMission ==7) {
		printOnlyMision7();
	}
	else {
		 temp=mission_vec[vec_mission_index].text;
		 if (mission_vec[vec_mission_index].type != 'A')
		 {
			 i = temp.find("$");
			 temp.erase(i, 1);
			 temp.insert(i,1, (char)'0' + currNum);
		 }
		 if (mission_vec[vec_mission_index].type == 'C')
		 {
			 i = temp.find("$");
			 temp.erase(i, 1);
			 temp.insert(i, 1, (char)'0'+currNum2);
		 }
		 cout << temp;

	}
}



//------------------------------------------------------------------------------------------
//functions for the missions answers
// each function return TRUE if the number that the snake ate is correct according to the mission of the level  

bool mission::CollectAnumberDividedBy(int num) {//type B
	SetRandom_currNum_currNum2(mission_vec[vec_mission_index].rand1, mission_vec[vec_mission_index].rand2, 0);

	return (num%currNum == 0);
}
bool mission::CollectAnumberDividedBy_X_and_Y_(int num) {//type c mission 
	SetRandom_currNum_currNum2(mission_vec[vec_mission_index].rand1, mission_vec[vec_mission_index].rand2, 1);

	return (num%currNum == 0 && num%currNum2 == 0);
}

bool mission::Equation(int num) {
	return (num == RightAnswer);
}

bool mission::isPrime(int num) {
	int i = 3;
	if ((num % 2 == 0) || (num == 1))
		return false;
	else
	{
		while (i <= sqrt(num))
		{
			if (num%i == 0)
				return false;
			i += 2;
		}
		return true;
	}
}

bool mission::IsTheSquertInteger(int num)
{
	int res;
	res = sqrt(num);
	if (res*res == num)
		return true;
	else
		return false;

}

bool mission::IsDiviedeByX_with_carry_y(int num) {
	//SetRandom_currNum_currNum2(mission_vec[vec_mission_index].rand1, mission_vec[vec_mission_index].rand2, 1);
	if (num%currNum == currNum2)
		return (TRUE);
	else
		return(FALSE);
}

bool mission::GetSingleDigitNumber(int num) {
	bool flag = false;
	SetRandom_currNum_currNum2(mission_vec[vec_mission_index].rand1, mission_vec[vec_mission_index].rand2, 0);
	if (currNum == 1) {
		if (num / 10 == 0)
			flag = true;
	}
	else if (currNum == 2)
		if (theGame_Mission->CountDigit(num) == 2)
			flag == true;
		else if (currNum == 3)
			if (theGame_Mission->CountDigit(num) == 3)
				flag == true;

	return(flag);
}
//----------------------------------------------------------------
//this two function we invent :one is to check the polindrom number 
// other is to culc the date .
bool mission::isPalindrom(int num) {
	int newNum = 0, num2 = num;
	while (num2 > 0)
	{
		newNum = (newNum * 10) + (num2 % 10);
		num2 = num2 / 10;
	}
	return (newNum == num);
}

bool mission::findTheCrrentDate(int num) {
	int day;
	time_t t = time(0);   // get time now
	struct tm * now = localtime(&t);
	day = (int)now->tm_mday;

	return (day == num);
}








