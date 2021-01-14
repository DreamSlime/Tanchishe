#pragma once
#include <iostream>
#include "wall.h"
using namespace std;

class Food {
public:
	Food(Wall& tempwall);
	//…Ë÷√ ≥ŒÔ
	void setFood();

	int count;
	int foodX, foodY;
	int foodX1, foodY1;
	int foodX2, foodY2;
	int foodX3, foodY3;
	int foodX4, foodY4;
	Wall& wall;
	bool special;
};