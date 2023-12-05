#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <fstream>
#include <limits> // for numeric_limits

using namespace std;

int generateRandomNumber(int min, int max) {
	return rand() % (max - min + 1) + min;
}