#include "AlgorithmRegistration.h"

map<std::string, std::function<AbstractPlayer*(void)>> AlgorithmRegistration::algoFactory;
