#pragma once
#include<iostream>
#include<random>
#include"DrunkWalk.h"
int DrunkWalk::draw_bar(std::mt19937_64 randSeed)
{//��������ġ�� �ϱ�� �����ϸ� ȣ����
	int pos = 0;
	std::uniform_int_distribution<int> rand(-goal + 1, goal);
	//�̰� ���̷��� -goal~ goal�����ε� 
	//�ּ� 1�����ϸ鼭 ������� 2����� �ϰ�

	int bonus = rand(randSeed);
	//��Ƚ��(goal + bonus)��ŭ�� �̾Ƴ���
	//�״��� ��ο��Ұǵ� how?
	//goal+bonus�� ���Ϲ޾ư����� ����ϵ��Ϲٲ� �ݺ��� �Ʒ� switch�ο��ٰ���
	return bonus + goal;
}

void DrunkWalk::Randomdrawing(std::mt19937_64 Seed,char **MAP)
{
	std::uniform_int_distribution<int> range(0, 3);
	//���ΰ� �Ʒ��ΰ�/ ���ΰ� ���ΰ� 2������ ���� <<�׷��� �Լ��ϳ����� �غ��°�

	int dir = range(Seed);
	//���� �ȵǸ� �ٽ� �õ带 �ο���´ٰų� �ƴϸ� �̷���Ŵ

	int add_x = 0;
	int add_y = 0;

	int bar = draw_bar(Seed);
	while (bar-- >= 1)
	{
		switch (dir)
		{//�̰� ���� ���������µ�
		 //2��� �۴���� �⿬���� ����� <<�켱 �ִ�,�ּһ����� �������
		case 0: if (this->now_y < Size_y.first) add_y = 1; else add_y = -1; break;
		case 1:if (this->now_x < Size_x.first) add_x = 1; else add_x = -1; break;
		case 2:if (this->now_y > Size_y.second) add_y = -1; else add_y = 1; break;
		case 3:if (this->now_x > Size_x.second) add_x = -1; else add_x = 1; break;
		}
		now_y += add_y;
		now_x += add_x;
		if (now_y >= 0 && now_y <Size_y.second && now_x >= 0 && now_x < Size_x.second)
		{
			this->Draw(MAP);
		}
		else
		{
			now_y -= add_y;
			now_x -= add_x;
			break;
		}

	}
}

void DrunkWalk::Exit_Draw(char **MAP)
{
	MAP[now_x][now_y] = 'E';
}
