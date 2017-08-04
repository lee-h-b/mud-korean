#pragma once
#include "location.h"


location::location(int size)
{
		//���⼭ �����ѹ��غ� ��ǥ =x,y�� ������ ������ ���������� Ȥ�ó� �𸣴� size���� �޾ư���
		std::random_device once;
		std::mt19937_64 seed(rand());
		std::uniform_int_distribution<int> range(0, size - 1);

		set_x = range(seed);
		set_y = range(seed);
		now_x = set_x;
		now_y = set_y;
		Start = false;
		End = false;
//		this->MAP = { MAP };
}

void location::Draw(char **MAP)
{
	if (Start == false)
	{
		Make_Start(MAP);
	}
	else if (set_x != now_x || set_y != now_y)
	{
		MAP[now_x][now_y] = '.';
	}
}

void location::Make_Start(char **MAP)
{
	if (Start == false)
	{
		MAP[now_x][now_y] = 'S';
		set_x = now_x;
		set_y = now_y;
		Start = true;
	}
}