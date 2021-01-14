#define _CRT_SECURE_NO_WARINGS
#include <iostream>
using namespace std;
#include "wall.h"
#include "snake.h"
#include "food.h"
#include <ctime>
#include <conio.h>
#include <windows.h>

void gotoxy(HANDLE hOut, int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut, pos);
}
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

int main() {
	srand((unsigned int)time(NULL));

	//是否死亡的标识
	bool isDead = false;
	char preKey = NULL;
	Wall wall;
	wall.initWall();
	wall.drawWall();
	Food food(wall);
	food.setFood();
	Snake snake(wall, food);
	snake.initSnake();
	gotoxy(hOut, 0, Wall::ROW);
	cout << "得分：" << snake.getScore() << "分" << endl;
	//gotoxy(hOut,5, 5);
	//接受用户出入
	while (true) {
		char key = _getch();

		if (preKey == NULL && key == snake.LEFT) {
			continue;
		}

		do {
			if (key == snake.LEFT || key == snake.RIGHT || key == snake.UP || key == snake.DOWN) {
				//判断本次按键是否与上次冲突
				if ((key == snake.LEFT && preKey == snake.RIGHT) ||
					(key == snake.RIGHT && preKey == snake.LEFT) ||
					(key == snake.UP && preKey == snake.DOWN) ||
					(key == snake.DOWN && preKey == snake.UP)) {
					key = preKey;
				}
				else {
					preKey = key;
				}
				preKey = key;
				if (snake.move(key) == true) {
					//移动成功的代码
					//system("cls");
					//wall.drawWall();
					gotoxy(hOut, 0, Wall::ROW);
					cout << "得分：" << snake.getScore() << "分" << endl;
					Sleep(snake.getSleepTime());
				}
				else {
					isDead = true;
					return 0;
				}
			}
			else {
				key = preKey;
			}
		} while (!_kbhit());//当没有键盘输入的时候返回0
	}

	system("pause");
	return EXIT_SUCCESS;
}