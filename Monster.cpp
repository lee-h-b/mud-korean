#include<cmath>
#include<iomanip>
#include<random>
#include<sstream>
#include "Monster.h"

/*

Monster::Monster()
{
}*/


Monster::~Monster()
{
}

void Monster::detect(CChara * Actor)
{
	std::pair<int, int> target = Actor->get_xy();
	double dist = std::pow(target.first - Pos.first,2) + std::pow(target.second - Pos.second,2);
	//���߿� �����丵�Ѵٸ� �� dist�� ��,������ ���°ɷ� ���Ұ���
	if (dist <= 5)
	{
		if (this->Pos.first - target.first > 0)
		{
			direction = 0;
		}
		else if (this->Pos.first - target.first < 0)
		{
			direction = 1;
		}
		else if (this->Pos.second - target.second > 0)
		{
			direction = 2;
		}
		else if (this->Pos.second - target.second < 0)
		{
			direction = 3;
		}
	}
	else
	{
		//���̷��� 0~3������ ������
		std::random_device rand;
		std::mt19937_64 seed(rand());
		std::uniform_int_distribution<int> range(0, 3);
		//���߿� �Լ��θ��� �Ű� a~b���� �̷��� �������� �õ� �����ٽ�
		direction = range(seed);
	}

//	MoveMent();//���⼭ ����ġ < ã���� Ʈ�系�� �װ���� ���°ɷ���
	//���� 5���϶������ ���Ϳ� �÷��̾��� first�� ����� �ؼ� -��� �Ʒ��� +�� ���� 
	//�����ɼ��ְڴ� mob.first - 
}
//�ش� ĳ���� x or y��ġ�� Ư����(�ϴ� �ӽ÷� 5)���̰� �׾ȿ� ���ع��� ���ٸ�
//�Ѿƿü� �ֵ��� �ϴ� ���𰡰� �ʿ��� ���� �߰��ߴµ� ����ٸ�?


void Monster::MoveMent()
{
	std::pair<int, int> there;
	if (delay >= 1)
	{
		delay = 0;
		switch (direction)
		{//�켱 ����Ʈ �����ϰ� ������ ���������� << actor��𼭰�����? ���� ����Ʈ�� bool�εǰ�
			//�ٷ� �����Ʈ �����ϴ°� ��������
			//���⼭ ���̽��� ���� ��ȭ
	//		if (there_is_null(mob, there = { Pos.first - 1, Pos.second }))
			//�ʿ��� �׷����� �����ٵ�����
		case 0:COM = new MoveUp(); COM->Action(this);	break;
		case 1:COM = new MoveDown(); COM->Action(this); break;
		case 2:COM = new MoveLeft(); COM->Action(this); break;
		case 3:COM = new MoveRight(); COM->Action(this); break;
		}
	}
	else
		delay += 0.01;

}

void Monster::set_xy_mob()
{
do
{
	std::random_device rand;
	std::mt19937_64 seed(rand());
	std::uniform_int_distribution<int> range(41, 40 * 38);
	//���� range�� �ٲ�Ȯ���� �ſ����
	Pos.first = range(seed) / 40;
	Pos.second = range(seed) % 40;
	} while (MAP[Pos.first][Pos.second] != '.');
}


void Monster::Show(std::queue<std::string> *clerk)
{
	std::ostringstream oss;
	oss << "�̸� : " << name ;//������ �Ⱦ����ɼ��� ����
	//�ִ̳°� �ְ� ������ �ٸ��� �� ���°����� �ҰŴ� endl����
	clerk->push(oss.str());
	oss.str("");
	oss.clear();
	
	oss << "ü��:" << std::setw(4) << Hp.first << "/" << std::setw(4)
	<< Hp.second << " ���ݷ�:" << std::setw(3) << Atk.first <<
		" ~ " << std::setw(3) << Atk.second;
		//���� % 2d",Hp.first, Hp.second, Atk.first, Atk.second,Def);
	clerk->push(oss.str());
	oss.str("");
	oss.clear();
oss << "���� " << std::setw(2) << Def << "\t ����ġ : " << std::setw(2) <<Exp;
	clerk->push(oss.str());
//�� clerk�� �̷������� �����ϰ� write �Լ��� ������
	//���ϸ� Ŭ����� ���ǹ��ѵ���
}
