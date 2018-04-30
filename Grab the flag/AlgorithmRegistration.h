
#ifndef _ALGORITHMREGISTRATION_H_
#define _ALGORITHMREGISTRATION_H_
#define _CRT_SECURE_NO_WARNINGS
#include <functional>
#include <map>
#include <string>
#include "AbstractPlayer.h"
using namespace std;

class AlgorithmRegistration {
public:
	AlgorithmRegistration(const string& id, std::function<AbstractPlayer*(void)> func) {
		algoFactory[id] = func;
	}
	static map<std::string, std::function<AbstractPlayer*(void)>> algoFactory;
};

#endif