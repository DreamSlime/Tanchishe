#include "snake.h"
#include <windows.h>

void gotoxy1(HANDLE hOut1, int x, int y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(hOut1, pos);
}
HANDLE hOut1 = GetStdHandle(STD_OUTPUT_HANDLE);

Snake::Snake(Wall& tempWall, Food& foodtmp) :wall(tempWall), food(foodtmp) {
	pHead = NULL;
	isRool = false;
	score = 0;
}
void Snake::initSnake() {
	destroyPoint();
	addPoint(5, 3);
	addPoint(5, 4);
	addPoint(5, 5);

}
//�������еĽڵ�
void Snake::destroyPoint() {
	Point* pCur = pHead;
	while (pHead != NULL) {
		pCur = pHead->next;
		delete pHead;
		pHead = pCur;
	}
}

void Snake::addPoint(int x, int y) {
	//����һ���µĽڵ�
	Point* newPoint = new Point;
	newPoint->x = x;
	newPoint->y = y;
	newPoint->next = NULL;

	//���ԭ��ͷ��Ϊ�� ��Ϊ����
	if (pHead != NULL) {
		wall.setWall(pHead->x, pHead->y, '=');
		gotoxy1(hOut1, pHead->y * 2, pHead->x);
		cout << "=";
	}
	newPoint->next = pHead;

	pHead = newPoint;//����ͷ��
	wall.setWall(pHead->x, pHead->y, '@');
	gotoxy1(hOut1, pHead->y * 2, pHead->x);
	cout << "@";
}

void Snake::delPoint() {
	//�����ڵ����� ��ȥɾ������
	if (pHead == NULL || pHead->next == NULL) {
		return;
	}
	Point* pCur = pHead->next;
	Point* pPre = pHead;

	while (pCur->next != NULL) {
		pPre = pPre->next;
		pCur = pCur->next;
	}

	wall.setWall(pCur->x, pCur->y, ' ');
	gotoxy1(hOut1, pCur->y * 2, pCur->x);
	cout << " ";
	delete pCur;
	pCur = NULL;
	pPre->next = NULL;
}

bool Snake::move(char key) {
	int x = pHead->x;
	int y = pHead->y;

	switch (key) {
	case UP:
		x--;
		break;
	case DOWN:
		x++;
		break;
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	}
	//�ж������һ����������β�ͣ���Ӧ������
	Point* pCur = pHead->next;
	Point* pPre = pHead;

	while (pCur->next != NULL) {
		pPre = pPre->next;
		pCur = pCur->next;
	}
	if (pCur->x == x && pCur->y == y) {
		//����ѭ��β��
		isRool = true;
	}
	else {
		//�ж��û�Ҫ����λ���Ƿ�ɹ�
		if (wall.getWall(x, y) == '=') {
			addPoint(x, y);
			delPoint();
			system("cls");
			wall.drawWall();
			cout << "�÷֣�" << getScore() << "��" << endl;
			cout << "Game Over!!" << endl;
			return false;
		}
		else if (wall.getWall(x, y) == '*') {
			if (x == 0) {
				x = wall.COL - 2;
			}
			if (x >= wall.COL - 1) {
				x = 1;
			}
			if (y == 0) {
				y = wall.ROW - 2;
			}
			if (y >= wall.ROW - 1) {
				y = 1;
			}
		}
	}
	//�ƶ��ɹ�������
	//�Ե�ʳ�� δ�Ե�ʳ��
	if (wall.getWall(x, y) == '#') {
		if (food.special == false) { score += 100; addPoint(x, y); food.count++; }
		else {
			score += 400;
			wall.setWall(food.foodX1, food.foodY1, ' ');
			gotoxy1(hOut1, food.foodY1 * 2, food.foodX1);
			cout << " ";
			wall.setWall(food.foodX2, food.foodY2, ' ');
			gotoxy1(hOut1, food.foodY2 * 2, food.foodX2);
			cout << " ";
			wall.setWall(food.foodX3, food.foodY3, ' ');
			gotoxy1(hOut1, food.foodY3 * 2, food.foodX3);
			cout << " ";
			wall.setWall(food.foodX4, food.foodY4, ' ');
			gotoxy1(hOut1, food.foodY4 * 2, food.foodX4);
			cout << " ";
			if (key == UP) {
				addPoint(x, y);
				addPoint(x - 1, y); food.count++;
			}
			else if (key == DOWN) {
				addPoint(x, y);
				addPoint(x + 1, y); food.count++;
			}
			else if (key == RIGHT) {
				addPoint(x, y);
				addPoint(x, y + 1); food.count++;
			}
			else {
				addPoint(x, y);
				addPoint(x - 1, y); food.count++;
			}
		}
		food.setFood();
	}
	else {
		addPoint(x, y);
		delPoint();
		if (isRool == true) {
			wall.setWall(x, y, '@');
			gotoxy1(hOut1, y * 2, x);
			cout << "@";
		}
	}
	return true;
}

int Snake::getSleepTime() {
	int sleepTime = 0;
	int size = countList();
	if (size < 10) sleepTime = max(10, 300 - size * 10);
	else sleepTime = max(10, 300 - size * 5);
	return sleepTime;
}

int Snake::countList() {
	int size = 0;
	Point* curPoint = pHead;
	while (curPoint != NULL) {
		size++;
		curPoint = curPoint->next;
	}
	return size;
}

int Snake::getScore() {
	return score;
}