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

	//�Ƿ������ı�ʶ
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
	cout << "�÷֣�" << snake.getScore() << "��" << endl;
	//gotoxy(hOut,5, 5);
	//�����û�����
	while (true) {
		char key = _getch();

		if (preKey == NULL && key == snake.LEFT) {
			continue;
		}

		do {
			if (key == snake.LEFT || key == snake.RIGHT || key == snake.UP || key == snake.DOWN) {
				//�жϱ��ΰ����Ƿ����ϴγ�ͻ
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
					//�ƶ��ɹ��Ĵ���
					//system("cls");
					//wall.drawWall();
					gotoxy(hOut, 0, Wall::ROW);
					cout << "�÷֣�" << snake.getScore() << "��" << endl;
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
		} while (!_kbhit());//��û�м��������ʱ�򷵻�0
	}

	system("pause");
	return EXIT_SUCCESS;
}