#pragma once
#include<iostream>
#include<random>
#include"DrunkWalk.h"
int DrunkWalk::draw_bar(std::mt19937_64 randSeed)
{//임의의위치로 하기로 결정하면 호출함
	int pos = 0;
	std::uniform_int_distribution<int> rand(-goal + 1, goal);
	//이거 왜이러나 -goal~ goal까지인데 
	//최소 1번은하면서 재수없음 2배까지 하게

	int bonus = rand(randSeed);
	//이횟수(goal + bonus)만큼을 뽑아낸다
	//그다음 드로우할건데 how?
	//goal+bonus를 리턴받아가지고 사용하도록바꿈 반복은 아래 switch로에다가ㅇ
	return bonus + goal;
}

void DrunkWalk::Randomdrawing(std::mt19937_64 Seed,char **MAP)
{
	std::uniform_int_distribution<int> range(0, 3);
	//위인가 아래인가/ 좌인가 우인가 2가지로 단축 <<그러면 함수하나만들어서 해보는게

	int dir = range(Seed);
	//만약 안되면 다시 시드를 부여잡는다거나 아니면 미러시킴

	int add_x = 0;
	int add_y = 0;

	int bar = draw_bar(Seed);
	while (bar-- >= 1)
	{
		switch (dir)
		{//이거 많이 쓰지말랬는데
		 //2적어도 작대기의 향연으로 만들거 <<우선 최대,최소사이즈 적용부터
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
