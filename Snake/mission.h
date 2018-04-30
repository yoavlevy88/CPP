
#ifndef _MISSION_H_
#define _MISSION_H_

using namespace std;

#include "Point.h"
#include <iostream>
#include "io_utils.h"
#include <ctime>
#include <vector>
class TheSnakesGame;
class num_eater;

struct mission_code {
	char type;
	string text;
	int rand1;
	int rand2;

};
class mission {
	enum { NUM_MISSIONS = 8 };
	TheSnakesGame* theGame_Mission;//Pointer to the snakesgame class
	num_eater* point_to_eater;
	Point NumArray[60];//array of all the digits on the bord
	int log_size = 0;//size of the numbers array 
	int currNum;//Random number for  mission number 0
	int currNum2;
	int currMission;//The current mission index for missionTypes array
	int vec_mission_index;
	char missionTypes[7][70] = { "Collect a number divided by: " , "Collect a prime number!" , "Collect a number that is a squert of an integer!" , "Collect a number that is divieded By 7 with a curry of 3!", "Find A Palindrom number!", "Find A single digit number!", "Find the current day of the month!" };
	// integers for misiion 7 
	int  RightAnswer;
	char arrForMission7[5];//arr for operators mission 7 

	vector <mission_code>mission_vec;
public:
	void set_currMission_after_rendom();
	void load_mission_from_file();
	Point getPointFromArray(int i) {
		return (NumArray[i]);
	}
	~mission() {
	}
	void set_point_to_eater(num_eater* _point_to_eater) {
		point_to_eater = _point_to_eater;
	}
	void ptintNumArray() {

		for (int i = 0; i < log_size; i++)
			cout << NumArray[i].getX() << ',' << NumArray[i].getY() << ' ';
	}
	void setmission(TheSnakesGame* __theGame) {
		theGame_Mission = __theGame;
	}
	int getCurrNum() const {
		return currNum;
	}
	int getNumberMission() const {
		return currMission;
	}
	void setLogSize(int size) {
		log_size = size;
	}
	int GetLogSize() {
		return(log_size);
	}
	void printOnlyMision7();
	void deleteRandomNumbersFromArr();
	void InsertNumToArray(int x, int y);
	void PrintMission();
	bool CollectAnumberDividedBy(int num);
	bool isPrime(int num);
	bool IsTheSquertInteger(int num);
	bool IsDiviedeByX_with_carry_y(int num);
	bool GetSingleDigitNumber(int num);
	bool isPalindrom(int num);
	bool findTheCrrentDate(int num);
	bool Equation(int num);
	void ShowTherightAnswers();
	bool CollectAnumberDividedBy_X_and_Y_(int num);
	void mission::SetRandom_currNum_currNum2(int num, int num2, bool type);
	void SetRandNumberForMissions();
	int minimum(int num, int curr);
	void SetAnswer(char Operator1, char Operator2, int Num1, int Num2, int Num3);
	void printMission7NotRandomNUM();//print misiion 7 with the numbers and operator that in char *arrForMission7
	int getLenOfMission() {
		return strlen(missionTypes[currMission]);
	}
};

#endif