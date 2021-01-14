#include "food.h"
#include <windows.h>
Food::Food(Wall& tempwall) :wall(tempwall) {
	special = false;
	count = 1;
}

void gotoxy2(HANDLE hOut2, int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut2, pos);
}
HANDLE hOut2 = GetStdHandle(STD_OUTPUT_HANDLE);


void Food::setFood() {
	while (true) {
		foodX = rand() % (Wall::ROW - 2) + 1;
		foodY = rand() % (Wall::COL - 2) + 1;
		//如果随机的位置不是蛇头或蛇身，就随机生成
		if (count % 5 == 0) {
			if (wall.getWall(foodX, foodY) == ' ' && wall.getWall(foodX + 1, foodY) == ' ' && wall.getWall(foodX, foodY + 1) == ' ' && wall.getWall(foodX + 1, foodY + 1) == ' ') {
				special = true;
				foodX1 = foodX, foodY1 = foodY;
				foodX2 = foodX + 1, foodY2 = foodY;
				foodX3 = foodX, foodY3 = foodY + 1;
				foodX4 = foodX + 1, foodY4 = foodY + 1;
				wall.setWall(foodX, foodY, '#');
				gotoxy2(hOut2, foodY * 2, foodX);
				cout << "#";
				wall.setWall(foodX + 1, foodY, '#');
				gotoxy2(hOut2, foodY * 2, foodX + 1);
				cout << "#";
				wall.setWall(foodX, foodY + 1, '#');
				gotoxy2(hOut2, (foodY + 1) * 2, foodX);
				cout << "#";
				wall.setWall(foodX + 1, foodY + 1, '#');
				gotoxy2(hOut2, (foodY + 1) * 2, foodX + 1);
				cout << "#";
				break;
			}
		}
		if (wall.getWall(foodX, foodY) == ' ') {
			special = false;
			wall.setWall(foodX, foodY, '#');
			gotoxy2(hOut2, foodY * 2, foodX);
			cout << "#";
			break;
		}
	}
}