#pragma once
#include <iostream>
#include "wall.h"
#include "food.h"
using namespace std;

class Snake {
public:
	Snake(Wall& tempWall, Food& foodtmp);
	enum { UP = 'w', DOWN = 's', LEFT = 'a', RIGHT = 'd' };
	struct Point {
		//������
		int x, y;
		//ָ����
		Point* next;
	};
	//��ʼ��
	void initSnake();
	//���ٽڵ�
	void destroyPoint();
	//��ӽڵ�
	void addPoint(int x, int y);
	//ɾ���ڵ�
	void delPoint();
	//�ƶ��ߵĲ���,����ֵ�������ƶ��Ƿ�ɹ�
	bool move(char key);
	//�趨�Ѷ�
	//��ȡˢ��ʱ��
	int getSleepTime();
	//��ȡ�ߵ����
	int countList();
	//��ȡ����
	int getScore();
	Point* pHead;
	Wall& wall;
	Food& food;
	bool isRool;//�ж�ѭ����ʾ
	int score;
};